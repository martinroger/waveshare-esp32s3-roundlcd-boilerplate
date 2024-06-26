#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "CST816S.h"
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <ui.h>
#include "obdHandler.h"

#ifndef TFT_BL
  #define TFT_BL 2
#endif

#ifndef SCREEN_ID_MAIN
  #define SCREEN_ID_MAIN 1
#endif

//Display buffer preparation
#define TFT_HOR_RES 240
#define TFT_VER_RES 240
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 4 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE];

// Touch initialisation
#define TP_INT 5
#define TP_SDA 6
#define TP_SCL 7
#define TP_RST 13
CST816S touch(TP_SDA, TP_SCL, TP_RST, TP_INT);
void touchRead(lv_indev_t *indev, lv_indev_data_t *data)
{
  
  if(touch.available()) {
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = touch.data.x;
    data->point.y = touch.data.y;
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

//Timers
Timer<millis> tickerLVGL      =   5;    //LVGL 5ms ticker
Timer<millis> refreshValues   =   100;  //Values refresh interval on the screens 
Timer<millis> OBDrequestDelay =   100;   //Interval for requests over OBD

//Vehicle variables
int32_t intakeTemp;
int32_t absBaroPressure = 100;
int32_t intakeManifoldPressure = 100;
int32_t boostPressure;
int32_t engineCoolantTemp;
int32_t controlModuleVoltage = 12000;

#ifdef TEST_GENERATOR
void generateValues() {
  intakeTemp    =   (int32_t)(127*(1+0.6*sin((2*PI/10000)*millis()))-40);
  boostPressure =   (int32_t)(127*(1+0.6*sin((2*PI/10000)*millis())));
  engineCoolantTemp   = (int32_t)(127*(1+0.6*sin((2*PI/10000)*millis()))-40);
  controlModuleVoltage = (int32_t)((12.0+3.0*sin((2*PI/10000)*millis()))*1000.0);
}
#else
void parseCANFrame() {
  if(ESP32Can.readFrame(rxFrame,0)) {
    if(rxFrame.identifier==FrameID) {
      OBD_length  = rxFrame.data[0];
      OBD_mode    = rxFrame.data[1];
      OBD_command = rxFrame.data[2];
      byteA       = rxFrame.data[3];
      byteB       = rxFrame.data[4];
      byteC       = rxFrame.data[5];
      byteD       = rxFrame.data[6];
      byteE       = rxFrame.data[7];

      if((OBD_mode-0x40)==0x01) { //Check we are in the correct mode
        switch (OBD_command)
        {
        case 0x05: //Engine Coolant Temperature : engineCoolantTemp
          engineCoolantTemp = ((int)byteA - 40);
          break;
        case 0x0B:
          intakeManifoldPressure = (int)byteA;
          break;
        case 0x0F :
          intakeTemp = ((int)byteA - 40);
          break;
        case 0x33 : 
          absBaroPressure = (int)byteA;
          break;
        case 0x42 : //Control module voltage... unit is mV !
          controlModuleVoltage = (256*(int)byteA + (int)byteB);
          break;
        default:
          break;
        }
        boostPressure = intakeManifoldPressure - absBaroPressure;
        lastConnected = millis();
      }
    }
  }
}
#endif

#if LV_USE_LOG != 0
void my_print( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

void setup() {
  //Initialise min-max indicators
  engineCoolantTemp_max = -40;
  engineCoolantTemp_min = 215;

  boostPressure_max = 0;
  boostPressure_min = 255;

  intakeTemp_max = -40;
  intakeTemp_min = 215;

  controlModuleVoltage_max = 0;
  controlModuleVoltage_min = 24000;

  //For Debug
  Serial.begin(115200);

  //CAN start
  canStart();

  #ifdef TEST_GENERATOR
  generateValues();
  #endif

  //Blackout the screen
  pinMode(TFT_BL,OUTPUT);
  analogWrite(TFT_BL,0);
  //digitalWrite(TFT_BL,HIGH);

  //Touch startup
  touch.begin();

  //LV startup sequence
  lv_init();
  #if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print );
  #endif
  lv_display_t * disp;
  disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev,touchRead);
  lv_disp_set_rotation(disp,LV_DISPLAY_ROTATION_90);
  //Draw screens
  ui_init();

  //Turn the lights on
  analogWrite(TFT_BL,128);
  //Debug
  Serial.println( "Setup done" );
}

void loop() {

  if(OBDrequestDelay) {
    sendObdFrame(requestID);
    //Move to the next requestID... would be better to use an enum list
    switch (requestID)  {
      case 0x05:
        requestID = 0x0B;
        break;
      case 0x0B:
        requestID = 0x0F;
        break;
      case 0x0F:
        requestID = 0x33;
        break;
      case 0x33:
        requestID = 0x42;
        break;
      case 0x42:
        requestID = 0x05;
        break;
      default:
        requestID = 0x05;
        break;
    }
  }
  
  //Parse a CAN Frame if available
  #ifdef TEST_GENERATOR
  generateValues();
  #else
  parseCANFrame();
  #endif

  //Update the canState in case of silent connection
  if(millis()-lastConnected>2000) {
    canState = false;
    }
  else {
    canState = true;
  }

  //Refresh the items in the UI
  if(refreshValues) {
    setCanState(!canState);
    
    //Coolant Screen
    updateCoolantScr(engineCoolantTemp);
    if((engineCoolantTemp_min>engineCoolantTemp) || (engineCoolantTemp_max<engineCoolantTemp))  {
      engineCoolantTemp_max = max(engineCoolantTemp_max,engineCoolantTemp);
      engineCoolantTemp_min = min(engineCoolantTemp_min,engineCoolantTemp);
      updateCoolantMinMax(engineCoolantTemp_min,engineCoolantTemp_max);
    }
    

    updateBoostScr(boostPressure);
    if((boostPressure_min>boostPressure) || (boostPressure_max<boostPressure))  {
      boostPressure_max = max(boostPressure_max,boostPressure);
      boostPressure_min = min(boostPressure_min,boostPressure);
      updateBoostMinMax(boostPressure_min,boostPressure_max);
    }

    updateIatScr(intakeTemp);
    if((intakeTemp_min>intakeTemp) || (intakeTemp_max<intakeTemp))  {
      intakeTemp_max = max(intakeTemp_max,intakeTemp);
      intakeTemp_min = min(intakeTemp_min,intakeTemp);
      updateIatMinMax(intakeTemp_min,intakeTemp_max);
    }

    updateVoltageScr(controlModuleVoltage);
    if((controlModuleVoltage_min>controlModuleVoltage) || (controlModuleVoltage_max<controlModuleVoltage))  {
      controlModuleVoltage_max = max(controlModuleVoltage_max,controlModuleVoltage);
      controlModuleVoltage_min = min(controlModuleVoltage_min,controlModuleVoltage);
      updateVoltageMinMax(controlModuleVoltage_min,controlModuleVoltage_max);
    }
  }
  
  //Loop LVGL
  if(tickerLVGL) {
    lv_task_handler();
    lv_tick_inc(5);
  }
}
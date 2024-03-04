// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_boostPressure_screen_init(void)
{
    ui_boostPressure = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_boostPressure, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);    /// Flags
    lv_obj_set_scrollbar_mode(ui_boostPressure, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(ui_boostPressure, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_boostPressure, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_boostArc = lv_arc_create(ui_boostPressure);
    lv_obj_set_width(ui_boostArc, 210);
    lv_obj_set_height(ui_boostArc, 210);
    lv_obj_set_align(ui_boostArc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_boostArc, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_boostArc, LV_SCROLLBAR_MODE_OFF);
    lv_arc_set_range(ui_boostArc, 0, 255);
    lv_arc_set_value(ui_boostArc, 128);
    lv_arc_set_bg_angles(ui_boostArc, 135, 45);
    lv_obj_set_style_arc_color(ui_boostArc, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_boostArc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_boostArc, lv_color_hex(0xFF7F00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_boostArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_boostArc, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_boostArc, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_boostArc, lv_color_hex(0xFFE800), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_boostArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_boostVal = lv_label_create(ui_boostPressure);
    lv_obj_set_width(ui_boostVal, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_boostVal, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_boostVal, LV_ALIGN_CENTER);
    lv_label_set_text(ui_boostVal, "---");
    lv_obj_clear_flag(ui_boostVal, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_boostVal, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_color(ui_boostVal, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_boostVal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_boostVal, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_boostVal, &ui_font_center60, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_boostUnit = lv_label_create(ui_boostPressure);
    lv_obj_set_width(ui_boostUnit, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_boostUnit, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_boostUnit, 0);
    lv_obj_set_y(ui_boostUnit, 100);
    lv_obj_set_align(ui_boostUnit, LV_ALIGN_CENTER);
    lv_label_set_text(ui_boostUnit, "kPa");
    lv_obj_clear_flag(ui_boostUnit, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_boostUnit, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_color(ui_boostUnit, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_boostUnit, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_boostUnit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_boostUnit, &ui_font_unit16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_boostLabel = lv_label_create(ui_boostPressure);
    lv_obj_set_width(ui_boostLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_boostLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_boostLabel, 0);
    lv_obj_set_y(ui_boostLabel, 38);
    lv_obj_set_align(ui_boostLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_boostLabel, "BOOST");
    lv_obj_set_style_text_color(ui_boostLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_boostLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_boostLabel, &ui_font_unit16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_boostPressure, ui_event_boostPressure, LV_EVENT_ALL, NULL);

}
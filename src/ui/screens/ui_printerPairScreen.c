#include "../ui.h"

void ui_event_printerPairScreenSubmitButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_msg_send(XTOUCH_ON_CLOUD_SELECT, NULL);
    }
}

void ui_printerPairScreen_screen_init(void)
{

    ui_printerPairScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_printerPairScreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM); /// Flags
    lv_obj_set_scrollbar_mode(ui_printerPairScreen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(ui_printerPairScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_printerPairScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_left(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_printerPairScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_printerPairScreenCaption;
    ui_printerPairScreenCaption = lv_label_create(ui_printerPairScreen);
    lv_obj_set_height(ui_printerPairScreenCaption, 50);
    lv_obj_set_width(ui_printerPairScreenCaption, lv_pct(100));
    lv_label_set_text(ui_printerPairScreenCaption, "Select Printer");
    lv_obj_set_style_text_align(ui_printerPairScreenCaption, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_printerPairScreenCaption, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_printerPairScreenCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_printerPairScreenCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_printerPairScreenCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_printerPairScreenCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *ui_printerPairScreenRoller;
    ui_printerPairScreenRoller = lv_roller_create(ui_printerPairScreen);

    lv_roller_set_options(ui_printerPairScreenRoller, LV_SYMBOL_CHARGE " Searching for Printers...", LV_ROLLER_MODE_NORMAL);
    lv_obj_set_width(ui_printerPairScreenRoller, lv_pct(100));
    lv_obj_set_flex_grow(ui_printerPairScreenRoller, 5);
    lv_obj_set_x(ui_printerPairScreenRoller, 344);
    lv_obj_set_y(ui_printerPairScreenRoller, 193);
    lv_obj_set_style_text_font(ui_printerPairScreenRoller, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_printerPairScreenRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_printerPairScreenRoller, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_printerPairScreenRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_printerPairScreenRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_printerPairScreenRoller, lv_color_hex(0x777777), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_printerPairScreenRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_printerPairScreenSubmitButton = lv_obj_create(ui_printerPairScreen);
    lv_obj_set_width(ui_printerPairScreenSubmitButton, 48);
    lv_obj_set_height(ui_printerPairScreenSubmitButton, 48);
    lv_obj_set_x(ui_printerPairScreenSubmitButton, -8);
    lv_obj_set_y(ui_printerPairScreenSubmitButton, -8);
    lv_obj_set_align(ui_printerPairScreenSubmitButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_flex_flow(ui_printerPairScreenSubmitButton, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_printerPairScreenSubmitButton, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(ui_printerPairScreenSubmitButton, LV_OBJ_FLAG_FLOATING);                                                                                                                                                                                                       /// Flags
    lv_obj_clear_flag(ui_printerPairScreenSubmitButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(ui_printerPairScreenSubmitButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(ui_printerPairScreenSubmitButton, lv_color_hex(0x22AF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_printerPairScreenSubmitButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_printerPairScreenSubmitButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_printerPairScreenSubmitButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_printerPairScreenSubmitButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_printerPairScreenSubmitButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_printerPairScreenSubmitButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_printerPairScreenSubmitButton, lv_color_hex(0x2AFF00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_printerPairScreenSubmitButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_flag(ui_printerPairScreenSubmitButton, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t *ui_printerPairScreenSubmitIcon;
    ui_printerPairScreenSubmitIcon = lv_label_create(ui_printerPairScreenSubmitButton);
    lv_obj_set_width(ui_printerPairScreenSubmitIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_printerPairScreenSubmitIcon, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(ui_printerPairScreenSubmitIcon, "q");
    lv_obj_set_style_text_color(ui_printerPairScreenSubmitIcon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_printerPairScreenSubmitIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_printerPairScreenSubmitIcon, &ui_font_xlcd, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_printerPairScreenSubmitButton, ui_event_printerPairScreenSubmitButton, LV_EVENT_ALL, NULL);
}

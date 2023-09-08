#include "../ui.h"
void ui_event_accessCodeScreenSubmit(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_READY)
    {
        const char *accessCode = lv_textarea_get_text(ui_accessCodeInput);
        // get length of string accessCode
        int n = strlen(accessCode);
        if (n == 8)
        {
            strcpy(xTouchConfig.xTouchAccessCode, lv_textarea_get_text(ui_accessCodeInput));
            lv_msg_send(XTOUCH_ON_CODE_ENTERED, NULL);
        }
    }

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        const char *accessCode = lv_textarea_get_text(ui_accessCodeInput);
        // get length of string accessCode
        int n = strlen(accessCode);

        lv_obj_set_style_text_color(ui_accessCodeInput, n != 8 ? lv_color_hex(0xFF0000) : lv_color_hex(0x0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (code == LV_EVENT_CANCEL)
    {
        lv_keyboard_mode_t lv_keyboard_mode = lv_keyboard_get_mode(ui_accessCodeScreenKeyboard);
        bool isKeyboardNumber = lv_keyboard_mode == LV_KEYBOARD_MODE_NUMBER;
        lv_keyboard_set_mode(ui_accessCodeScreenKeyboard, isKeyboardNumber ? LV_KEYBOARD_MODE_TEXT_LOWER : LV_KEYBOARD_MODE_NUMBER);
        lv_obj_set_height(ui_accessCodeScreenKeyboard, isKeyboardNumber ? 160 : 190);
        lv_obj_set_y(ui_accessCodeInput, isKeyboardNumber ? 30 : 0);
    }
}
void ui_accessCodeScreen_screen_init(void)
{
    ui_accessCodeScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_accessCodeScreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM); /// Flags
    lv_obj_set_scrollbar_mode(ui_accessCodeScreen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_flow(ui_accessCodeScreen, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_accessCodeScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_left(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_accessCodeScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_accessCodeScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *ui_accessCodeScreenKeyboard;
    ui_accessCodeScreenKeyboard = lv_keyboard_create(ui_accessCodeScreen);
    lv_keyboard_set_mode(ui_accessCodeScreenKeyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_height(ui_accessCodeScreenKeyboard, 190);
    lv_obj_set_width(ui_accessCodeScreenKeyboard, lv_pct(100));
    lv_obj_add_flag(ui_accessCodeScreenKeyboard, LV_OBJ_FLAG_FLOATING);                                                                                                                                                                                                                               /// Flags
    lv_obj_clear_flag(ui_accessCodeScreenKeyboard, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(ui_accessCodeScreenKeyboard, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_color(ui_accessCodeScreenKeyboard, lv_color_hex(0x444444), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_accessCodeScreenKeyboard, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // lv_obj_t *ui_accessCodeInput;
    ui_accessCodeInput = lv_textarea_create(ui_accessCodeScreen);
    lv_obj_set_width(ui_accessCodeInput, lv_pct(100));
    lv_obj_set_height(ui_accessCodeInput, LV_SIZE_CONTENT); /// 48
    lv_obj_set_x(ui_accessCodeInput, 0);
    lv_obj_set_y(ui_accessCodeInput, 0);
    lv_textarea_set_placeholder_text(ui_accessCodeInput, "Enter Access Code");
    lv_textarea_set_one_line(ui_accessCodeInput, true);
    lv_obj_add_flag(ui_accessCodeInput, LV_OBJ_FLAG_FLOATING);                                 /// Flags
    lv_obj_clear_flag(ui_accessCodeInput, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
    lv_obj_set_style_text_align(ui_accessCodeInput, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_accessCodeInput, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_accessCodeInput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_accessCodeInput, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_accessCodeInput, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_accessCodeInput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_letter_space(ui_accessCodeInput, 0, LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_accessCodeInput, 0, LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_accessCodeInput, &lv_font_montserrat_28, LV_PART_TEXTAREA_PLACEHOLDER | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_accessCodeInput, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_max_length(ui_accessCodeInput, 8);
    lv_keyboard_set_textarea(ui_accessCodeScreenKeyboard, ui_accessCodeInput);

    lv_obj_add_event_cb(ui_accessCodeInput, ui_event_accessCodeScreenSubmit, LV_EVENT_ALL, NULL);
}

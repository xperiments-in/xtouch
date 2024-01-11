#include "../ui.h"


void ui_event_comp_filamentComponent_onNozzleTemp(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;

    char value[10];
    itoa(message->data, value, 10);
    lv_label_set_text(target, value);
    lv_obj_set_style_text_color(target, message->data < 170 ? lv_color_hex(0x39a1fd) : lv_color_hex(0xfaa61e), LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_event_comp_filamentComponent_filamentScreenNozzleUp(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_filamentComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onNozzleUp(e);
    }
}
void ui_event_comp_filamentComponent_filamentScreenNozzleDown(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_filamentComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onNozzleDown(e);
    }
}
void ui_event_comp_filamentComponent_filamentScreenUnload(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_filamentComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onFilamentUnload(e);
    }
}
void ui_event_comp_filamentComponent_filamentScreenLoad(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_filamentComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onFilamentLoad(e);
    }
}

void ui_filamentComponent_onAMSBits(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    lv_obj_t *unload = ui_comp_get_child(target, UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENUNLOAD);

    if (bambuStatus.ams_exist_bits != 0 && bambuStatus.ams_status_main == AMS_STATUS_MAIN_IDLE && bambuStatus.hw_switch_state == 1 && bambuStatus.m_tray_now == 255)
    {
        lv_obj_clear_state(unload, LV_STATE_DISABLED);
    }
    else
    {
        lv_obj_add_state(unload, LV_STATE_DISABLED);
    }
}

void ui_event_comp_filamentComponent_onNozzleTempClick(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeNozzleTemp(e, 3);
    }
}


// COMPONENT filamentComponent

lv_obj_t *ui_filamentComponent_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_filamentComponent;
    cui_filamentComponent = lv_obj_create(comp_parent);
    lv_obj_set_height(cui_filamentComponent, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentComponent, 1);
    lv_obj_set_x(cui_filamentComponent, 386);
    lv_obj_set_y(cui_filamentComponent, 178);
    lv_obj_set_flex_flow(cui_filamentComponent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_filamentComponent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_filamentComponent, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentComponent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_filamentComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentComponent, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_filamentComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_filamentComponent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_filamentComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_filamentScreenNozzle;
    cui_filamentScreenNozzle = lv_obj_create(cui_filamentComponent);
    lv_obj_set_height(cui_filamentScreenNozzle, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenNozzle, 2);
    lv_obj_set_x(cui_filamentScreenNozzle, 386);
    lv_obj_set_y(cui_filamentScreenNozzle, 178);
    lv_obj_set_flex_flow(cui_filamentScreenNozzle, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_filamentScreenNozzle, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_filamentScreenNozzle, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenNozzle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzle, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_filamentScreenNozzle, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_filamentScreenNozzle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_filamentScreenNozzle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_filamentScreenNozzle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_filamentScreenNozzleUp;
    cui_filamentScreenNozzleUp = lv_label_create(cui_filamentScreenNozzle);
    lv_obj_set_width(cui_filamentScreenNozzleUp, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenNozzleUp, 2);
    lv_obj_set_align(cui_filamentScreenNozzleUp, LV_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenNozzleUp, "s");
    lv_obj_add_flag(cui_filamentScreenNozzleUp, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_filamentScreenNozzleUp, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenNozzleUp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenNozzleUp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenNozzleUp, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_filamentScreenNozzleUp, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleUp, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenNozzleUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenNozzleUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenNozzleUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenNozzleUp, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenNozzleUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleUp, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleUp, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_filamentScreenNozzleIcon;
    cui_filamentScreenNozzleIcon = lv_label_create(cui_filamentScreenNozzle);
    lv_obj_set_width(cui_filamentScreenNozzleIcon, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenNozzleIcon, 1);
    lv_obj_set_align(cui_filamentScreenNozzleIcon, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_filamentScreenNozzleIcon, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_filamentScreenNozzleIcon, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenNozzleIcon, "p");
    lv_obj_clear_flag(cui_filamentScreenNozzleIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenNozzleIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenNozzleIcon, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenNozzleIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_filamentScreenNozzleIcon, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleIcon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenNozzleIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenNozzleIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenNozzleIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenNozzleIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenNozzleIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleIcon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleIcon, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_flag(cui_filamentScreenNozzleIcon, LV_OBJ_FLAG_CLICKABLE);    

    lv_obj_t *cui_filamentScreenNozzleTemp;
    cui_filamentScreenNozzleTemp = lv_label_create(cui_filamentScreenNozzleIcon);
    lv_label_set_text(cui_filamentScreenNozzleTemp, "");
    lv_obj_set_style_text_font(cui_filamentScreenNozzleTemp, lv_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenNozzleTemp, -8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_filamentScreenNozzleDown;
    cui_filamentScreenNozzleDown = lv_label_create(cui_filamentScreenNozzle);
    lv_obj_set_width(cui_filamentScreenNozzleDown, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenNozzleDown, 2);
    lv_obj_set_align(cui_filamentScreenNozzleDown, LV_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenNozzleDown, "t");
    lv_obj_add_flag(cui_filamentScreenNozzleDown, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_filamentScreenNozzleDown, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenNozzleDown, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenNozzleDown, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenNozzleDown, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_filamentScreenNozzleDown, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleDown, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleDown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenNozzleDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenNozzleDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenNozzleDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenNozzleDown, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenNozzleDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenNozzleDown, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenNozzleDown, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_filamentScreenFilament;
    cui_filamentScreenFilament = lv_obj_create(cui_filamentComponent);
    lv_obj_set_height(cui_filamentScreenFilament, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenFilament, 2);
    lv_obj_set_x(cui_filamentScreenFilament, 386);
    lv_obj_set_y(cui_filamentScreenFilament, 178);
    lv_obj_set_flex_flow(cui_filamentScreenFilament, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_filamentScreenFilament, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_filamentScreenFilament, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenFilament, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_filamentScreenFilament, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_filamentScreenFilament, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_filamentScreenFilament, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_filamentScreenFilament, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_filamentScreenFilament, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_filamentScreenUnload;
    cui_filamentScreenUnload = lv_label_create(cui_filamentScreenFilament);
    lv_obj_set_width(cui_filamentScreenUnload, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenUnload, 2);
    lv_obj_set_align(cui_filamentScreenUnload, LV_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenUnload, "UN\nLOAD");
    lv_obj_add_flag(cui_filamentScreenUnload, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_filamentScreenUnload, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenUnload, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenUnload, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenUnload, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_filamentScreenUnload, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_radius(cui_filamentScreenUnload, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenUnload, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenUnload, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_bg_opa(cui_filamentScreenUnload, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenUnload, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenUnload, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenUnload, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenUnload, 28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenUnload, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenUnload, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenUnload, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_filamentScreenFilamentIcon;
    cui_filamentScreenFilamentIcon = lv_label_create(cui_filamentScreenFilament);
    lv_obj_set_width(cui_filamentScreenFilamentIcon, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenFilamentIcon, 1);
    lv_obj_set_align(cui_filamentScreenFilamentIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenFilamentIcon, "n");
    lv_obj_clear_flag(cui_filamentScreenFilamentIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenFilamentIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenFilamentIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenFilamentIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_filamentScreenFilamentIcon, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenFilamentIcon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_filamentScreenFilamentIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenFilamentIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenFilamentIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenFilamentIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenFilamentIcon, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenFilamentIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenFilamentIcon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenFilamentIcon, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_filamentScreenLoad;
    cui_filamentScreenLoad = lv_label_create(cui_filamentScreenFilament);
    lv_obj_set_width(cui_filamentScreenLoad, lv_pct(100));
    lv_obj_set_flex_grow(cui_filamentScreenLoad, 2);
    lv_obj_set_align(cui_filamentScreenLoad, LV_ALIGN_CENTER);
    lv_label_set_text(cui_filamentScreenLoad, "LOAD");
    lv_obj_add_flag(cui_filamentScreenLoad, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_filamentScreenLoad, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_filamentScreenLoad, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_filamentScreenLoad, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_filamentScreenLoad, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_filamentScreenLoad, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_radius(cui_filamentScreenLoad, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenLoad, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenLoad, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_bg_opa(cui_filamentScreenLoad, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_filamentScreenLoad, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_filamentScreenLoad, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_filamentScreenLoad, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_filamentScreenLoad, 36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_filamentScreenLoad, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_filamentScreenLoad, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_filamentScreenLoad, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_FILAMENTCOMPONENT_NUM);
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTCOMPONENT] = cui_filamentComponent;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE] = cui_filamentScreenNozzle;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEUP] = cui_filamentScreenNozzleUp;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEICON] = cui_filamentScreenNozzleIcon;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLETEMP] = cui_filamentScreenNozzleTemp;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENNOZZLE_FILAMENTSCREENNOZZLEDOWN] = cui_filamentScreenNozzleDown;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT] = cui_filamentScreenFilament;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENUNLOAD] = cui_filamentScreenUnload;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENFILAMENTICON] = cui_filamentScreenFilamentIcon;
    children[UI_COMP_FILAMENTCOMPONENT_FILAMENTSCREENFILAMENT_FILAMENTSCREENLOAD] = cui_filamentScreenLoad;
    lv_obj_add_event_cb(cui_filamentComponent, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_filamentComponent, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_filamentScreenNozzleUp, ui_event_comp_filamentComponent_filamentScreenNozzleUp, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_filamentScreenNozzleDown, ui_event_comp_filamentComponent_filamentScreenNozzleDown, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_filamentScreenUnload, ui_event_comp_filamentComponent_filamentScreenUnload, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_filamentScreenLoad, ui_event_comp_filamentComponent_filamentScreenLoad, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_filamentScreenNozzleIcon, ui_event_comp_filamentComponent_onNozzleTempClick, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_filamentComponent, ui_filamentComponent_onAMSBits, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_AMS_BITS, cui_filamentComponent, NULL);


    lv_obj_add_event_cb(cui_filamentScreenNozzleTemp, ui_event_comp_filamentComponent_onNozzleTemp, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_NOZZLE_TEMP, cui_filamentScreenNozzleTemp, NULL);    

    ui_comp_filamentComponent_create_hook(cui_filamentComponent);
    return cui_filamentComponent;
}

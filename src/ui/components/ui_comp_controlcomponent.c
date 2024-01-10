#include "../ui.h"

void ui_event_comp_controlComponent_controlScreenRange(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        controlMode.inc = controlMode.inc == 1 ? 10 : 1;
        onControlRange(e);
    }
}
void ui_event_comp_controlComponent_controlScreenLeft(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onControlLeft(e);
    }
}
void ui_event_comp_controlComponent_controlScreenUp(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onControlUp(e);
    }
}

void ui_event_comp_controlComponent_controlScreenHomeConfirm() { onControlHome(NULL); }
void ui_event_comp_controlComponent_controlScreenHome(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_confirmPanel_show(LV_SYMBOL_WARNING " Start Homing Process?", ui_event_comp_controlComponent_controlScreenHomeConfirm);
    }
}
void ui_event_comp_controlComponent_controlScreenDown(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onControlDown(e);
    }
}
void ui_event_comp_controlComponent_controlScreenAxixToggle(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onControlAxis(e);
    }
}
void ui_event_comp_controlComponent_controlScreenRight(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_controlComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onControlRight(e);
    }
}

void onXtouchRangeChange(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_label_set_text(target, controlMode.inc == 1 ? "1" : "10");
}

void onXTouchAxisChange(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    controlMode.axis = controlMode.axis == 0 ? 1 : 0;
    lv_label_set_text(target, controlMode.axis == 0 ? "l" : "m");

    lv_obj_t *left = ui_comp_get_child(ui_controlComponent, UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENLEFT);
    lv_obj_t *leftIcon = ui_comp_get_child(ui_controlComponent, UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENLEFT_CONTROLSCREENLEFTICON);
    lv_obj_t *right = ui_comp_get_child(ui_controlComponent, UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENRIGHT);
    lv_obj_t *rightIcon = ui_comp_get_child(ui_controlComponent, UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENRIGHT_CONTROLSCREENRIGHTICON);

    if (controlMode.axis == 0)
    {
        lv_obj_clear_state(left, LV_STATE_DISABLED);
        lv_obj_clear_state(right, LV_STATE_DISABLED);
        lv_obj_clear_state(leftIcon, LV_STATE_DISABLED);
        lv_obj_clear_state(rightIcon, LV_STATE_DISABLED);
    }
    else
    {
        lv_obj_add_state(left, LV_STATE_DISABLED);
        lv_obj_add_state(right, LV_STATE_DISABLED);
        lv_obj_add_state(leftIcon, LV_STATE_DISABLED);
        lv_obj_add_state(rightIcon, LV_STATE_DISABLED);
    }
}

// COMPONENT controlComponent

lv_obj_t *ui_controlComponent_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_controlComponent;
    cui_controlComponent = lv_obj_create(comp_parent);
    lv_obj_set_height(cui_controlComponent, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlComponent, 1);
    lv_obj_set_x(cui_controlComponent, 386);
    lv_obj_set_y(cui_controlComponent, 178);
    lv_obj_set_flex_flow(cui_controlComponent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlComponent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlComponent, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlComponent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_controlComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlComponent, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlComponent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenColA;
    cui_controlScreenColA = lv_obj_create(cui_controlComponent);
    lv_obj_set_height(cui_controlScreenColA, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenColA, 1);
    lv_obj_set_x(cui_controlScreenColA, 386);
    lv_obj_set_y(cui_controlScreenColA, 178);
    lv_obj_set_flex_flow(cui_controlScreenColA, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_controlScreenColA, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_controlScreenColA, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenColA, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenColA, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenColA, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenColA, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenColA, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenColA, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenRange;
    cui_controlScreenRange = lv_obj_create(cui_controlScreenColA);
    lv_obj_set_width(cui_controlScreenRange, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenRange, 2);
    lv_obj_set_x(cui_controlScreenRange, 386);
    lv_obj_set_y(cui_controlScreenRange, 178);
    lv_obj_set_flex_flow(cui_controlScreenRange, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenRange, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenRange, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenRange, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenRange, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenRange, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenRange, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenRange, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenRange, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenRange, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenRange, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenRange, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenRange, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenRange, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenRange, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenRange, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenRange, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenRangeIcon;
    cui_controlScreenRangeIcon = lv_label_create(cui_controlScreenRange);
    lv_obj_set_width(cui_controlScreenRangeIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_controlScreenRangeIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_controlScreenRangeIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenRangeIcon, "k");
    lv_obj_clear_flag(cui_controlScreenRangeIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenRangeIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenRangeIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenRangeIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenRangeValue;
    cui_controlScreenRangeValue = lv_label_create(cui_controlScreenRange);
    lv_obj_set_height(cui_controlScreenRangeValue, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenRangeValue, 1);
    lv_obj_set_align(cui_controlScreenRangeValue, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenRangeValue, "-");
    lv_obj_clear_flag(cui_controlScreenRangeValue, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenRangeValue, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenRangeValue, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenRangeValue, lv_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenLeft;
    cui_controlScreenLeft = lv_obj_create(cui_controlScreenColA);
    lv_obj_set_width(cui_controlScreenLeft, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenLeft, 2);
    lv_obj_set_x(cui_controlScreenLeft, 386);
    lv_obj_set_y(cui_controlScreenLeft, 178);
    lv_obj_set_flex_flow(cui_controlScreenLeft, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenLeft, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenLeft, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenLeft, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenLeft, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenLeft, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenLeft, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenLeft, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenLeft, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenLeft, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenLeft, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenLeft, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenLeft, 0, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_color(cui_controlScreenLeft, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);

    lv_obj_t *cui_controlScreenLeftIcon;
    cui_controlScreenLeftIcon = lv_label_create(cui_controlScreenLeft);
    lv_obj_set_height(cui_controlScreenLeftIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenLeftIcon, 1);
    lv_obj_set_align(cui_controlScreenLeftIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenLeftIcon, "u");
    lv_obj_clear_flag(cui_controlScreenLeftIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenLeftIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenLeftIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenLeftIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenLeftIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenLeftIcon, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);

    lv_obj_t *cui_controlScreenDummy0;
    cui_controlScreenDummy0 = lv_obj_create(cui_controlScreenColA);
    lv_obj_set_width(cui_controlScreenDummy0, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenDummy0, 2);
    lv_obj_set_x(cui_controlScreenDummy0, 386);
    lv_obj_set_y(cui_controlScreenDummy0, 178);
    lv_obj_set_flex_flow(cui_controlScreenDummy0, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenDummy0, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenDummy0, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenDummy0, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenDummy0, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenDummy0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenDummy0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenDummy0, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenDummy0, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenDummy0, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenDummy0, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenDummy0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenDummy0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenDummy0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenDummy0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenDummy0, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenDummy0, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenColB;
    cui_controlScreenColB = lv_obj_create(cui_controlComponent);
    lv_obj_set_height(cui_controlScreenColB, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenColB, 1);
    lv_obj_set_x(cui_controlScreenColB, 386);
    lv_obj_set_y(cui_controlScreenColB, 178);
    lv_obj_set_flex_flow(cui_controlScreenColB, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_controlScreenColB, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_controlScreenColB, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenColB, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenColB, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenColB, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenColB, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenColB, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenColB, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenUp;
    cui_controlScreenUp = lv_obj_create(cui_controlScreenColB);
    lv_obj_set_width(cui_controlScreenUp, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenUp, 2);
    lv_obj_set_x(cui_controlScreenUp, 386);
    lv_obj_set_y(cui_controlScreenUp, 178);
    lv_obj_set_flex_flow(cui_controlScreenUp, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenUp, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenUp, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenUp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenUp, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenUp, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenUp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenUp, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenUp, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenUpIcon;
    cui_controlScreenUpIcon = lv_label_create(cui_controlScreenUp);
    lv_obj_set_height(cui_controlScreenUpIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenUpIcon, 1);
    lv_obj_set_align(cui_controlScreenUpIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenUpIcon, "s");
    lv_obj_clear_flag(cui_controlScreenUpIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenUpIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenUpIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenUpIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenHome;
    cui_controlScreenHome = lv_obj_create(cui_controlScreenColB);
    lv_obj_set_width(cui_controlScreenHome, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenHome, 2);
    lv_obj_set_x(cui_controlScreenHome, 386);
    lv_obj_set_y(cui_controlScreenHome, 178);
    lv_obj_set_flex_flow(cui_controlScreenHome, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenHome, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenHome, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenHome, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenHome, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenHome, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenHome, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenHome, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenHome, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenHome, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenHome, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenHome, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenHomeIcon;
    cui_controlScreenHomeIcon = lv_label_create(cui_controlScreenHome);
    lv_obj_set_height(cui_controlScreenHomeIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenHomeIcon, 1);
    lv_obj_set_align(cui_controlScreenHomeIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenHomeIcon, "a");
    lv_obj_clear_flag(cui_controlScreenHomeIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenHomeIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenHomeIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenHomeIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenDown;
    cui_controlScreenDown = lv_obj_create(cui_controlScreenColB);
    lv_obj_set_width(cui_controlScreenDown, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenDown, 2);
    lv_obj_set_x(cui_controlScreenDown, 386);
    lv_obj_set_y(cui_controlScreenDown, 178);
    lv_obj_set_flex_flow(cui_controlScreenDown, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenDown, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenDown, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenDown, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenDown, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenDown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenDown, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenDown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenDown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenDown, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenDown, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenDownIcon;
    cui_controlScreenDownIcon = lv_label_create(cui_controlScreenDown);
    lv_obj_set_height(cui_controlScreenDownIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenDownIcon, 1);
    lv_obj_set_align(cui_controlScreenDownIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenDownIcon, "t");
    lv_obj_clear_flag(cui_controlScreenDownIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenDownIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenDownIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenDownIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenColC;
    cui_controlScreenColC = lv_obj_create(cui_controlComponent);
    lv_obj_set_height(cui_controlScreenColC, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenColC, 1);
    lv_obj_set_x(cui_controlScreenColC, 386);
    lv_obj_set_y(cui_controlScreenColC, 178);
    lv_obj_set_flex_flow(cui_controlScreenColC, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_controlScreenColC, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_controlScreenColC, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenColC, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenColC, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenColC, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenColC, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenColC, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenColC, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenAxixToggle;
    cui_controlScreenAxixToggle = lv_obj_create(cui_controlScreenColC);
    lv_obj_set_width(cui_controlScreenAxixToggle, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenAxixToggle, 2);
    lv_obj_set_x(cui_controlScreenAxixToggle, 386);
    lv_obj_set_y(cui_controlScreenAxixToggle, 178);
    lv_obj_set_flex_flow(cui_controlScreenAxixToggle, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenAxixToggle, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenAxixToggle, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenAxixToggle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenAxixToggle, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenAxixToggle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenAxixToggle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenAxixToggle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenAxixToggle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenAxixToggle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenAxixToggle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenAxixToggle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenAxixToggle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenAxixToggle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenAxixToggle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenAxixToggle, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenAxixToggle, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_controlScreenAxixToggleIcon;
    cui_controlScreenAxixToggleIcon = lv_label_create(cui_controlScreenAxixToggle);
    lv_obj_set_width(cui_controlScreenAxixToggleIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_controlScreenAxixToggleIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_controlScreenAxixToggleIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenAxixToggleIcon, "l");
    lv_obj_clear_flag(cui_controlScreenAxixToggleIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenAxixToggleIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenAxixToggleIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenAxixToggleIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_controlScreenRight;
    cui_controlScreenRight = lv_obj_create(cui_controlScreenColC);
    lv_obj_set_width(cui_controlScreenRight, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenRight, 2);
    lv_obj_set_x(cui_controlScreenRight, 386);
    lv_obj_set_y(cui_controlScreenRight, 178);
    lv_obj_set_flex_flow(cui_controlScreenRight, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenRight, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenRight, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenRight, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenRight, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenRight, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenRight, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenRight, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenRight, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenRight, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenRight, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenRight, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenRight, 0, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_color(cui_controlScreenRight, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);

    lv_obj_t *cui_controlScreenRightIcon;
    cui_controlScreenRightIcon = lv_label_create(cui_controlScreenRight);
    lv_obj_set_height(cui_controlScreenRightIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_controlScreenRightIcon, 1);
    lv_obj_set_align(cui_controlScreenRightIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_controlScreenRightIcon, "v");
    lv_obj_clear_flag(cui_controlScreenRightIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenRightIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_controlScreenRightIcon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_controlScreenRightIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenRightIcon, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenRightIcon, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DISABLED);

    lv_obj_t *cui_controlScreenDummy1;
    cui_controlScreenDummy1 = lv_obj_create(cui_controlScreenColC);
    lv_obj_set_width(cui_controlScreenDummy1, lv_pct(100));
    lv_obj_set_flex_grow(cui_controlScreenDummy1, 2);
    lv_obj_set_x(cui_controlScreenDummy1, 386);
    lv_obj_set_y(cui_controlScreenDummy1, 178);
    lv_obj_set_flex_flow(cui_controlScreenDummy1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_controlScreenDummy1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_controlScreenDummy1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_controlScreenDummy1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_controlScreenDummy1, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_controlScreenDummy1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_controlScreenDummy1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_controlScreenDummy1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_controlScreenDummy1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_controlScreenDummy1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_controlScreenDummy1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_controlScreenDummy1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_controlScreenDummy1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_controlScreenDummy1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_controlScreenDummy1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_controlScreenDummy1, lv_color_hex(0x008800), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_controlScreenDummy1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CONTROLCOMPONENT_NUM);
    children[UI_COMP_CONTROLCOMPONENT_CONTROLCOMPONENT] = cui_controlComponent;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA] = cui_controlScreenColA;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENRANGE] = cui_controlScreenRange;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENRANGE_CONTROLSCREENRANGEICON] = cui_controlScreenRangeIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENRANGE_CONTROLSCREENRANGEVALUE] = cui_controlScreenRangeValue;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENLEFT] = cui_controlScreenLeft;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENLEFT_CONTROLSCREENLEFTICON] = cui_controlScreenLeftIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLA_CONTROLSCREENDUMMY0] = cui_controlScreenDummy0;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB] = cui_controlScreenColB;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENUP] = cui_controlScreenUp;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENUP_CONTROLSCREENUPICON] = cui_controlScreenUpIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENHOME] = cui_controlScreenHome;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENHOME_CONTROLSCREENHOMEICON] = cui_controlScreenHomeIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENDOWN] = cui_controlScreenDown;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLB_CONTROLSCREENDOWN_CONTROLSCREENDOWNICON] = cui_controlScreenDownIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC] = cui_controlScreenColC;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENAXIXTOGGLE] = cui_controlScreenAxixToggle;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENAXIXTOGGLE_CONTROLSCREENAXIXTOGGLEICON] = cui_controlScreenAxixToggleIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENRIGHT] = cui_controlScreenRight;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENRIGHT_CONTROLSCREENRIGHTICON] = cui_controlScreenRightIcon;
    children[UI_COMP_CONTROLCOMPONENT_CONTROLSCREENCOLC_CONTROLSCREENDUMMY1] = cui_controlScreenDummy1;
    lv_obj_add_event_cb(cui_controlComponent, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_controlComponent, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_controlScreenRange, ui_event_comp_controlComponent_controlScreenRange, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenLeft, ui_event_comp_controlComponent_controlScreenLeft, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenUp, ui_event_comp_controlComponent_controlScreenUp, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenHome, ui_event_comp_controlComponent_controlScreenHome, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenDown, ui_event_comp_controlComponent_controlScreenDown, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenAxixToggle, ui_event_comp_controlComponent_controlScreenAxixToggle, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_controlScreenRight, ui_event_comp_controlComponent_controlScreenRight, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_controlScreenRangeValue, onXtouchRangeChange, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_CONTROL_INC_SWITCH, cui_controlScreenRangeValue, NULL);

    lv_obj_add_event_cb(cui_controlScreenAxixToggleIcon, onXTouchAxisChange, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_CONTROL_AXIS_SWITCH, cui_controlScreenAxixToggleIcon, NULL);

    ui_comp_controlComponent_create_hook(cui_controlComponent);
    return cui_controlComponent;
}

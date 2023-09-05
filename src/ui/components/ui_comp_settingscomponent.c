#include <stdio.h>
#include "../ui.h"

void setScreenTimerTimeout()
{
}

void ui_event_comp_settingsComponent_auxFanInput(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsAuxFan(e);
    }
}
void ui_event_comp_settingsComponent_chamberInput(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsChamberSensor(e);
    }
}
void ui_event_comp_settingsComponent_resetDeviceButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsResetDevice(e);
    }
}
void ui_event_comp_settingsComponent_unpairButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsUnPair(e);
    }
}

void ui_event_comp_settingsComponent_resetSettingsButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsReset(e);
    }
}

// COMPONENT settingsComponent

lv_obj_t *ui_settingsComponent_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_settingsComponent;
    cui_settingsComponent = lv_obj_create(ui_settingsScreen);
    lv_obj_set_height(cui_settingsComponent, lv_pct(100));
    lv_obj_set_flex_grow(cui_settingsComponent, 1);
    lv_obj_set_x(cui_settingsComponent, 385);
    lv_obj_set_y(cui_settingsComponent, 178);
    lv_obj_set_flex_flow(cui_settingsComponent, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_settingsComponent, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_settingsComponent, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_style_radius(cui_settingsComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_settingsComponent, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsComponent, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_settingsComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_settingsComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_settingsComponent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_settingsComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_settingsComponent, LV_SCROLLBAR_MODE_ACTIVE);

    lv_obj_set_style_bg_color(cui_settingsComponent, lv_color_hex(0x2AFF00), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsComponent, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsTitle;
    cui_settingsTitle = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_settingsTitle, lv_pct(100));
    lv_obj_set_height(cui_settingsTitle, LV_SIZE_CONTENT); /// 40
    lv_label_set_text(cui_settingsTitle, "SETTINGS");
    lv_obj_clear_flag(cui_settingsTitle, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_settingsTitle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_settingsTitle, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsTitle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsTitle, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_info;
    cui_info = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_info, lv_pct(100));
    lv_obj_set_height(cui_info, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_info, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_info, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_info, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(cui_info, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_infoLabel;
    cui_infoLabel = lv_label_create(cui_info);
    lv_obj_set_width(cui_infoLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_infoLabel, LV_SIZE_CONTENT); /// 1

    char output[200];
    sprintf(output, "Access Code:\n    %s\nSerial:\n    %s",
            xTouchConfig.xTouchAccessCode, xTouchConfig.xTouchSerialNumber);

    lv_label_set_text(cui_infoLabel, output);

    lv_obj_t *cui_unpairButton;
    cui_unpairButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_unpairButton, lv_pct(100));
    lv_obj_set_height(cui_unpairButton, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_unpairButton, LV_SYMBOL_SETTINGS " Unpair Device");
    lv_obj_add_flag(cui_unpairButton, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_unpairButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_unpairButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_unpairButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_unpairButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_unpairButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_unpairButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_reseDeviceButton;
    cui_reseDeviceButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_reseDeviceButton, lv_pct(100));
    lv_obj_set_height(cui_reseDeviceButton, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_reseDeviceButton, LV_SYMBOL_POWER " Reboot Device");
    lv_obj_add_flag(cui_reseDeviceButton, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_reseDeviceButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_reseDeviceButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_reseDeviceButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_reseDeviceButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_reseDeviceButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_reseDeviceButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_resetSettingsButton;
    cui_resetSettingsButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_resetSettingsButton, lv_pct(100));
    lv_obj_set_height(cui_resetSettingsButton, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_resetSettingsButton, LV_SYMBOL_SETTINGS " Restore Defaults");
    lv_obj_add_flag(cui_resetSettingsButton, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_resetSettingsButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_resetSettingsButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_resetSettingsButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_resetSettingsButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_resetSettingsButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_resetSettingsButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_resetSettingsButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_resetSettingsButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_resetSettingsButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_resetSettingsButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_SETTINGSCOMPONENT_NUM);
    children[UI_COMP_SETTINGSCOMPONENT_SETTINGSCOMPONENT] = cui_settingsComponent;
    children[UI_COMP_SETTINGSCOMPONENT_INFO] = cui_info;
    children[UI_COMP_SETTINGSCOMPONENT_INFO_INFOLABEL] = cui_infoLabel;
    children[UI_COMP_SETTINGSCOMPONENT_UNPAIRBUTTON] = cui_unpairButton;
    children[UI_COMP_SETTINGSCOMPONENT_RESETDEVICEBUTTON] = cui_reseDeviceButton;
    children[UI_COMP_SETTINGSCOMPONENT_RESETSETTINGSBUTTON] = cui_resetSettingsButton;
    lv_obj_add_event_cb(cui_settingsComponent, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_settingsComponent, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_reseDeviceButton, ui_event_comp_settingsComponent_resetDeviceButton, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_unpairButton, ui_event_comp_settingsComponent_unpairButton, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_resetSettingsButton, ui_event_comp_settingsComponent_resetSettingsButton, LV_EVENT_ALL, children);
    ui_comp_settingsComponent_create_hook(cui_settingsComponent);
    return cui_settingsComponent;
}

#include <Arduino.h>
#include <stdio.h>
#include "../ui.h"
#include "xtouch/globals.h"

const char *xtouch_device_get_print_state()
{
    switch (bambuStatus.print_status)
    {
    case XTOUCH_PRINT_STATUS_IDLE:
        return LV_SYMBOL_OK " Ready";
    case XTOUCH_PRINT_STATUS_FINISHED:
        return LV_SYMBOL_OK "Finished";
    case XTOUCH_PRINT_STATUS_FAILED:
        return LV_SYMBOL_WARNING "Failed";
    default:
        return "N/A";
    }
}

void ui_event_comp_homeComponent_mainScreenPlayPauseButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeControllerPlayPause(e);
    }
}
void ui_event_comp_homeComponent_mainScreenStopButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeControllerStop(e);
    }
}
void ui_event_comp_homeComponent_mainScreenSpeedDropDown(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onHomeSpeedSelection(e);
    }
}
void ui_event_comp_homeComponent_mainScreenLightButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeLight(e);
        _ui_state_modify(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENLIGHTBUTTON], LV_STATE_CHECKED, _UI_MODIFY_STATE_TOGGLE);
    }
}
void ui_event_comp_homeComponent_mainScreenBedTemp(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeBedTemp(e);
    }
}
void ui_event_comp_homeComponent_mainScreenNozzleTemp(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onHomeNozzleTemp(e, 0);
    }
}

void ui_event_comp_homeComponent_mainScreenSpeedChange(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    int last_speed = bambuStatus.printing_speed_lvl;
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        char buf[32];
        uint16_t index = lv_dropdown_get_selected(target);
        switch (index)
        {
        case 0:
            bambuStatus.printing_speed_lvl = XTOUCH_SPEED_LEVEL_SILENCE;
            break;
        case 1:
            bambuStatus.printing_speed_lvl = XTOUCH_SPEED_LEVEL_NORMAL;
            break;
        case 2:
            bambuStatus.printing_speed_lvl = XTOUCH_SPEED_LEVEL_RAPID;
            break;
        case 3:
            bambuStatus.printing_speed_lvl = XTOUCH_SPEED_LEVEL_RAMPAGE;
            break;
        }
        lv_msg_send(XTOUCH_COMMAND_PRINT_SPEED, NULL);
    }
}

void onXTouchLightMessage(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;

    if (message->data == 1)
    {

        lv_obj_add_state(target, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(target, LV_STATE_CHECKED);
    }
}

void onXTouchBedTemp(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;

    char value[10];

    itoa(message->data, value, 10);
    lv_label_set_text(target, value);
}

void onXTouchChamberTemp(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;
    char value[10];

    itoa(message->data, value, 10);
    lv_label_set_text(target, value);
}

void onXTouchBedTempTarget(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;
    lv_obj_set_style_text_color(target, message->data > 0 ? lv_color_hex(0xff682a) : lv_color_hex(0xCCCCCC), LV_PART_MAIN | LV_STATE_DEFAULT);
}

void onXTouchAMS(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;
    if (message->data == 1)
    {
        lv_obj_clear_flag(target, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(target, LV_OBJ_FLAG_HIDDEN);
    }
}

void onXTouchWifiSignal(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);

    struct XTOUCH_MESSAGE_DATA *message = (struct XTOUCH_MESSAGE_DATA *)m->payload;
    lv_obj_set_style_text_color(target, message->data < 50 ? lv_color_hex(0x2aff00) : lv_color_hex(0xff682a), LV_PART_MAIN | LV_STATE_DEFAULT);
}

void onXTouchIPCam(lv_event_t *e)
{

    lv_obj_t *target = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);
    if (bambuStatus.has_ipcam)
    {
        lv_obj_clear_flag(target, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_text_color(target, bambuStatus.camera_recording_when_printing || bambuStatus.camera_timelapse ? lv_color_hex(0x2aff00) : lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(target, bambuStatus.camera_timelapse ? "y 2" : "y");
    }
    else
    {
        lv_obj_add_flag(target, LV_OBJ_FLAG_HIDDEN);
    }
}

int printingLevelToIndex(int lvl)
{

    switch (lvl)
    {
    case XTOUCH_SPEED_LEVEL_INVALID:
        return 1;
    case XTOUCH_SPEED_LEVEL_SILENCE:
        return 0;
    case XTOUCH_SPEED_LEVEL_NORMAL:
        return 1;
    case XTOUCH_SPEED_LEVEL_RAPID:
        return 2;
    case XTOUCH_SPEED_LEVEL_RAMPAGE:
        return 3;
    }
}

void onXTouchPrintStatus(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_homeComponent = lv_event_get_user_data(e);

    ui_confirmPanel_hide(); // hide confirm panel if new data comes

    char layerText[32];
    sprintf(layerText, "%d/%d", bambuStatus.current_layer, bambuStatus.total_layers);
    lv_label_set_text(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER2_MAINSCREENLAYER], layerText);
    lv_slider_set_value(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENPROGRESSBAR], bambuStatus.mc_print_percent, LV_ANIM_ON);

    char remainingTimeText[48];
    _ui_seconds_to_timeleft(bambuStatus.mc_left_time, remainingTimeText);

    char percentAndRemaining[100]; // Adjust the size accordingly
    sprintf(percentAndRemaining, "%d%% -- %s", bambuStatus.mc_print_percent, remainingTimeText);

    lv_label_set_text(target, percentAndRemaining);

    lv_obj_t *playPauseButton = comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER_MAINSCREENPLAYPAUSEBUTTON];
    lv_obj_t *dropDown = comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL_MAINSCREENSPEEDDROPDOWN];

    switch (bambuStatus.print_status)
    {
    case XTOUCH_PRINT_STATUS_PAUSED:
        lv_label_set_text(playPauseButton, "z");
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENIDLE], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(dropDown, LV_STATE_DISABLED);

        break;
    case XTOUCH_PRINT_STATUS_RUNNING:

        lv_label_set_text(playPauseButton, "0");
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENIDLE], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(dropDown, LV_STATE_DISABLED);
        break;
    case XTOUCH_PRINT_STATUS_PREPARE:
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENIDLE], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_state(dropDown, LV_STATE_DISABLED);
        break;

    case XTOUCH_PRINT_STATUS_IDLE:
    case XTOUCH_PRINT_STATUS_FINISHED:
    case XTOUCH_PRINT_STATUS_FAILED:
        lv_obj_add_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(comp_homeComponent[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENIDLE], LV_OBJ_FLAG_HIDDEN);
        lv_obj_t *statusCaption = ui_comp_get_child(ui_mainStatusComponent, UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUSCAPTION);
        lv_label_set_text(statusCaption, xtouch_device_get_print_state());
        lv_obj_add_state(dropDown, LV_STATE_DISABLED);
        break;
    }

    lv_obj_clear_state(playPauseButton, LV_STATE_DISABLED);

    lv_dropdown_set_selected(dropDown, printingLevelToIndex(bambuStatus.printing_speed_lvl));
}

// COMPONENT homeComponent

lv_obj_t *ui_homeComponent_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_homeComponent;
    cui_homeComponent = lv_obj_create(ui_homeScreen);
    lv_obj_set_width(cui_homeComponent, lv_pct(85));
    lv_obj_set_height(cui_homeComponent, lv_pct(100));
    lv_obj_set_x(cui_homeComponent, 386);
    lv_obj_set_y(cui_homeComponent, 178);
    lv_obj_set_flex_flow(cui_homeComponent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_homeComponent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_homeComponent, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_homeComponent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_homeComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_homeComponent, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_homeComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_homeComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_homeComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_homeComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_homeComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_homeComponent, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_homeComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_homeComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_homeComponent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_homeComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenLeft;
    cui_mainScreenLeft = lv_obj_create(cui_homeComponent);
    lv_obj_set_width(cui_mainScreenLeft, lv_pct(75));
    lv_obj_set_height(cui_mainScreenLeft, lv_pct(100));
    lv_obj_set_x(cui_mainScreenLeft, 386);
    lv_obj_set_y(cui_mainScreenLeft, 178);
    lv_obj_set_flex_flow(cui_mainScreenLeft, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenLeft, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenLeft, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenLeft, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenLeft, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenLeft, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenLeft, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenLeft, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenLeft, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenLeft, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenLeft, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenStatusBar;
    cui_mainScreenStatusBar = lv_obj_create(cui_mainScreenLeft);
    lv_obj_set_height(cui_mainScreenStatusBar, lv_pct(12));
    lv_obj_set_width(cui_mainScreenStatusBar, lv_pct(100));
    lv_obj_set_x(cui_mainScreenStatusBar, 386);
    lv_obj_set_y(cui_mainScreenStatusBar, 178);
    lv_obj_set_flex_flow(cui_mainScreenStatusBar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenStatusBar, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenStatusBar, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenStatusBar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenStatusBar, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenStatusBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenStatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenStatusBar, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenStatusBar, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenStatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenStatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenStatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenStatusBar, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenStatusBar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenStatusBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenWifiIcon;
    cui_mainScreenWifiIcon = lv_label_create(cui_mainScreenStatusBar);
    lv_obj_set_width(cui_mainScreenWifiIcon, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(cui_mainScreenWifiIcon, LV_SIZE_CONTENT); /// 16
    lv_label_set_text(cui_mainScreenWifiIcon, "x");
    lv_obj_clear_flag(cui_mainScreenWifiIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenWifiIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenWifiIcon, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenCameraIcon;
    cui_mainScreenCameraIcon = lv_label_create(cui_mainScreenStatusBar);
    lv_obj_set_height(cui_mainScreenCameraIcon, LV_SIZE_CONTENT); /// 16
    lv_obj_set_flex_grow(cui_mainScreenCameraIcon, 1);
    lv_label_set_text(cui_mainScreenCameraIcon, "y");
    lv_obj_clear_flag(cui_mainScreenCameraIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenCameraIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenCameraIcon, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenCameraIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenCameraIcon, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenCameraIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenCameraIcon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenAMS;
    cui_mainScreenAMS = lv_obj_create(cui_mainScreenStatusBar);
    lv_obj_set_height(cui_mainScreenAMS, lv_pct(70));
    lv_obj_set_flex_grow(cui_mainScreenAMS, 1);
    lv_obj_set_x(cui_mainScreenAMS, 386);
    lv_obj_set_y(cui_mainScreenAMS, 178);
    lv_obj_set_flex_flow(cui_mainScreenAMS, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenAMS, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenAMS, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenAMS, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenAMS, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenAMS, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenAMS, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenAMS, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenAMS, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(cui_mainScreenAMS, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t *cui_mainScreenAMSColor0;
    cui_mainScreenAMSColor0 = lv_obj_create(cui_mainScreenAMS);
    lv_obj_set_height(cui_mainScreenAMSColor0, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenAMSColor0, 1);
    lv_obj_set_x(cui_mainScreenAMSColor0, 386);
    lv_obj_set_y(cui_mainScreenAMSColor0, 178);
    lv_obj_set_flex_flow(cui_mainScreenAMSColor0, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenAMSColor0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenAMSColor0, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenAMSColor0, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenAMSColor0, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenAMSColor0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenAMSColor0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenAMSColor0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenAMSColor0, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenAMSColor0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenAMSColor0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenAMSColor1;
    cui_mainScreenAMSColor1 = lv_obj_create(cui_mainScreenAMS);
    lv_obj_set_height(cui_mainScreenAMSColor1, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenAMSColor1, 1);
    lv_obj_set_x(cui_mainScreenAMSColor1, 386);
    lv_obj_set_y(cui_mainScreenAMSColor1, 178);
    lv_obj_set_flex_flow(cui_mainScreenAMSColor1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenAMSColor1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenAMSColor1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenAMSColor1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenAMSColor1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenAMSColor1, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenAMSColor1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenAMSColor1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenAMSColor1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenAMSColor1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenAMSColor1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenAMSColor2;
    cui_mainScreenAMSColor2 = lv_obj_create(cui_mainScreenAMS);
    lv_obj_set_height(cui_mainScreenAMSColor2, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenAMSColor2, 1);
    lv_obj_set_x(cui_mainScreenAMSColor2, 386);
    lv_obj_set_y(cui_mainScreenAMSColor2, 178);
    lv_obj_set_flex_flow(cui_mainScreenAMSColor2, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenAMSColor2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenAMSColor2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenAMSColor2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenAMSColor2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenAMSColor2, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenAMSColor2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenAMSColor2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenAMSColor2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenAMSColor2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenAMSColor2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenAMSColor3;
    cui_mainScreenAMSColor3 = lv_obj_create(cui_mainScreenAMS);
    lv_obj_set_height(cui_mainScreenAMSColor3, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenAMSColor3, 1);
    lv_obj_set_x(cui_mainScreenAMSColor3, 386);
    lv_obj_set_y(cui_mainScreenAMSColor3, 178);
    lv_obj_set_flex_flow(cui_mainScreenAMSColor3, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenAMSColor3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenAMSColor3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenAMSColor3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenAMSColor3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenAMSColor3, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenAMSColor3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenAMSColor3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenAMSColor3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenAMSColor3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenAMSColor3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mainStatusComponent = ui_mainScreenStatus_create(cui_mainScreenLeft);

    lv_obj_t *cui_mainScreenPlayer;
    cui_mainScreenPlayer = lv_obj_create(cui_mainScreenLeft);
    lv_obj_set_width(cui_mainScreenPlayer, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenPlayer, 3);
    lv_obj_set_x(cui_mainScreenPlayer, 386);
    lv_obj_set_y(cui_mainScreenPlayer, 178);
    lv_obj_set_flex_flow(cui_mainScreenPlayer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenPlayer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenPlayer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenPlayer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenPlayer, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenPlayer, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenPlayer, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenPlayer, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenPlayer, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenPlayer, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenPlayer, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenController;
    cui_mainScreenController = lv_obj_create(cui_mainScreenPlayer);
    lv_obj_set_width(cui_mainScreenController, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenController, 4);
    lv_obj_set_x(cui_mainScreenController, 364);
    lv_obj_set_y(cui_mainScreenController, 183);
    lv_obj_set_flex_flow(cui_mainScreenController, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenController, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenController, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenController, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenController, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenController, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenController, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenController, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenNozzleIcon;
    cui_mainScreenNozzleIcon = lv_label_create(cui_mainScreenController);
    lv_obj_set_width(cui_mainScreenNozzleIcon, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(cui_mainScreenNozzleIcon, LV_SIZE_CONTENT); /// 24
    lv_label_set_text(cui_mainScreenNozzleIcon, "p");
    lv_obj_clear_flag(cui_mainScreenNozzleIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenNozzleIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenNozzleIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenPlayPauseButton;
    cui_mainScreenPlayPauseButton = lv_label_create(cui_mainScreenController);
    lv_obj_set_height(cui_mainScreenPlayPauseButton, LV_SIZE_CONTENT); /// 48
    lv_obj_set_flex_grow(cui_mainScreenPlayPauseButton, 1);
    lv_obj_set_align(cui_mainScreenPlayPauseButton, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenPlayPauseButton, "0");
    lv_obj_add_flag(cui_mainScreenPlayPauseButton, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_mainScreenPlayPauseButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenPlayPauseButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_mainScreenPlayPauseButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_mainScreenPlayPauseButton, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_mainScreenPlayPauseButton, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_mainScreenPlayPauseButton, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_mainScreenPlayPauseButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenPlayPauseButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenPlayPauseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenPlayPauseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenPlayPauseButton, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenPlayPauseButton, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenPlayPauseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenPlayPauseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenPlayPauseButton, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_mainScreenPlayPauseButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_mainScreenStopButton;
    cui_mainScreenStopButton = lv_label_create(cui_mainScreenController);
    lv_obj_set_height(cui_mainScreenStopButton, LV_SIZE_CONTENT); /// 48
    lv_obj_set_flex_grow(cui_mainScreenStopButton, 1);
    lv_obj_set_align(cui_mainScreenStopButton, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenStopButton, "1");
    lv_obj_add_flag(cui_mainScreenStopButton, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_mainScreenStopButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenStopButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(cui_mainScreenStopButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_mainScreenStopButton, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_mainScreenStopButton, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_mainScreenStopButton, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(cui_mainScreenStopButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenStopButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenStopButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenStopButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenStopButton, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenStopButton, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenStopButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenStopButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenStopButton, lv_color_hex(0xff682a), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_mainScreenStopButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_mainScreenProgressBar;
    cui_mainScreenProgressBar = lv_slider_create(cui_mainScreenPlayer);
    lv_slider_set_value(cui_mainScreenProgressBar, 60, LV_ANIM_OFF);
    if (lv_slider_get_mode(cui_mainScreenProgressBar) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(cui_mainScreenProgressBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(cui_mainScreenProgressBar, lv_pct(100));
    lv_obj_set_height(cui_mainScreenProgressBar, lv_pct(6));
    lv_obj_set_align(cui_mainScreenProgressBar, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_mainScreenProgressBar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenProgressBar, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenProgressBar, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
    lv_obj_set_style_bg_color(cui_mainScreenProgressBar, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenProgressBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(cui_mainScreenProgressBar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenProgressBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(cui_mainScreenProgressBar, lv_color_hex(0xCCCCCC), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenProgressBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenProgressBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenProgressBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenProgressBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenProgressBar, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenController1;
    cui_mainScreenController1 = lv_obj_create(cui_mainScreenPlayer);
    lv_obj_set_width(cui_mainScreenController1, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenController1, 1);
    lv_obj_set_x(cui_mainScreenController1, 364);
    lv_obj_set_y(cui_mainScreenController1, 183);
    lv_obj_set_flex_flow(cui_mainScreenController1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenController1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenController1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenController1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenController1, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenController1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenController1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenController1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenController1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenTimeLeftIcon;
    cui_mainScreenTimeLeftIcon = lv_label_create(cui_mainScreenController1);
    lv_obj_set_width(cui_mainScreenTimeLeftIcon, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(cui_mainScreenTimeLeftIcon, LV_SIZE_CONTENT); /// 16
    lv_label_set_text(cui_mainScreenTimeLeftIcon, "2");
    lv_obj_clear_flag(cui_mainScreenTimeLeftIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenTimeLeftIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenTimeLeftIcon, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenTimeLeft;
    cui_mainScreenTimeLeft = lv_label_create(cui_mainScreenController1);
    lv_obj_set_width(cui_mainScreenTimeLeft, LV_SIZE_CONTENT);  /// 3
    lv_obj_set_height(cui_mainScreenTimeLeft, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenTimeLeft, LV_ALIGN_CENTER);
    lv_label_set_long_mode(cui_mainScreenTimeLeft, LV_LABEL_LONG_CLIP);
    lv_label_set_text(cui_mainScreenTimeLeft, "N/A");
    lv_obj_clear_flag(cui_mainScreenTimeLeft, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenTimeLeft, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenTimeLeft, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenController2;
    cui_mainScreenController2 = lv_obj_create(cui_mainScreenPlayer);
    lv_obj_set_width(cui_mainScreenController2, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenController2, 1);
    lv_obj_set_x(cui_mainScreenController2, 364);
    lv_obj_set_y(cui_mainScreenController2, 183);
    lv_obj_set_flex_flow(cui_mainScreenController2, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenController2, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenController2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenController2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenController2, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenController2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenController2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenController2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenController2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenLayerIcon;
    cui_mainScreenLayerIcon = lv_label_create(cui_mainScreenController2);
    lv_obj_set_width(cui_mainScreenLayerIcon, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(cui_mainScreenLayerIcon, LV_SIZE_CONTENT); /// 16
    lv_label_set_text(cui_mainScreenLayerIcon, "3");
    lv_obj_clear_flag(cui_mainScreenLayerIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenLayerIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenLayerIcon, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenLayer;
    cui_mainScreenLayer = lv_label_create(cui_mainScreenController2);
    lv_obj_set_width(cui_mainScreenLayer, LV_SIZE_CONTENT);  /// 3
    lv_obj_set_height(cui_mainScreenLayer, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenLayer, LV_ALIGN_CENTER);
    lv_label_set_long_mode(cui_mainScreenLayer, LV_LABEL_LONG_CLIP);
    lv_label_set_text(cui_mainScreenLayer, "100/255");
    lv_obj_clear_flag(cui_mainScreenLayer, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenLayer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenLayer, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenCentral;
    cui_mainScreenCentral = lv_obj_create(cui_mainScreenLeft);
    lv_obj_set_width(cui_mainScreenCentral, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenCentral, 1);
    lv_obj_set_x(cui_mainScreenCentral, 386);
    lv_obj_set_y(cui_mainScreenCentral, 178);
    lv_obj_set_flex_flow(cui_mainScreenCentral, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenCentral, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenCentral, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenCentral, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenCentral, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenCentral, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenCentral, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenCentral, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenCentral, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenCentral, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenSpeedIcon;
    cui_mainScreenSpeedIcon = lv_label_create(cui_mainScreenCentral);
    lv_obj_set_width(cui_mainScreenSpeedIcon, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(cui_mainScreenSpeedIcon, LV_SIZE_CONTENT); /// 16
    lv_label_set_text(cui_mainScreenSpeedIcon, "h");
    lv_obj_clear_flag(cui_mainScreenSpeedIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenSpeedIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenSpeedIcon, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenSpeedDropDown;
    cui_mainScreenSpeedDropDown = lv_dropdown_create(cui_mainScreenCentral);
    lv_dropdown_set_options(cui_mainScreenSpeedDropDown, "Silent\nStandard\nSport\nLudicrous");
    lv_obj_set_width(cui_mainScreenSpeedDropDown, lv_pct(90));
    lv_obj_set_height(cui_mainScreenSpeedDropDown, LV_SIZE_CONTENT);           /// 1
    lv_obj_add_state(cui_mainScreenSpeedDropDown, LV_STATE_PRESSED);           /// States
    lv_obj_add_flag(cui_mainScreenSpeedDropDown, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_set_style_bg_color(cui_mainScreenSpeedDropDown, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenSpeedDropDown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenSpeedDropDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_dropdown_set_selected(cui_mainScreenSpeedDropDown, 1);

    lv_obj_set_style_text_color(cui_mainScreenSpeedDropDown, lv_color_hex(0x2aff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenSpeedDropDown, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_text_letter_space(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_letter_space(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 32, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x2aff00), LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_SELECTED | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), lv_color_hex(0x00AA00), LV_PART_SELECTED | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(cui_mainScreenSpeedDropDown), 255, LV_PART_SELECTED | LV_STATE_PRESSED);

    lv_obj_t *cui_mainScreenRight;
    cui_mainScreenRight = lv_obj_create(cui_homeComponent);
    lv_obj_set_width(cui_mainScreenRight, lv_pct(25));
    lv_obj_set_height(cui_mainScreenRight, lv_pct(100));
    lv_obj_set_x(cui_mainScreenRight, 386);
    lv_obj_set_y(cui_mainScreenRight, 178);
    lv_obj_set_flex_flow(cui_mainScreenRight, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenRight, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenRight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenRight, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenRight, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenRight, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenRight, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenRight, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenRight, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenRight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenLightButton;
    cui_mainScreenLightButton = lv_obj_create(cui_mainScreenRight);
    lv_obj_set_height(cui_mainScreenLightButton, lv_pct(25));
    lv_obj_set_width(cui_mainScreenLightButton, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenLightButton, 1);
    lv_obj_set_x(cui_mainScreenLightButton, 386);
    lv_obj_set_y(cui_mainScreenLightButton, 178);
    lv_obj_set_flex_flow(cui_mainScreenLightButton, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_mainScreenLightButton, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    // lv_obj_add_state(cui_mainScreenLightButton, LV_STATE_CHECKED);                                                                                                                                                                                                          /// States
    lv_obj_clear_flag(cui_mainScreenLightButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenLightButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenLightButton, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenLightButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenLightButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenLightButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenLightButton, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenLightButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cui_mainScreenLightButton, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(cui_mainScreenLightButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(cui_mainScreenLightButton, 3, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(cui_mainScreenLightButton, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(cui_mainScreenLightButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_t *cui_mainScreenLightButtonIcon;
    cui_mainScreenLightButtonIcon = lv_label_create(cui_mainScreenLightButton);
    lv_obj_set_width(cui_mainScreenLightButtonIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenLightButtonIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenLightButtonIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenLightButtonIcon, "w");
    lv_obj_clear_flag(cui_mainScreenLightButtonIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenLightButtonIcon, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_mainScreenLightButtonIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenTemps;
    cui_mainScreenTemps = lv_obj_create(cui_mainScreenRight);
    lv_obj_set_height(cui_mainScreenTemps, lv_pct(75));
    lv_obj_set_width(cui_mainScreenTemps, lv_pct(100));
    lv_obj_set_x(cui_mainScreenTemps, 386);
    lv_obj_set_y(cui_mainScreenTemps, 178);
    lv_obj_set_flex_flow(cui_mainScreenTemps, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenTemps, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(cui_mainScreenTemps, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenTemps, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenTemps, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenTemps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenTemps, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenTemps, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenTemps, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenTemps, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenTemps, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenTemps, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenTemps, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenTemps, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenTemps, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenNozzleTemp;
    cui_mainScreenNozzleTemp = lv_obj_create(cui_mainScreenTemps);
    lv_obj_set_width(cui_mainScreenNozzleTemp, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenNozzleTemp, 2);
    lv_obj_set_x(cui_mainScreenNozzleTemp, 386);
    lv_obj_set_y(cui_mainScreenNozzleTemp, 178);
    lv_obj_set_flex_flow(cui_mainScreenNozzleTemp, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenNozzleTemp, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenNozzleTemp, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenNozzleTemp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenNozzleTemp, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenNozzleTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenNozzleTemp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenNozzleTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenNozzleTemp, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_mainScreenNozzleTemp, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_mainScreenNozzleTempIcon;
    cui_mainScreenNozzleTempIcon = lv_label_create(cui_mainScreenNozzleTemp);
    lv_obj_set_width(cui_mainScreenNozzleTempIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenNozzleTempIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenNozzleTempIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenNozzleTempIcon, "f");
    lv_obj_set_style_text_color(cui_mainScreenNozzleTempIcon, lv_color_hex(0xCCCCCC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenNozzleTempIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_mainScreenNozzleTempIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenNozzleTempValue;
    cui_mainScreenNozzleTempValue = lv_label_create(cui_mainScreenNozzleTemp);
    lv_obj_set_width(cui_mainScreenNozzleTempValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenNozzleTempValue, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenNozzleTempValue, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenNozzleTempValue, "--");
    lv_obj_set_style_text_font(cui_mainScreenNozzleTempValue, lv_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenBedTemp;
    cui_mainScreenBedTemp = lv_obj_create(cui_mainScreenTemps);
    lv_obj_set_width(cui_mainScreenBedTemp, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenBedTemp, 2);
    lv_obj_set_x(cui_mainScreenBedTemp, 386);
    lv_obj_set_y(cui_mainScreenBedTemp, 178);
    lv_obj_set_flex_flow(cui_mainScreenBedTemp, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenBedTemp, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenBedTemp, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenBedTemp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenBedTemp, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenBedTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenBedTemp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenBedTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_mainScreenBedTemp, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_mainScreenBedTemp, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *cui_mainScreenBedTempIcon;
    cui_mainScreenBedTempIcon = lv_label_create(cui_mainScreenBedTemp);
    lv_obj_set_width(cui_mainScreenBedTempIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenBedTempIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenBedTempIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenBedTempIcon, "e");
    lv_obj_set_style_text_color(cui_mainScreenBedTempIcon, lv_color_hex(0xCCCCCC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenBedTempIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_mainScreenBedTempIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenBedTempValue;
    cui_mainScreenBedTempValue = lv_label_create(cui_mainScreenBedTemp);
    lv_obj_set_width(cui_mainScreenBedTempValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenBedTempValue, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenBedTempValue, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenBedTempValue, "--");
    lv_obj_set_style_text_font(cui_mainScreenBedTempValue, lv_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenChamberTemp;
    cui_mainScreenChamberTemp = lv_obj_create(cui_mainScreenTemps);
    lv_obj_set_width(cui_mainScreenChamberTemp, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenChamberTemp, 2);
    lv_obj_set_x(cui_mainScreenChamberTemp, 386);
    lv_obj_set_y(cui_mainScreenChamberTemp, 178);
    lv_obj_set_flex_flow(cui_mainScreenChamberTemp, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenChamberTemp, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenChamberTemp, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenChamberTemp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenChamberTemp, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenChamberTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenChamberTemp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenChamberTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (xtouch_bblp_is_p1Series() && !xTouchConfig.xTouchChamberSensorEnabled)
    {
        lv_obj_add_flag(cui_mainScreenChamberTemp, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_t *cui_mainScreenChamberTempIcon;
    cui_mainScreenChamberTempIcon = lv_label_create(cui_mainScreenChamberTemp);
    lv_obj_set_width(cui_mainScreenChamberTempIcon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenChamberTempIcon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenChamberTempIcon, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenChamberTempIcon, "g");
    lv_obj_set_style_text_color(cui_mainScreenChamberTempIcon, lv_color_hex(0xCCCCCC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenChamberTempIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_mainScreenChamberTempIcon, lv_icon_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenChamberTempValue;
    cui_mainScreenChamberTempValue = lv_label_create(cui_mainScreenChamberTemp);
    lv_obj_set_width(cui_mainScreenChamberTempValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenChamberTempValue, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(cui_mainScreenChamberTempValue, LV_ALIGN_CENTER);
    lv_label_set_text(cui_mainScreenChamberTempValue, "--");
    lv_obj_set_style_text_font(cui_mainScreenChamberTempValue, lv_font_big, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_HOMECOMPONENT_NUM);
    children[UI_COMP_HOMECOMPONENT_HOMECOMPONENT] = cui_homeComponent;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT] = cui_mainScreenLeft;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR] = cui_mainScreenStatusBar;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENWIFIICON] = cui_mainScreenWifiIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENCAMERAICON] = cui_mainScreenCameraIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENAMS] = cui_mainScreenAMS;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENAMS_MAINSCREENAMSCOLOR0] = cui_mainScreenAMSColor0;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENAMS_MAINSCREENAMSCOLOR1] = cui_mainScreenAMSColor1;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENAMS_MAINSCREENAMSCOLOR2] = cui_mainScreenAMSColor2;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENSTATUSBAR_MAINSCREENAMS_MAINSCREENAMSCOLOR3] = cui_mainScreenAMSColor3;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENIDLE] = ui_mainStatusComponent;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER] = cui_mainScreenPlayer;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER] = cui_mainScreenController;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER_MAINSCREENNOZZLEICON] = cui_mainScreenNozzleIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER_MAINSCREENPLAYPAUSEBUTTON] = cui_mainScreenPlayPauseButton;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER_MAINSCREENSTOPBUTTON] = cui_mainScreenStopButton;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENPROGRESSBAR] = cui_mainScreenProgressBar;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER1] = cui_mainScreenController1;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER1_MAINSCREENTIMELEFTICON] = cui_mainScreenTimeLeftIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER1_MAINSCREENTIMELEFT] = cui_mainScreenTimeLeft;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER2] = cui_mainScreenController2;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER2_MAINSCREENLAYERICON] = cui_mainScreenLayerIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENPLAYER_MAINSCREENCONTROLLER2_MAINSCREENLAYER] = cui_mainScreenLayer;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL] = cui_mainScreenCentral;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL_MAINSCREENSPEEDICON] = cui_mainScreenSpeedIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENLEFT_MAINSCREENCENTRAL_MAINSCREENSPEEDDROPDOWN] = cui_mainScreenSpeedDropDown;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT] = cui_mainScreenRight;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENLIGHTBUTTON] = cui_mainScreenLightButton;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENLIGHTBUTTON_MAINSCREENLIGHTBUTTONICON] = cui_mainScreenLightButtonIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS] = cui_mainScreenTemps;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENNOZZLETEMP] = cui_mainScreenNozzleTemp;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENNOZZLETEMP_MAINSCREENNOZZLETEMPICON] = cui_mainScreenNozzleTempIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENNOZZLETEMP_MAINSCREENNOZZLETEMPVALUE] = cui_mainScreenNozzleTempValue;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENBEDTEMP] = cui_mainScreenBedTemp;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENBEDTEMP_MAINSCREENBEDTEMPICON] = cui_mainScreenBedTempIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENBEDTEMP_MAINSCREENBEDTEMPVALUE] = cui_mainScreenBedTempValue;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENCHAMBERTEMP] = cui_mainScreenChamberTemp;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENCHAMBERTEMP_MAINSCREENCHAMBERTEMPICON] = cui_mainScreenChamberTempIcon;
    children[UI_COMP_HOMECOMPONENT_MAINSCREENRIGHT_MAINSCREENTEMPS_MAINSCREENCHAMBERTEMP_MAINSCREENCHAMBERTEMPVALUE] = cui_mainScreenChamberTempValue;
    lv_obj_add_event_cb(cui_homeComponent, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_homeComponent, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_mainScreenPlayPauseButton, ui_event_comp_homeComponent_mainScreenPlayPauseButton, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenStopButton, ui_event_comp_homeComponent_mainScreenStopButton, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenSpeedDropDown, ui_event_comp_homeComponent_mainScreenSpeedDropDown, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenLightButton, ui_event_comp_homeComponent_mainScreenLightButton, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenBedTemp, ui_event_comp_homeComponent_mainScreenBedTemp, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenNozzleTemp, ui_event_comp_homeComponent_mainScreenNozzleTemp, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_mainScreenSpeedDropDown, ui_event_comp_homeComponent_mainScreenSpeedChange, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_mainScreenLightButton, onXTouchLightMessage, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_LIGHT_REPORT, cui_mainScreenLightButton, NULL);

    lv_obj_add_event_cb(cui_mainScreenBedTempValue, onXTouchBedTemp, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_BED_TEMP, cui_mainScreenBedTempValue, NULL);

    lv_obj_add_event_cb(cui_mainScreenBedTempIcon, onXTouchBedTempTarget, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_BED_TARGET_TEMP, cui_mainScreenBedTempIcon, NULL);

    lv_obj_add_event_cb(cui_mainScreenNozzleTempValue, onXTouchBedTemp, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_NOZZLE_TEMP, cui_mainScreenNozzleTempValue, NULL);

    lv_obj_add_event_cb(cui_mainScreenChamberTempValue, onXTouchChamberTemp, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_CHAMBER_TEMP, cui_mainScreenChamberTempValue, NULL);

    lv_obj_add_event_cb(cui_mainScreenNozzleTempIcon, onXTouchBedTempTarget, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_NOZZLE_TARGET_TEMP, cui_mainScreenNozzleTempIcon, NULL);

    lv_obj_add_event_cb(cui_mainScreenAMS, onXTouchAMS, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_AMS, cui_mainScreenAMS, NULL);

    lv_obj_add_event_cb(cui_mainScreenWifiIcon, onXTouchWifiSignal, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_WIFI_SIGNAL, cui_mainScreenWifiIcon, NULL);

    lv_obj_add_event_cb(cui_mainScreenCameraIcon, onXTouchIPCam, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_IPCAM, cui_mainScreenCameraIcon, NULL);

    lv_obj_add_event_cb(cui_mainScreenTimeLeft, onXTouchPrintStatus, LV_EVENT_MSG_RECEIVED, children);
    lv_msg_subsribe_obj(XTOUCH_ON_PRINT_STATUS, cui_mainScreenTimeLeft, NULL);

    ui_comp_homeComponent_create_hook(cui_homeComponent);
    return cui_homeComponent;
}

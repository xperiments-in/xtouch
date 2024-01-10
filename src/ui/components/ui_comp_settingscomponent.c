#include <stdio.h>
#include "../ui.h"
#include "../ui_msgs.h"

void ui_event_comp_settingsComponent_unpairButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsUnPair(e);
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

void ui_event_comp_settingsComponent_onBackLight(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        lv_msg_send(XTOUCH_SETTINGS_BACKLIGHT, NULL);
    }
    if (event_code == LV_EVENT_RELEASED)
    {
        lv_msg_send(XTOUCH_SETTINGS_BACKLIGHT_SET, NULL);
    }
}

void ui_event_comp_settingsComponent_tftInvertInput(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_msg_send(XTOUCH_SETTINGS_TFT_INVERT, NULL);
    }
}

void ui_event_comp_settingsComponent_onTFTOFF(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        uint32_t value = lv_slider_get_value(ui_settingsTFTOFFSlider);
        lv_label_set_text_fmt(ui_settingsTFTOFFValue, "%dm", value);
        if (value < XTOUCH_LCD_MIN_SLEEP_TIME)
        {
            lv_label_set_text(ui_settingsTFTOFFValue, LV_SYMBOL_POWER);
        }
        else
        {
            lv_label_set_text_fmt(ui_settingsTFTOFFValue, "%dm", value);
        }
    }
    if (event_code == LV_EVENT_RELEASED)
    {
        lv_msg_send(XTOUCH_SETTINGS_TFTOFF_SET, NULL);
    }
}

void ui_event_comp_settingsComponent_onWOP(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsWOP(e);
    }
}

void ui_event_comp_settingsComponent_onTFTFlip(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsTFTFlip(e);
    }
}

void ui_event_comp_settingsComponent_onOTA(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsOTA(e);
    }
}

void ui_event_comp_settingsComponent_onAuxFan(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsAuxFan(e);
    }
}

void ui_event_comp_settingsComponent_onChamberFan(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsChamberFan(e);
    }
}

void ui_event_comp_settingsComponent_onChamberTemp(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        onSettingsChamberSensor(e);
    }
}

void ui_event_comp_settingsComponent_clearAccesCodeCacheButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSettingsClearAccesCodeCache(e);
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
    lv_obj_set_style_radius(cui_settingsComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_settingsComponent, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsComponent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsComponent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsComponent, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_settingsComponent, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
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
    lv_label_set_text_fmt(cui_settingsTitle, LV_SYMBOL_SETTINGS " SETTINGS");
    lv_obj_set_scrollbar_mode(cui_settingsTitle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_settingsTitle, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_settingsTitle, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_settingsTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_settingsTitle, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_screenTitle;
    cui_screenTitle = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_screenTitle, lv_pct(100));
    lv_obj_set_height(cui_screenTitle, LV_SIZE_CONTENT); /// 40
    lv_label_set_text(cui_screenTitle, LV_SYMBOL_IMAGE " LCD");
    lv_obj_set_scrollbar_mode(cui_screenTitle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_screenTitle, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_screenTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_screenTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_screenTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_screenTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_screenTitle, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_screenTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_screenTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_screenTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_screenTitle, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsBackLightPanel;
    cui_settingsBackLightPanel = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settingsBackLightPanel, lv_pct(100));
    lv_obj_set_height(cui_settingsBackLightPanel, 70);
    lv_obj_set_flex_flow(cui_settingsBackLightPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settingsBackLightPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_radius(cui_settingsBackLightPanel, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_settingsBackLightPanel, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsBackLightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsBackLightPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsBackLightPanel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsBackLightPanel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsBackLightPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsBackLightPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsBackLightPanelLabel;
    cui_settingsBackLightPanelLabel = lv_label_create(cui_settingsBackLightPanel);
    lv_obj_set_width(cui_settingsBackLightPanelLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settingsBackLightPanelLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settingsBackLightPanelLabel, "Back " LV_SYMBOL_CHARGE);
    lv_obj_set_style_text_font(cui_settingsBackLightPanelLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsBackLightPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsBackLightPanelLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsBackLightPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsBackLightPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *ui_settingsBackLightPanelSlider;
    ui_settingsBackLightPanelSlider = lv_slider_create(cui_settingsBackLightPanel);
    lv_slider_set_range(ui_settingsBackLightPanelSlider, 10, 255);
    lv_slider_set_value(ui_settingsBackLightPanelSlider, xTouchConfig.xTouchBacklightLevel, LV_ANIM_OFF);
    lv_obj_set_height(ui_settingsBackLightPanelSlider, 10);
    lv_obj_set_flex_grow(ui_settingsBackLightPanelSlider, 1);
    lv_obj_set_x(ui_settingsBackLightPanelSlider, 9);
    lv_obj_set_y(ui_settingsBackLightPanelSlider, 28);
    lv_obj_set_style_bg_color(ui_settingsBackLightPanelSlider, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsBackLightPanelSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_settingsBackLightPanelSlider, lv_color_hex(0x00FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsBackLightPanelSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_settingsBackLightPanelSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsBackLightPanelSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsTFTOFFPanel;
    cui_settingsTFTOFFPanel = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settingsTFTOFFPanel, lv_pct(100));
    lv_obj_set_height(cui_settingsTFTOFFPanel, 70);
    lv_obj_set_flex_flow(cui_settingsTFTOFFPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settingsTFTOFFPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_radius(cui_settingsTFTOFFPanel, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_settingsTFTOFFPanel, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsTFTOFFPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsTFTOFFPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsTFTOFFPanel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsTFTOFFPanel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsTFTOFFPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsTFTOFFPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsTFTOFFPanelLabel;
    cui_settingsTFTOFFPanelLabel = lv_label_create(cui_settingsTFTOFFPanel);
    lv_obj_set_width(cui_settingsTFTOFFPanelLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settingsTFTOFFPanelLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settingsTFTOFFPanelLabel, "Sleep");
    lv_obj_set_style_text_font(cui_settingsTFTOFFPanelLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsTFTOFFPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsTFTOFFPanelLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsTFTOFFPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsTFTOFFPanelLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsTFTOFFSlider = lv_slider_create(cui_settingsTFTOFFPanel);
    lv_slider_set_range(ui_settingsTFTOFFSlider, 4, 60);
    lv_slider_set_value(ui_settingsTFTOFFSlider, xTouchConfig.xTouchTFTOFFValue, LV_ANIM_OFF);
    lv_obj_set_height(ui_settingsTFTOFFSlider, 10);
    lv_obj_set_flex_grow(ui_settingsTFTOFFSlider, 1);
    lv_obj_set_x(ui_settingsTFTOFFSlider, 9);
    lv_obj_set_y(ui_settingsTFTOFFSlider, 28);
    lv_obj_set_style_bg_color(ui_settingsTFTOFFSlider, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsTFTOFFSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_settingsTFTOFFSlider, lv_color_hex(0x00FF00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsTFTOFFSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_settingsTFTOFFSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsTFTOFFSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_settingsTFTOFFValue = lv_label_create(cui_settingsTFTOFFPanel);
    lv_obj_set_width(ui_settingsTFTOFFValue, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_settingsTFTOFFValue, LV_SIZE_CONTENT); /// 1

    int32_t value = lv_slider_get_value(ui_settingsTFTOFFSlider);
    lv_label_set_text_fmt(ui_settingsTFTOFFValue, value < XTOUCH_LCD_MIN_SLEEP_TIME ? LV_SYMBOL_POWER : "%dm", value);
    lv_obj_set_style_text_font(ui_settingsTFTOFFValue, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_settingsTFTOFFValue, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_settingsTFTOFFValue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_settingsTFTOFFValue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_settingsTFTOFFValue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_screenWOPSetting;
    cui_screenWOPSetting = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_screenWOPSetting, lv_pct(100));
    lv_obj_set_height(cui_screenWOPSetting, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_screenWOPSetting, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_screenWOPSetting, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_screenWOPSetting, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_screenWOPSetting, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_screenWOPSetting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_screenWOPSetting, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_screenWOPSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_screenWOPSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_screenWOPSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_screenWOPSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_screenWOPLabel;
    cui_screenWOPLabel = lv_label_create(cui_screenWOPSetting);
    lv_obj_set_width(cui_screenWOPLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_screenWOPLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_screenWOPLabel, LV_SYMBOL_EYE_OPEN " Wake on Print");
    lv_obj_set_style_text_font(cui_screenWOPLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_screenWOPLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settingsWOPSwitch = lv_switch_create(cui_screenWOPSetting);
    lv_obj_set_width(ui_settingsWOPSwitch, 50);
    lv_obj_set_height(ui_settingsWOPSwitch, 25);

    lv_obj_set_style_bg_color(ui_settingsWOPSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsWOPSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settingsWOPSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsWOPSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingsWOPSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsWOPSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    if (xTouchConfig.xTouchWakeOnPrint)
    {
        lv_obj_add_state(ui_settingsWOPSwitch, LV_STATE_CHECKED);
    }

    lv_obj_t *cui_screenInvertSetting;
    cui_screenInvertSetting = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_screenInvertSetting, lv_pct(100));
    lv_obj_set_height(cui_screenInvertSetting, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_screenInvertSetting, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_screenInvertSetting, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_screenInvertSetting, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_screenInvertSetting, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_screenInvertSetting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_screenInvertSetting, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_screenInvertSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_screenInvertSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_screenInvertSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_screenInvertSetting, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_screenInvertLabel;
    cui_screenInvertLabel = lv_label_create(cui_screenInvertSetting);
    lv_obj_set_width(cui_screenInvertLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_screenInvertLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_screenInvertLabel, LV_SYMBOL_IMAGE " Invert Colors");
    lv_obj_set_style_text_font(cui_screenInvertLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_screenInvertLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settingsTFTInvertSwitch = lv_switch_create(cui_screenInvertSetting);
    lv_obj_set_width(ui_settingsTFTInvertSwitch, 50);
    lv_obj_set_height(ui_settingsTFTInvertSwitch, 25);

    lv_obj_set_style_bg_color(ui_settingsTFTInvertSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsTFTInvertSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settingsTFTInvertSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsTFTInvertSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingsTFTInvertSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsTFTInvertSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);
    if (xTouchConfig.xTouchTFTInvert)
    {
        lv_obj_add_state(ui_settingsTFTInvertSwitch, LV_STATE_CHECKED);
    }

    lv_obj_t *cui_settingsTFTFlip;
    cui_settingsTFTFlip = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settingsTFTFlip, lv_pct(100));
    lv_obj_set_height(cui_settingsTFTFlip, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_settingsTFTFlip, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settingsTFTFlip, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_settingsTFTFlip, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_settingsTFTFlip, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settingsTFTFlip, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settingsTFTFlip, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settingsTFTFlip, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settingsTFTFlip, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settingsTFTFlip, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settingsTFTFlip, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settingsTFTFlipLabel;
    cui_settingsTFTFlipLabel = lv_label_create(cui_settingsTFTFlip);
    lv_obj_set_width(cui_settingsTFTFlipLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settingsTFTFlipLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settingsTFTFlipLabel, LV_SYMBOL_SHUFFLE " Flip Screen");
    lv_obj_set_style_text_font(cui_settingsTFTFlipLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_settingsTFTFlipLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settingsTFTFlipSwitch = lv_switch_create(cui_settingsTFTFlip);
    lv_obj_set_width(ui_settingsTFTFlipSwitch, 50);
    lv_obj_set_height(ui_settingsTFTFlipSwitch, 25);

    lv_obj_set_style_bg_color(ui_settingsTFTFlipSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsTFTFlipSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settingsTFTFlipSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsTFTFlipSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingsTFTFlipSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settingsTFTFlipSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);
    if (xTouchConfig.xTouchTFTFlip)
    {
        lv_obj_add_state(ui_settingsTFTFlipSwitch, LV_STATE_CHECKED);
    }

    lv_obj_t *cui_pairingTitle;
    cui_pairingTitle = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_pairingTitle, lv_pct(100));
    lv_obj_set_height(cui_pairingTitle, LV_SIZE_CONTENT); /// 40
    lv_label_set_text(cui_pairingTitle, LV_SYMBOL_LIST " CONNECTED PRINTERS");
    lv_obj_set_scrollbar_mode(cui_pairingTitle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_pairingTitle, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_pairingTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_pairingTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_pairingTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_pairingTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_pairingTitle, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_pairingTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_pairingTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_pairingTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_pairingTitle, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_unpairButton;
    cui_unpairButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_unpairButton, lv_pct(100));
    lv_obj_set_height(cui_unpairButton, LV_SIZE_CONTENT);     /// 1
    lv_obj_add_flag(cui_unpairButton, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_obj_set_scrollbar_mode(cui_unpairButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_unpairButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_unpairButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_unpairButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_unpairButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_unpairButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text_fmt(cui_unpairButton, LV_SYMBOL_SHUFFLE " Unlink [ %s ]", xTouchConfig.xTouchPrinterName);
    lv_obj_set_style_text_font(cui_unpairButton, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_clearAccesCodeCacheButton;
    cui_clearAccesCodeCacheButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_clearAccesCodeCacheButton, lv_pct(100));
    lv_obj_set_height(cui_clearAccesCodeCacheButton, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_clearAccesCodeCacheButton, LV_SYMBOL_TRASH " Clear Access Code Cache");
    lv_obj_set_style_text_font(cui_clearAccesCodeCacheButton, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(cui_clearAccesCodeCacheButton, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_obj_set_scrollbar_mode(cui_clearAccesCodeCacheButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_clearAccesCodeCacheButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_clearAccesCodeCacheButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_clearAccesCodeCacheButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_clearAccesCodeCacheButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_clearAccesCodeCacheButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_clearAccesCodeCacheButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_clearAccesCodeCacheButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_clearAccesCodeCacheButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_deviceTitle;
    cui_deviceTitle = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_deviceTitle, lv_pct(100));
    lv_obj_set_height(cui_deviceTitle, LV_SIZE_CONTENT); /// 40
    lv_label_set_text_fmt(cui_deviceTitle, LV_SYMBOL_LIST " XTOUCH v%s", XTOUCH_FIRMWARE_VERSION);
    lv_obj_set_scrollbar_mode(cui_deviceTitle, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_deviceTitle, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_deviceTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_deviceTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_deviceTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_deviceTitle, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_deviceTitle, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_deviceTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_deviceTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_deviceTitle, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_deviceTitle, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settings_auxFan;
    cui_settings_auxFan = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settings_auxFan, lv_pct(100));
    lv_obj_set_height(cui_settings_auxFan, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_settings_auxFan, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settings_auxFan, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_settings_auxFan, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_settings_auxFan, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settings_auxFan, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settings_auxFan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settings_auxFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settings_auxFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settings_auxFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settings_auxFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settings_auxFanLabel;
    cui_settings_auxFanLabel = lv_label_create(cui_settings_auxFan);
    lv_obj_set_width(cui_settings_auxFanLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settings_auxFanLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settings_auxFanLabel, "AUX FAN");
    lv_obj_set_scrollbar_mode(cui_settings_auxFanLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settings_auxFanSwitch = lv_switch_create(cui_settings_auxFan);
    lv_obj_set_width(ui_settings_auxFanSwitch, 50);
    lv_obj_set_height(ui_settings_auxFanSwitch, 25);

    lv_obj_set_style_bg_color(ui_settings_auxFanSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_auxFanSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settings_auxFanSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settings_auxFanSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settings_auxFanSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_auxFanSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    if (!xtouch_bblp_is_p1p() && !xtouch_bblp_is_x1())
    {
        lv_obj_add_flag(cui_settings_auxFan, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        if (xTouchConfig.xTouchAuxFanEnabled)
        {
            lv_obj_add_state(ui_settings_auxFanSwitch, LV_STATE_CHECKED);
        }
    }

    lv_obj_t *cui_settings_chamberFan;
    cui_settings_chamberFan = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settings_chamberFan, lv_pct(100));
    lv_obj_set_height(cui_settings_chamberFan, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_settings_chamberFan, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settings_chamberFan, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_settings_chamberFan, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_settings_chamberFan, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settings_chamberFan, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settings_chamberFan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settings_chamberFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settings_chamberFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settings_chamberFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settings_chamberFan, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settings_chamberFanLabel;
    cui_settings_chamberFanLabel = lv_label_create(cui_settings_chamberFan);
    lv_obj_set_width(cui_settings_chamberFanLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settings_chamberFanLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settings_chamberFanLabel, "CHAMBER FAN");
    lv_obj_set_style_text_font(cui_settings_chamberFanLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_settings_chamberFanLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settings_chamberFanSwitch = lv_switch_create(cui_settings_chamberFan);
    lv_obj_set_width(ui_settings_chamberFanSwitch, 50);
    lv_obj_set_height(ui_settings_chamberFanSwitch, 25);

    lv_obj_set_style_bg_color(ui_settings_chamberFanSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_chamberFanSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settings_chamberFanSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settings_chamberFanSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settings_chamberFanSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_chamberFanSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    if (!xtouch_bblp_is_p1p())
    {
        lv_obj_add_flag(cui_settings_chamberFan, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        if (xTouchConfig.xTouchChamberFanEnabled)
        {
            lv_obj_add_state(ui_settings_chamberFanSwitch, LV_STATE_CHECKED);
        }
    }

    lv_obj_t *cui_settings_chamberSensor;
    cui_settings_chamberSensor = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settings_chamberSensor, lv_pct(100));
    lv_obj_set_height(cui_settings_chamberSensor, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_settings_chamberSensor, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settings_chamberSensor, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_settings_chamberSensor, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_settings_chamberSensor, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settings_chamberSensor, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settings_chamberSensor, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settings_chamberSensor, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settings_chamberSensor, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settings_chamberSensor, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settings_chamberSensor, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settings_chamberSensorLabel;
    cui_settings_chamberSensorLabel = lv_label_create(cui_settings_chamberSensor);
    lv_obj_set_width(cui_settings_chamberSensorLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settings_chamberSensorLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settings_chamberSensorLabel, "CHAMBER TEMP");
    lv_obj_set_style_text_font(cui_settings_chamberSensorLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_settings_chamberSensorLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settings_chamberSensorSwitch = lv_switch_create(cui_settings_chamberSensor);
    lv_obj_set_width(ui_settings_chamberSensorSwitch, 50);
    lv_obj_set_height(ui_settings_chamberSensorSwitch, 25);

    lv_obj_set_style_bg_color(ui_settings_chamberSensorSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_chamberSensorSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settings_chamberSensorSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settings_chamberSensorSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settings_chamberSensorSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_chamberSensorSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    if (!xtouch_bblp_is_p1Series())
    {
        lv_obj_add_flag(cui_settings_chamberSensor, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        if (xTouchConfig.xTouchChamberSensorEnabled)
        {
            lv_obj_add_state(ui_settings_chamberSensorSwitch, LV_STATE_CHECKED);
        }
    }

    lv_obj_t *cui_settings_ota;
    cui_settings_ota = lv_obj_create(cui_settingsComponent);
    lv_obj_set_width(cui_settings_ota, lv_pct(100));
    lv_obj_set_height(cui_settings_ota, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_settings_ota, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_settings_ota, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(cui_settings_ota, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_settings_ota, lv_color_hex(0x222222), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_settings_ota, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_settings_ota, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_settings_ota, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_settings_ota, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_settings_ota, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_settings_ota, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_settings_otaLabel;
    cui_settings_otaLabel = lv_label_create(cui_settings_ota);
    lv_obj_set_width(cui_settings_otaLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_settings_otaLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_settings_otaLabel, "OTA Update");
    lv_obj_set_style_text_font(cui_settings_otaLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cui_settings_otaLabel, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *ui_settingsTFTInvertSwitch;
    ui_settings_otaSwitch = lv_switch_create(cui_settings_ota);
    lv_obj_set_width(ui_settings_otaSwitch, 50);
    lv_obj_set_height(ui_settings_otaSwitch, 25);

    lv_obj_set_style_bg_color(ui_settings_otaSwitch, lv_color_hex(0x2AFF00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_otaSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_settings_otaSwitch, lv_color_hex(0x2AFF00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settings_otaSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settings_otaSwitch, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_settings_otaSwitch, 255, LV_PART_KNOB | LV_STATE_CHECKED);

    if (xTouchConfig.xTouchOTAEnabled)
    {
        lv_obj_add_state(ui_settings_otaSwitch, LV_STATE_CHECKED);
    }

    lv_obj_t *cui_reseDeviceButton;
    cui_reseDeviceButton = lv_label_create(cui_settingsComponent);
    lv_obj_set_width(cui_reseDeviceButton, lv_pct(100));
    lv_obj_set_height(cui_reseDeviceButton, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_reseDeviceButton, LV_SYMBOL_POWER " Reboot Device");
    lv_obj_set_style_text_font(cui_reseDeviceButton, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(cui_reseDeviceButton, LV_OBJ_FLAG_CLICKABLE);    /// Flags
    lv_obj_clear_flag(cui_reseDeviceButton, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_scrollbar_mode(cui_reseDeviceButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_reseDeviceButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_reseDeviceButton, lv_color_hex(0xFF682A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_reseDeviceButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_reseDeviceButton, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_reseDeviceButton, lv_color_hex(0x000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_SETTINGSCOMPONENT_NUM);
    children[UI_COMP_SETTINGSCOMPONENT_SETTINGSCOMPONENT] = cui_settingsComponent;
    children[UI_COMP_SETTINGSCOMPONENT_SCREEN_TITLE] = cui_screenTitle;
    children[UI_COMP_SETTINGSCOMPONENT_BACKLIGHT] = cui_settingsBackLightPanel;
    children[UI_COMP_SETTINGSCOMPONENT_BACKLIGHT_LABEL] = cui_settingsBackLightPanelLabel;
    children[UI_COMP_SETTINGSCOMPONENT_BACKLIGHT_SLIDER] = ui_settingsBackLightPanelSlider;
    children[UI_COMP_SETTINGSCOMPONENT_TFTOFF] = cui_settingsTFTOFFPanel;
    children[UI_COMP_SETTINGSCOMPONENT_TFTOFF_LABEL] = cui_settingsTFTOFFPanelLabel;
    children[UI_COMP_SETTINGSCOMPONENT_TFTOFF_SLIDER] = ui_settingsTFTOFFSlider;
    children[UI_COMP_SETTINGSCOMPONENT_TFTOFF_VALUE] = ui_settingsTFTOFFValue;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_WOP] = cui_screenWOPSetting;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_WOP_LABEL] = cui_screenWOPLabel;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_WOP_INPUT] = ui_settingsWOPSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_INVERT] = cui_screenInvertSetting;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_INVERT_LABEL] = cui_screenInvertLabel;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_INVERT_INPUT] = ui_settingsTFTInvertSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_FLIP] = cui_settingsTFTFlip;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_FLIP_LABEL] = cui_settingsTFTFlipLabel;
    children[UI_COMP_SETTINGSCOMPONENT_TFT_FLIP_INPUT] = ui_settingsTFTFlipSwitch;

    children[UI_COMP_SETTINGSCOMPONENT_PAIR_TITLE] = cui_pairingTitle;
    children[UI_COMP_SETTINGSCOMPONENT_UNPAIRBUTTON] = cui_unpairButton;
    children[UI_COMP_SETTINGSCOMPONENT_RESETSETTINGSBUTTON] = cui_clearAccesCodeCacheButton;

    children[UI_COMP_SETTINGSCOMPONENT_DEVICE_TITLE] = cui_deviceTitle;
    children[UI_COMP_SETTINGSCOMPONENT_AUXFAN] = cui_settings_auxFan;
    children[UI_COMP_SETTINGSCOMPONENT_AUXFAN_LABEL] = cui_settings_auxFanLabel;
    children[UI_COMP_SETTINGSCOMPONENT_AUXFAN_SWITCH] = ui_settings_auxFanSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBERFAN] = cui_settings_chamberFan;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBERFAN_LABEL] = cui_settings_chamberFanLabel;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBERFAN_SWITCH] = ui_settings_chamberFanSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBER_TEMP] = cui_settings_chamberSensor;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBER_TEMP_LABEL] = cui_settings_chamberSensorLabel;
    children[UI_COMP_SETTINGSCOMPONENT_CHAMBER_TEMP_SWITCH] = ui_settings_chamberSensorSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_OTA] = cui_settings_ota;
    children[UI_COMP_SETTINGSCOMPONENT_OTA_LABEL] = cui_settings_otaLabel;
    children[UI_COMP_SETTINGSCOMPONENT_OTA_SWITCH] = ui_settings_otaSwitch;
    children[UI_COMP_SETTINGSCOMPONENT_RESETDEVICEBUTTON] = cui_reseDeviceButton;

    lv_obj_add_event_cb(cui_settingsComponent, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_settingsComponent, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_unpairButton, ui_event_comp_settingsComponent_unpairButton, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(cui_clearAccesCodeCacheButton, ui_event_comp_settingsComponent_clearAccesCodeCacheButton, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(cui_reseDeviceButton, ui_event_comp_settingsComponent_resetDeviceButton, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_settingsTFTOFFSlider, ui_event_comp_settingsComponent_onTFTOFF, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsBackLightPanelSlider, ui_event_comp_settingsComponent_onBackLight, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsWOPSwitch, ui_event_comp_settingsComponent_onWOP, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_settingsTFTInvertSwitch, ui_event_comp_settingsComponent_tftInvertInput, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_event_cb(ui_settings_auxFanSwitch, ui_event_comp_settingsComponent_onAuxFan, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_settings_chamberFanSwitch, ui_event_comp_settingsComponent_onChamberFan, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_settings_chamberSensorSwitch, ui_event_comp_settingsComponent_onChamberTemp, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_settingsTFTFlipSwitch, ui_event_comp_settingsComponent_onTFTFlip, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_settings_otaSwitch, ui_event_comp_settingsComponent_onOTA, LV_EVENT_VALUE_CHANGED, NULL);

    ui_comp_settingsComponent_create_hook(cui_settingsComponent);
    return cui_settingsComponent;
}

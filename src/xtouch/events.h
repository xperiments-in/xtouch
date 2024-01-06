#ifndef _XLCD_CONFIG
#define _XLCD_CONFIG

void xtouch_events_onResetDevice(lv_msg_t *m)
{
    ESP.restart();
}

void xtouch_events_onUnPair(lv_msg_t *m)
{
    xtouch_ssdp_unpair();
}
void xtouch_events_onSSDP(lv_msg_t *m)
{
    xtouch_pair_loop_exit = true;

    char selectedUSNTitle[64];
    lv_roller_get_selected_str(ui_printerPairScreenRoller, selectedUSNTitle, 64);
    String selectedUSNTitleString = String(selectedUSNTitle);
    selectedUSNTitleString.trim();
    String selectedUSN = selectedUSNTitleString.substring(selectedUSNTitleString.lastIndexOf(" ") + 1);
    strcpy(xTouchConfig.xTouchSerialNumber, selectedUSN.c_str());
}

void xtouch_events_onCodeEntered(lv_msg_t *m)
{
    xtouch_pair_loop_exit = true;
}

void xtouch_events_onClearAccesCodeCache(lv_msg_t *m)
{
    xtouch_ssdp_clear_pair_list();
    ESP.restart();
}

void xtouch_events_onBackLight(lv_msg_t *m)
{
    int32_t value = lv_slider_get_value(ui_settingsBackLightPanelSlider);
    xTouchConfig.xTouchBacklightLevel = value;
    xtouch_screen_setBrightness(value);
}

void xtouch_events_onBackLightSet(lv_msg_t *m)
{
    int32_t value = lv_slider_get_value(ui_settingsBackLightPanelSlider);
    JsonDocument settings = xtouch_filesystem_readJson(SD, xtouch_paths_settings);
    settings["backlight"] = value;
    xTouchConfig.xTouchBacklightLevel = value;
    xtouch_filesystem_writeJson(SD, xtouch_paths_settings, settings);
    xtouch_screen_setBrightness(value);
}

void xtouch_events_onTFTTimerSet(lv_msg_t *m)
{
    int32_t value = lv_slider_get_value(ui_settingsTFTOFFSlider);
    xtouch_screen_setScreenTimer(value * 1000 * 60);

    JsonDocument settings = xtouch_filesystem_readJson(SD, xtouch_paths_settings);
    settings["tftOff"] = value;
    xTouchConfig.xTouchTFTOFFValue = value;
    xtouch_filesystem_writeJson(SD, xtouch_paths_settings, settings);
}

void xtouch_events_onTFTInvert(lv_msg_t *m)
{
    bool value = lv_obj_has_state(ui_settingsTFTInvertSwitch, LV_STATE_CHECKED);
    JsonDocument settings = xtouch_filesystem_readJson(SD, xtouch_paths_settings);
    settings["tftInvert"] = value ? true : false;
    xtouch_filesystem_writeJson(SD, xtouch_paths_settings, settings);
    xTouchConfig.xTouchTFTInvert = value;
    xtouch_screen_invertColors();
}

void xtouch_events_onSettingsSave(lv_msg_t *m)
{
    xtouch_settings_save();
}

void xtouch_events_onTFTFlip(lv_msg_t *m)
{
    xtouch_screen_toggleTFTFlip();
}

void xtouch_events_onResetTouch(lv_msg_t *m)
{
    xtouch_resetTouchConfig();
}

void xtouch_events_onChamberTempSwitch(lv_msg_t *m)
{
    if (xTouchConfig.xTouchChamberSensorEnabled)
    {
        xtouch_chamber_timer_start();
    }
    else
    {
        xtouch_chamber_timer_stop();
    }
}

void xtouch_setupGlobalEvents()
{
    lv_msg_subscribe(XTOUCH_SETTINGS_RESET_DEVICE, (lv_msg_subscribe_cb_t)xtouch_events_onResetDevice, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_UNPAIR, (lv_msg_subscribe_cb_t)xtouch_events_onUnPair, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_CLEAR_ACCESS_CODE_CACHE, (lv_msg_subscribe_cb_t)xtouch_events_onClearAccesCodeCache, NULL);
    lv_msg_subscribe(XTOUCH_ON_SSDP, (lv_msg_subscribe_cb_t)xtouch_events_onSSDP, NULL);
    lv_msg_subscribe(XTOUCH_ON_CODE_ENTERED, (lv_msg_subscribe_cb_t)xtouch_events_onCodeEntered, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_BACKLIGHT, (lv_msg_subscribe_cb_t)xtouch_events_onBackLight, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_BACKLIGHT_SET, (lv_msg_subscribe_cb_t)xtouch_events_onBackLightSet, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_TFTOFF_SET, (lv_msg_subscribe_cb_t)xtouch_events_onTFTTimerSet, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_TFT_INVERT, (lv_msg_subscribe_cb_t)xtouch_events_onTFTInvert, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_SAVE, (lv_msg_subscribe_cb_t)xtouch_events_onSettingsSave, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_CHAMBER_TEMP, (lv_msg_subscribe_cb_t)xtouch_events_onChamberTempSwitch, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_TFT_FLIP, (lv_msg_subscribe_cb_t)xtouch_events_onTFTFlip, NULL);
}

#endif
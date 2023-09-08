#ifndef _XLCD_CONFIG
#define _XLCD_CONFIG

void xtouch_events_onUpdatedConfig(lv_msg_t *m)
{
    // xtouch_saveConfig();
}
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
    ledcAnalogWrite(LEDC_CHANNEL_0, value);
}

void xtouch_events_onBackLightSet(lv_msg_t *m)
{
    int32_t value = lv_slider_get_value(ui_settingsBackLightPanelSlider);
    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, settingsPath);
    settings["backlight"] = value;
    xtouch_filesystem_writeJson(SD, settingsPath, settings);
    ledcAnalogWrite(LEDC_CHANNEL_0, value);
}

void xtouch_events_onTFTTimerSet(lv_msg_t *m)
{
    int32_t value = lv_slider_get_value(ui_settingsTFTOFFSlider);
    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, settingsPath);
    settings["tftOff"] = value;
    xtouch_filesystem_writeJson(SD, settingsPath, settings);
    xtouch_screen_updateScreenTimer(value * 1000 * 60);
}

void xtouch_events_onTFTInvert(lv_msg_t *m)
{
    bool value = lv_obj_has_state(ui_settingsTFTInvertSwitch, LV_STATE_CHECKED);
    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, settingsPath);
    settings["tftInvert"] = value ? true : false;
    xtouch_filesystem_writeJson(SD, settingsPath, settings);
    xTouchConfig.xTouchTFTInvert = value;
    xtouch_screen_invert_setup();
}

void xtouch_events_onSettingsSave(lv_msg_t *m)
{
    xtouch_settings_save();
}

void xtouch_events_onTFTFlip(lv_msg_t *m)
{
    xtouch_settings_save();
    xtouch_screen_setFlip();
    lv_obj_t *current = lv_scr_act();
    lv_obj_invalidate(current);
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
    lv_msg_subscribe(XTOUCH_SETTINGS_TFT_FLIP, (lv_msg_subscribe_cb_t)xtouch_events_onTFTFlip, NULL);
}

#endif
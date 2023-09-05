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
void xtouch_events_onResetConfig(lv_msg_t *m)
{
    // restartESPDefaults();
}
void xtouch_events_onUnPair(lv_msg_t *m)
{
    Serial.println("xtouch_events_onUnPair");
    xtouch_ssdp_unpair();
}
void xtouch_events_onSSDP(lv_msg_t *m)
{
    // restartESPDefaults();
    // String options = (const char *)lv_msg_get_payload(m);
    Serial.println("xtouch_events_onSSDP");
    Serial.println(xTouchConfig.xTouchSerialNumber);
    xtouch_ssdp_loop_exit = true;
}
void xtouch_events_onCodeEntered(lv_msg_t *m)
{
    // restartESPDefaults();
    // String options = (const char *)lv_msg_get_payload(m);
    Serial.println("xtouch_events_onCodeEntered");
    Serial.println(xTouchConfig.xTouchAccessCode);
    xtouch_ssdp_loop_exit = true;
}

void xtouch_setupGlobalEvents()
{
    lv_msg_subscribe(XTOUCH_CONFIG_UPDATE, (lv_msg_subscribe_cb_t)xtouch_events_onUpdatedConfig, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_RESET_DEVICE, (lv_msg_subscribe_cb_t)xtouch_events_onResetDevice, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_RESET, (lv_msg_subscribe_cb_t)xtouch_events_onResetConfig, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_UNPAIR, (lv_msg_subscribe_cb_t)xtouch_events_onUnPair, NULL);
    lv_msg_subscribe(XTOUCH_ON_SSDP, (lv_msg_subscribe_cb_t)xtouch_events_onSSDP, NULL);
    lv_msg_subscribe(XTOUCH_ON_CODE_ENTERED, (lv_msg_subscribe_cb_t)xtouch_events_onCodeEntered, NULL);
}

#endif
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
}
void xtouch_events_onCodeEntered(lv_msg_t *m)
{
    xtouch_pair_loop_exit = true;
}

void xtouch_events_onClearAccesCodeCache(lv_msg_t *m)
{
    xtouch_filesystem_deleteFile(SD, xtouch_ssdp_pair);
    ESP.restart();
}

void xtouch_setupGlobalEvents()
{
    lv_msg_subscribe(XTOUCH_CONFIG_UPDATE, (lv_msg_subscribe_cb_t)xtouch_events_onUpdatedConfig, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_RESET_DEVICE, (lv_msg_subscribe_cb_t)xtouch_events_onResetDevice, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_UNPAIR, (lv_msg_subscribe_cb_t)xtouch_events_onUnPair, NULL);
    lv_msg_subscribe(XTOUCH_SETTINGS_CLEAR_ACCESS_CODE_CACHE, (lv_msg_subscribe_cb_t)xtouch_events_onClearAccesCodeCache, NULL);
    lv_msg_subscribe(XTOUCH_ON_SSDP, (lv_msg_subscribe_cb_t)xtouch_events_onSSDP, NULL);
    lv_msg_subscribe(XTOUCH_ON_CODE_ENTERED, (lv_msg_subscribe_cb_t)xtouch_events_onCodeEntered, NULL);
}

#endif
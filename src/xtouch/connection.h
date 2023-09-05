#ifndef _XLCD_CONNECTION
#define _XLCD_CONNECTION

bool xtouch_wifi_setup()
{
    DynamicJsonDocument wifiConfig = xtouch_filesystem_readJson(SD, "/xtouch.json");
    if (wifiConfig.isNull() || !wifiConfig.containsKey("ssid") || !wifiConfig.containsKey("pwd"))
    {
        lv_label_set_text(introScreenCaption, LV_SYMBOL_SD_CARD " WRONG CONFIG FILE");
        lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();
        return false;
    }
    const char *ssid = wifiConfig["ssid"].as<const char *>();
    const char *password = wifiConfig["pwd"].as<const char *>();

    WiFi.setTxPower(WIFI_POWER_19_5dBm); // https://github.com/G6EJD/ESP32-8266-Adjust-WiFi-RF-Power-Output/blob/main/README.md

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println(F("[XTOUCH][CONNECTION] Connecting to WiFi .."));
    delay(500);
    wl_status_t status = WiFi.status();
    const char *statusText = "";
    lv_color_t statusColor = lv_color_hex(0x555555);
    while (status != WL_CONNECTED)
    {

        switch (status)
        {
        case WL_IDLE_STATUS:
            statusText = LV_SYMBOL_WIFI " Connecting to SSID";
            statusColor = lv_color_hex(0x555555);
            break;

        case WL_NO_SSID_AVAIL:
            statusText = LV_SYMBOL_WARNING " Bad SSID Check WiFi credentials";
            statusColor = lv_color_hex(0xff0000);
            break;

            // case WL_CONNECTION_LOST:
            //     break;

        case WL_CONNECT_FAILED:
        case WL_DISCONNECTED:
            statusText = LV_SYMBOL_WARNING " Check your WiFi credentials";
            statusColor = lv_color_hex(0xff0000);
            break;

        default:
            break;
        }

        if (statusText != "")
        {

            lv_label_set_text(introScreenCaption, statusText);
            lv_obj_set_style_text_color(introScreenCaption, statusColor, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_timer_handler();
            delay(500);
        }

        status = WiFi.status();
    }

    lv_label_set_text(introScreenCaption, LV_SYMBOL_WIFI " Connected to SSID");
    lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_timer_handler();
    delay(500);
    Serial.print(F("[XTOUCH][CONNECTION] Connected to the WiFi network with IP: "));
    Serial.println(WiFi.localIP());

    return true;
}

#endif
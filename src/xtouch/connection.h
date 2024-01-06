#ifndef _XLCD_CONNECTION
#define _XLCD_CONNECTION

bool xtouch_wifi_setup()
{
    JsonDocument wifiConfig = xtouch_filesystem_readJson(SD, xtouch_paths_wifi);
    if (wifiConfig.isNull() || !wifiConfig.containsKey("ssid") || !wifiConfig.containsKey("pwd"))
    {
        lv_label_set_text(introScreenCaption, wifiConfig.isNull() ? LV_SYMBOL_SD_CARD " Missing wifi.json" : LV_SYMBOL_WARNING " Inaccurate wifi.json");
        lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();
        lv_task_handler();
        return false;
    }
    const char *ssid = wifiConfig["ssid"].as<const char *>();
    const char *password = wifiConfig["pwd"].as<const char *>();
    int timeout = wifiConfig.containsKey("timeout") ? wifiConfig["timeout"].as<int>() : 3000;

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    ConsoleInfo.println(F("[XTOUCH][CONNECTION] Connecting to WiFi .."));

    lv_label_set_text(introScreenCaption, LV_SYMBOL_WIFI " Connecting");
    lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_timer_handler();
    lv_task_handler();

    delay(timeout);
    wl_status_t status = WiFi.status();
    const char *statusText = "";
    lv_color_t statusColor = lv_color_hex(0x555555);

    bool reboot = false;
    while (status != WL_CONNECTED)
    {

        switch (status)
        {
        case WL_IDLE_STATUS:
            statusText = LV_SYMBOL_WIFI " Connecting";
            statusColor = lv_color_hex(0x555555);
            break;

        case WL_NO_SSID_AVAIL:
            statusText = LV_SYMBOL_WARNING " Bad SSID Check WiFi credentials";
            statusColor = lv_color_hex(0xff0000);
            reboot = true;
            break;

            // case WL_CONNECTION_LOST:
            //     break;

        case WL_CONNECT_FAILED:
        case WL_DISCONNECTED:
            statusText = LV_SYMBOL_WARNING " Check your WiFi credentials";
            statusColor = lv_color_hex(0xff0000);
            reboot = true;
            break;

        default:
            break;
        }

        if (statusText != "")
        {

            lv_label_set_text(introScreenCaption, statusText);
            lv_obj_set_style_text_color(introScreenCaption, statusColor, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_timer_handler();
            lv_task_handler();
            delay(32);
        }

        if (reboot)
        {
            delay(3000);
            lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
            lv_timer_handler();
            lv_task_handler();
            ESP.restart();
        }
        status = WiFi.status();
    }

    WiFi.setTxPower(WIFI_POWER_19_5dBm); // https://github.com/G6EJD/ESP32-8266-Adjust-WiFi-RF-Power-Output/blob/main/README.md

    delay(1000);
    lv_label_set_text(introScreenCaption, LV_SYMBOL_WIFI " Connected");
    lv_timer_handler();
    lv_task_handler();
    delay(1000);
    ConsoleInfo.print(F("[XTOUCH][CONNECTION] Connected to the WiFi network with IP: "));
    ConsoleInfo.println(WiFi.localIP());

    return true;
}

#endif
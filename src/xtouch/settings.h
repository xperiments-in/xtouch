#ifndef _XLCD_SETTINGS
#define _XLCD_SETTINGS

void xtouch_settings_save(bool onlyRoot = false)
{
    DynamicJsonDocument doc(128);
    doc["backlight"] = xTouchConfig.xTouchBacklightLevel;
    doc["tftOff"] = xTouchConfig.xTouchTFTOFFValue;
    doc["tftInvert"] = xTouchConfig.xTouchTFTInvert;
    doc["ota"] = xTouchConfig.xTouchOTAEnabled;
    xtouch_filesystem_writeJson(SD, xtouch_paths_settings, doc);

    if (onlyRoot)
    {
        return;
    }

    DynamicJsonDocument printersSettings(128);
    printersSettings["chamberTemp"] = xTouchConfig.xTouchChamberSensorEnabled;
    printersSettings["auxFan"] = xTouchConfig.xTouchAuxFanEnabled;
    printersSettings["chamberFan"] = xTouchConfig.xTouchChamberFanEnabled;

    DynamicJsonDocument printers = xtouch_ssdp_load_printer();
    printers[xTouchConfig.xTouchSerialNumber]["settings"] = printersSettings;
    xtouch_filesystem_writeJson(SD, xtouch_paths_printers, printers);
}

void xtouch_settings_loadSettings()
{
    if (!xtouch_filesystem_exist(SD, xtouch_paths_settings))
    {
        DynamicJsonDocument doc(128);
        xTouchConfig.xTouchBacklightLevel = 128;
        xTouchConfig.xTouchTFTOFFValue = 15;
        xTouchConfig.xTouchTFTInvert = false;
        xTouchConfig.xTouchOTAEnabled = false;
        xtouch_settings_save(true);
    }

    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, xtouch_paths_settings);

    xTouchConfig.xTouchBacklightLevel = settings["backlight"].as<int>();
    xTouchConfig.xTouchTFTOFFValue = settings["tftOff"].as<int>();
    xTouchConfig.xTouchTFTInvert = settings["tftInvert"].as<bool>();
    xTouchConfig.xTouchOTAEnabled = settings["ota"].as<bool>();

    if (xtouch_ssdp_is_paired())
    {
        xtouch_ssdp_load_pair();
        JsonObject currentPrinterSettings = xtouch_ssdp_load_printer()[xTouchConfig.xTouchSerialNumber]["settings"];
        xTouchConfig.xTouchChamberSensorEnabled = currentPrinterSettings["chamberTemp"].as<bool>();
        xTouchConfig.xTouchAuxFanEnabled = currentPrinterSettings["auxFan"].as<bool>();
        xTouchConfig.xTouchChamberFanEnabled = currentPrinterSettings["chamberFan"].as<bool>();
    }
    else
    {
        xTouchConfig.xTouchChamberSensorEnabled = false;
        xTouchConfig.xTouchAuxFanEnabled = false;
        xTouchConfig.xTouchChamberFanEnabled = false;
    }

    bool isTFTFlipped = xtouch_screen_getTFTFlip();
    tft.setRotation(isTFTFlipped ? 3 : 1);
    x_touch_touchScreen.setRotation(isTFTFlipped ? 3 : 1);
    xtouch_screen_setBrightness(xTouchConfig.xTouchBacklightLevel);

    xtouch_screen_invertColors();
}

#endif
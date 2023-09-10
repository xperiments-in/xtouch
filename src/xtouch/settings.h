#ifndef _XLCD_SETTINGS
#define _XLCD_SETTINGS

void xtouch_settings_save()
{
    DynamicJsonDocument doc(128);
    doc["backlight"] = xTouchConfig.xTouchBacklightLevel;
    doc["tftOff"] = xTouchConfig.xTouchTFTOFFValue;
    doc["tftInvert"] = xTouchConfig.xTouchTFTInvert;
    doc["auxFan"] = xTouchConfig.xTouchAuxFanEnabled;
    doc["chamberTemp"] = xTouchConfig.xTouchChamberSensorEnabled;
    doc["ota"] = xTouchConfig.xTouchOTAEnabled;

    xtouch_filesystem_writeJson(SD, xtouch_paths_settings, doc);
}

void xtouch_settings_setup()
{
    if (!xtouch_filesystem_exist(SD, xtouch_paths_settings))
    {
        DynamicJsonDocument doc(128);
        xTouchConfig.xTouchBacklightLevel = 128;
        xTouchConfig.xTouchTFTOFFValue = 15;
        xTouchConfig.xTouchTFTInvert = false;
        xTouchConfig.xTouchAuxFanEnabled = false;
        xTouchConfig.xTouchChamberSensorEnabled = false;
        xTouchConfig.xTouchOTAEnabled = false;
        xtouch_settings_save();
    }

    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, xtouch_paths_settings);
    xTouchConfig.xTouchBacklightLevel = settings["backlight"].as<int>();
    xTouchConfig.xTouchTFTOFFValue = settings["tftOff"].as<int>();
    xTouchConfig.xTouchTFTInvert = settings["tftInvert"].as<bool>();
    xTouchConfig.xTouchAuxFanEnabled = settings["auxFan"].as<bool>();
    xTouchConfig.xTouchChamberSensorEnabled = settings["chamberTemp"].as<bool>();
    xTouchConfig.xTouchOTAEnabled = settings["ota"].as<bool>();
    xtouch_screen_setBrightness(xTouchConfig.xTouchBacklightLevel);

    bool isTFTFlipped = xtouch_screen_getTFTFlip();
    tft.setRotation(isTFTFlipped ? 3 : 1);
    x_touch_touchScreen.setRotation(isTFTFlipped ? 3 : 1);

    xtouch_screen_invertColors();
}

#endif
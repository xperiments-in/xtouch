#ifndef _XLCD_SETTINGS
#define _XLCD_SETTINGS

void xtouch_settings_save()
{

    DynamicJsonDocument doc(128);
    doc["backlight"] = xTouchConfig.xTouchBacklightLevel;
    doc["tftOff"] = xTouchConfig.xTouchTFTOFFValue;
    doc["tftInvert"] = xTouchConfig.xTouchTFTInvert;
    doc["tftFlip"] = xTouchConfig.xTouchTFTFlip;
    doc["auxFan"] = xTouchConfig.xTouchAuxFanEnabled;
    doc["chamberTemp"] = xTouchConfig.xTouchChamberSensorEnabled;

    Serial.println("xtouch_settings_save");
    Serial.println(xTouchConfig.xTouchTFTFlip);

    xtouch_eeprom_write(XTOUCH_EEPROM_POS_TFTFLIP, xTouchConfig.xTouchTFTFlip);
    xtouch_filesystem_writeJson(SD, settingsPath, doc);
}

void xtouch_settings_setup()
{
    if (!xtouch_filesystem_exist(SD, settingsPath))
    {
        DynamicJsonDocument doc(128);
        xTouchConfig.xTouchBacklightLevel = 128;
        xTouchConfig.xTouchTFTOFFValue = 15;
        xTouchConfig.xTouchTFTInvert = false;
        xTouchConfig.xTouchTFTFlip = false;
        xTouchConfig.xTouchAuxFanEnabled = false;
        xTouchConfig.xTouchChamberSensorEnabled = false;
        xtouch_settings_save();
    }

    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, settingsPath);
    xTouchConfig.xTouchBacklightLevel = settings["backlight"].as<int>();
    xTouchConfig.xTouchTFTOFFValue = settings["tftOff"].as<int>();
    xTouchConfig.xTouchTFTInvert = settings["tftInvert"].as<bool>();
    xTouchConfig.xTouchTFTFlip = settings["tftFlip"].as<bool>();
    xTouchConfig.xTouchAuxFanEnabled = settings["auxFan"].as<bool>();
    xTouchConfig.xTouchChamberSensorEnabled = settings["chamberTemp"].as<bool>();
    ledcAnalogWrite(LEDC_CHANNEL_0, settings["backlight"].as<int>());
    tft.setRotation(xTouchConfig.xTouchTFTFlip ? 3 : 1);
    x_touch_touchScreen.setRotation(xTouchConfig.xTouchTFTFlip ? 3 : 1);
    xtouch_screen_invert_setup();
}

#endif
#ifndef _XLCD_SETTINGS
#define _XLCD_SETTINGS

const char *settingsPath = "/settings.json";

void xtouch_settings_setup()
{
    if (!xtouch_filesystem_exist(SD, settingsPath))
    {
        DynamicJsonDocument doc(128);
        doc["backlight"] = 128;
        doc["tftOff"] = 15;
        doc["tftInvert"] = false;
        xtouch_filesystem_writeJson(SD, settingsPath, doc);
    }

    DynamicJsonDocument settings = xtouch_filesystem_readJson(SD, settingsPath);
    xTouchConfig.xTouchBacklightLevel = settings["backlight"].as<int>();
    xTouchConfig.xTouchTFTOFFValue = settings["tftOff"].as<int>();
    xTouchConfig.xTouchTFTInvert = settings["tftInvert"].as<bool>();
    ledcAnalogWrite(LEDC_CHANNEL_0, settings["backlight"].as<int>());

    xtouch_screen_invert_setup();
}

#endif
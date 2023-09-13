#ifndef _XLCD_SDCARD
#define _XLCD_SDCARD

#include "FS.h"
#include "SD.h"
#include <ArduinoJson.h>
#include <Arduino.h>

bool xtouch_sdcard_setup()
{
    if (!SD.begin())
    {
        lv_label_set_text(introScreenCaption, LV_SYMBOL_SD_CARD " INSERT SD CARD");
        lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();

        ConsoleError.println("[XTouch][SD] Card Mount Failed");
        return false;
    }

    lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        ConsoleError.println("[XTouch][SD] No SD card attached");
        return false;
    }

    ConsoleInfo.print("XTouch][SD] SD Card Type: ");

    if (cardType == CARD_MMC)
    {
        ConsoleInfo.println("[XTouch][SD] MMC");
    }
    else if (cardType == CARD_SD)
    {
        ConsoleInfo.println("[XTouch][SD] SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        ConsoleInfo.println("[XTouch][SD] SDHC");
    }
    else
    {
        ConsoleInfo.println("[XTouch][SD] UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    ConsoleInfo.printf("[XTouch][SD] SD Card Size: %lluMB\n", cardSize);
    xtouch_filesystem_mkdir(SD, xtouch_paths_root);

    return true;
}

#endif
#ifndef _XLCD_COLDBOOT
#define _XLCD_COLDBOOT

#ifdef ESP_IDF_VERSION_MAJOR // IDF 4+
#if CONFIG_IDF_TARGET_ESP32  // ESP32/PICO-D4
#include "esp32/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/rtc.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/rtc.h"
#else
#error Target CONFIG_IDF_TARGET is not supported
#endif
#else // ESP32 Before IDF 4.0
#include "rom/rtc.h"
#endif

// https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/ResetReason

#include <Arduino.h>

void xtouch_coldboot_check()
{
    if (rtc_get_reset_reason(0) == POWERON_RESET)
    {
        DynamicJsonDocument config = xtouch_filesystem_readJson(SD, xtouch_paths_config);
        int coldbootTimeout = config.containsKey("coldboot") ? config["coldboot"].as<int>() : 5000;
        lv_label_set_text(introScreenCaption, LV_SYMBOL_POWER);
        lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();
        delay(coldbootTimeout);
    }
}

#endif
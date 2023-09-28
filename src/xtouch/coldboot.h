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

enum ResetReason
{
    POWERON_RESET = 1,      /**<1,  Vbat power on reset*/
    SW_RESET = 3,           /**<3,  Software reset digital core*/
    OWDT_RESET,             /**<4,  Legacy watch dog reset digital core*/
    DEEPSLEEP_RESET,        /**<5,  Deep Sleep reset digital core*/
    SDIO_RESET,             /**<6,  Reset by SLC module, reset digital core*/
    TG0WDT_SYS_RESET,       /**<7,  Timer Group0 Watch dog reset digital core*/
    TG1WDT_SYS_RESET,       /**<8,  Timer Group1 Watch dog reset digital core*/
    RTCWDT_SYS_RESET,       /**<9,  RTC Watch dog Reset digital core*/
    INTRUSION_RESET,        /**<10, Instrusion tested to reset CPU*/
    TGWDT_CPU_RESET,        /**<11, Time Group reset CPU*/
    SW_CPU_RESET,           /**<12, Software reset CPU*/
    RTCWDT_CPU_RESET,       /**<13, RTC Watch dog Reset CPU*/
    EXT_CPU_RESET,          /**<14, for APP CPU, reseted by PRO CPU*/
    RTCWDT_BROWN_OUT_RESET, /**<15, Reset when the vdd voltage is not stable*/
    RTCWDT_RTC_RESET,       /**<16, RTC Watch dog reset digital core and rtc module*/

};

#include <Arduino.h>

void xtouch_coldboot_check()
{
    if (rtc_get_reset_reason(0) == POWERON_RESET)
    {
        DynamicJsonDocument wifiConfig = xtouch_filesystem_readJson(SD, xtouch_paths_wifi);
        int coldbootTimeout = wifiConfig.containsKey("coldboot") ? wifiConfig["coldboot"].as<int>() : 5000;
        lv_label_set_text(introScreenCaption, LV_SYMBOL_POWER);
        lv_obj_set_style_text_color(introScreenCaption, lv_color_hex(0x2aff00), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_timer_handler();
        delay(coldbootTimeout);
    }
}

#endif
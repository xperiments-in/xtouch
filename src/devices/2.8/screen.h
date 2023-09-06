#ifndef _XLCD_SCREEN
#define _XLCD_SCREEN

#include <TFT_eSPI.h>

#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI 23
#define SD_CS 5

#define SCREENTIMER 1000 * 60 * 3

static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#include "ui/ui.h"
#include "touch.h"
#include "xtouch/globals.h"

bool x_touch_read_from_power_off = false;

void xtouch_screen_setBackLedOff()
{
    pinMode(4, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(16, HIGH);
    digitalWrite(17, HIGH); // The LEDs are "active low", meaning HIGH == off, LOW == on
}

void xtouch_screen_onScreenOff(lv_timer_t *timer)
{
    digitalWrite(21, LOW);
    x_touch_read_from_power_off = true;
}

/* Display flushing */
void xtouch_screen_dispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void xtouch_screen_setupScreenTimer()
{
    xtouch_screen_onScreenOffTimer = lv_timer_create(xtouch_screen_onScreenOff, SCREENTIMER, NULL);
    lv_timer_pause(xtouch_screen_onScreenOffTimer);
}

void xtouch_screen_startScreenTimer()
{
    lv_timer_resume(xtouch_screen_onScreenOffTimer);
}

void xtouch_screen_touchRead(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

    if (x_touch_touchScreen.tirqTouched() && x_touch_touchScreen.touched())
    {
        lv_timer_reset(xtouch_screen_onScreenOffTimer);
        // dont pass first touch after power on
        if (x_touch_read_from_power_off)
        {
            x_touch_read_from_power_off = false;
            digitalWrite(21, HIGH);
            while (x_touch_touchScreen.touched())
                ;
            return;
        }

        // digitalWrite(21, HIGH);
        ScreenPoint sp = ScreenPoint();
        TS_Point p = x_touch_touchScreen.getPoint();
        sp = getScreenCoords(p.x, p.y);
        data->state = LV_INDEV_STATE_PR;
        data->point.x = sp.x;
        data->point.y = sp.y;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void xtouch_screen_setup()
{

    pinMode(XPT2046_CS, OUTPUT);
    pinMode(TFT_CS, OUTPUT);
    pinMode(SD_CS, OUTPUT);

    digitalWrite(XPT2046_CS, HIGH); // Touch controller chip select (if used)
    digitalWrite(TFT_CS, HIGH);     // TFT screen chip select
    digitalWrite(SD_CS, HIGH);      // SD card chips select, must use GPIO 5 (ESP32 SS)

    xtouch_screen_setBackLedOff();

    lv_init();

    tft.init();
    tft.setRotation(1);
    x_touch_spi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    x_touch_touchScreen.begin(x_touch_spi);
    x_touch_touchScreen.setRotation(1);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenHeight;
    disp_drv.ver_res = screenWidth;
    disp_drv.flush_cb = xtouch_screen_dispFlush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = xtouch_screen_touchRead;
    lv_indev_drv_register(&indev_drv);

    /*Initialize the graphics library */
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    initTopLayer();
}

#endif
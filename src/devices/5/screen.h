#ifndef _XLCD_SCREEN_5
#define _XLCD_SCREEN_5

/*
 * Display driver for the JC8048W550C (Guition ESP32-S3 5" 800×480)
 *
 * Display interface : RGB parallel (16-bit)
 * Display IC        : ST7262 (integrated RGB controller)
 * Touch controller  : GT911  (see touch.h)
 * Chip              : ESP32-S3 (16 MB flash, 8 MB OPI PSRAM)
 *
 * SD-card SPI pins on this board:
 *   CS   = GPIO10, MOSI = GPIO11, MISO = GPIO13, CLK = GPIO12
 *
 * Backlight:  GPIO2  (active-high PWM)
 */

#include <Arduino_GFX_Library.h>
#include <SPI.h>
#include "touch.h"
#include "xtouch/globals.h"

/* ── SD-card SPI ────────────────────────────────────────────────────── */
#define SD_CS   10
#define SD_MOSI 11
#define SD_MISO 13
#define SD_SCK  12

/* ── Backlight ──────────────────────────────────────────────────────── */
#define LCD_BACK_LIGHT_PIN 2
#define LEDC_CHANNEL_BL    0
#define LEDC_TIMER_12_BIT  12
#define LEDC_BASE_FREQ     5000

/* ── Screen resolution ──────────────────────────────────────────────── */
static const uint16_t screenWidth  = 800;
static const uint16_t screenHeight = 480;

/* ── RGB panel bus – JC8048W550C pin mapping ────────────────────────── *
 *  The ESP32-S3 RGB LCD peripheral drives the display directly;
 *  no SPI/I2C communication with a display IC is needed.
 *
 *  Timing values from the Guition / Jingcai datasheet:
 *    PCLK  16 MHz
 *    H: front_porch=210, sync_width=30, back_porch=16
 *    V: front_porch=22,  sync_width=13, back_porch=10
 * ─────────────────────────────────────────────────────────────────── */
Arduino_ESP32RGBPanel *_xtouch_rgb_bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS  */,
    GFX_NOT_DEFINED /* SCK */,
    GFX_NOT_DEFINED /* SDO */,
    40 /* DE    */,
    41 /* VSYNC */,
    39 /* HSYNC */,
    42 /* PCLK  */,
    /* R0..R4 */ 45, 48, 47, 21, 14,
    /* G0..G5 */  5,  6,  7, 15, 16,  4,
    /* B0..B4 */  8,  3, 46,  9,  1,
    /* hsync: polarity, front_porch, pulse_width, back_porch */
    0, 210, 30, 16,
    /* vsync: polarity, front_porch, pulse_width, back_porch */
    0,  22, 13, 10,
    /* pclk_active_neg */ true
);

/* ── GFX display object ─────────────────────────────────────────────── */
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    _xtouch_rgb_bus,
    GFX_NOT_DEFINED /* RST */,
    0               /* rotation */,
    true            /* auto_flush – let the RGB peripheral push pixels */,
    800, 480
);

/* ── Compatibility shim so settings.h can call tft.setRotation() ────── */
class _XTouchTFTCompat
{
public:
    void setRotation(uint8_t /*r*/) { /* RGB panel rotation handled elsewhere */ }
    void invertDisplay(bool /*inv*/) { /* RGB panels do not support HW inversion */ }
} tft;

/* ── LVGL draw buffer (in PSRAM when available) ─────────────────────── */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *_lv_buf1 = nullptr;
static lv_color_t *_lv_buf2 = nullptr;
/* Use ~1/10 of screen as LVGL buffer (80×480 pixels each) */
#define LVGL_BUF_LINES 48
#define LVGL_BUF_SIZE  (screenWidth * LVGL_BUF_LINES)

/* ── Screen-off timer (shared with rest of code) ────────────────────── */
bool xtouch_screen_touchFromPowerOff = false;

/* ── Backlight helpers ──────────────────────────────────────────────── */
static void _bl_analog_write(uint32_t value, uint32_t valueMax = 255)
{
    uint32_t duty = (4095 / valueMax) * min(value, valueMax);
    ledcWrite(LEDC_CHANNEL_BL, duty);
}

void xtouch_screen_setBrightness(byte brightness)
{
    _bl_analog_write(brightness);
}

/* ── Screen-sleep timer callbacks ───────────────────────────────────── */
void xtouch_screen_wakeUp()
{
    lv_timer_reset(xtouch_screen_onScreenOffTimer);
    xtouch_screen_touchFromPowerOff = false;
    loadScreen(0);
    xtouch_screen_setBrightness(xTouchConfig.xTouchBacklightLevel);
}

void xtouch_screen_onScreenOff(lv_timer_t * /*timer*/)
{
    if (xTouchConfig.xTouchTFTOFFValue < XTOUCH_LCD_MIN_SLEEP_TIME)
        return;
    ConsoleInfo.println("[XTouch][SCREEN5] Screen Off");
    xtouch_screen_setBrightness(0);
    xtouch_screen_touchFromPowerOff = true;
}

void xtouch_screen_setupScreenTimer()
{
    xtouch_screen_onScreenOffTimer =
        lv_timer_create(xtouch_screen_onScreenOff,
                        xTouchConfig.xTouchTFTOFFValue * 1000 * 60, NULL);
    lv_timer_pause(xtouch_screen_onScreenOffTimer);
}

void xtouch_screen_startScreenTimer()
{
    lv_timer_resume(xtouch_screen_onScreenOffTimer);
}

void xtouch_screen_setScreenTimer(uint32_t period)
{
    lv_timer_set_period(xtouch_screen_onScreenOffTimer, period);
}

/* No-op for RGB panels (no HW color inversion support) */
void xtouch_screen_invertColors() {}

/* ── Screen-flip (rotation) – stored in EEPROM ──────────────────────── */
byte xtouch_screen_getTFTFlip()
{
    byte val = xtouch_eeprom_read(XTOUCH_EEPROM_POS_TFTFLIP);
    xTouchConfig.xTouchTFTFlip = val;
    return val;
}

void xtouch_screen_setTFTFlip(byte mode)
{
    xTouchConfig.xTouchTFTFlip = mode;
    xtouch_eeprom_write(XTOUCH_EEPROM_POS_TFTFLIP, mode);
}

void xtouch_screen_toggleTFTFlip()
{
    xtouch_screen_setTFTFlip(!xtouch_screen_getTFTFlip());
    xtouch_resetTouchConfig();
}

void xtouch_screen_setupTFTFlip()
{
    /* Rotation via Arduino_GFX:
     *  0 = normal (landscape), 2 = 180° flip */
    byte flipped = xtouch_screen_getTFTFlip();
    gfx->setRotation(flipped ? 2 : 0);
    x_touch_touchScreen.setRotation(flipped ? TAMC_GT911_ROTATE_180
                                            : TAMC_GT911_ROTATE_0);
}

/* ── LVGL display flush callback ────────────────────────────────────── */
void xtouch_screen_dispFlush(lv_disp_drv_t *disp, const lv_area_t *area,
                              lv_color_t *color_p)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    /* LV_COLOR_16_SWAP is 0 → native RGB565 little-endian */
    gfx->draw16bitRGBBitmap(area->x1, area->y1,
                             (uint16_t *)&color_p->full, w, h);
    lv_disp_flush_ready(disp);
}

/* ── LVGL touch read callback ────────────────────────────────────────── */
void xtouch_screen_touchRead(lv_indev_drv_t * /*indev_driver*/,
                              lv_indev_data_t *data)
{
    x_touch_touchScreen.read();
    if (x_touch_touchScreen.isTouched && x_touch_touchScreen.touches > 0)
    {
        lv_timer_reset(xtouch_screen_onScreenOffTimer);

        if (xtouch_screen_touchFromPowerOff)
        {
            xtouch_screen_wakeUp();
            return;
        }

        data->state    = LV_INDEV_STATE_PR;
        data->point.x  = x_touch_touchScreen.points[0].x;
        data->point.y  = x_touch_touchScreen.points[0].y;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

/* ── Main screen setup ──────────────────────────────────────────────── */
void xtouch_screen_setup()
{
    ConsoleInfo.println("[XTouch][SCREEN5] Setup");

    /* Configure SPI bus for SD card before anything uses SD.begin() */
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    /* Backlight – start at full brightness for splash screen */
    ledcSetup(LEDC_CHANNEL_BL, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
    ledcAttachPin(LCD_BACK_LIGHT_PIN, LEDC_CHANNEL_BL);
    xtouch_screen_setBrightness(255);

    /* LVGL init */
    lv_init();

    /* GFX / RGB panel init */
    if (!gfx->begin(16000000UL /* PCLK 16 MHz */))
    {
        ConsoleError.println("[XTouch][SCREEN5] GFX begin failed!");
    }

    /* Allocate LVGL buffers – prefer PSRAM */
    _lv_buf1 = (lv_color_t *)heap_caps_malloc(
        LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    _lv_buf2 = (lv_color_t *)heap_caps_malloc(
        LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

    if (!_lv_buf1 || !_lv_buf2)
    {
        /* Fall back to internal RAM with a smaller buffer */
        ConsoleError.println("[XTouch][SCREEN5] PSRAM alloc failed, using internal RAM");
        static lv_color_t _fallback_buf[screenWidth * 10];
        lv_disp_draw_buf_init(&draw_buf, _fallback_buf, NULL, screenWidth * 10);
    }
    else
    {
        lv_disp_draw_buf_init(&draw_buf, _lv_buf1, _lv_buf2, LVGL_BUF_SIZE);
    }

    /* Register display driver */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = screenWidth;
    disp_drv.ver_res  = screenHeight;
    disp_drv.flush_cb = xtouch_screen_dispFlush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register touch input driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = xtouch_screen_touchRead;
    lv_indev_drv_register(&indev_drv);

    /* Apply stored rotation */
    xtouch_screen_setupTFTFlip();

    /* LVGL theme */
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
    lv_disp_t   *dispp = lv_disp_get_default();
    lv_theme_t  *theme = lv_theme_default_init(
        dispp,
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_RED),
        true /* dark mode */,
        LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    initTopLayer();
}

#endif /* _XLCD_SCREEN_5 */

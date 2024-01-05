#ifndef _XLCD_SCREEN
#define _XLCD_SCREEN

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// SETUP LGFX PARAMETERS FOR WT32-SC01-PLUS
class LGFX : public lgfx::LGFX_Device
{

lgfx::Panel_ST7796      _panel_instance;
lgfx::Bus_Parallel8     _bus_instance;   
lgfx::Light_PWM         _light_instance;
lgfx::Touch_FT5x06      _touch_instance; // FT5206, FT5306, FT5406, FT6206, FT6236, FT6336, FT6436

public:
  LGFX(void)
  {
    { 
      auto cfg = _bus_instance.config();

      cfg.freq_write = 20000000;    
      cfg.pin_wr = 47; // pin number connecting WR
      cfg.pin_rd = -1; // pin number connecting RD
      cfg.pin_rs = 0;  // Pin number connecting RS(D/C)
      cfg.pin_d0 = 9;  // pin number connecting D0
      cfg.pin_d1 = 46; // pin number connecting D1
      cfg.pin_d2 = 3;  // pin number connecting D2
      cfg.pin_d3 = 8;  // pin number connecting D3
      cfg.pin_d4 = 18; // pin number connecting D4
      cfg.pin_d5 = 17; // pin number connecting D5
      cfg.pin_d6 = 16; // pin number connecting D6
      cfg.pin_d7 = 15; // pin number connecting D7
      //cfg.i2s_port = I2S_NUM_0; // (I2S_NUM_0 or I2S_NUM_1)

      _bus_instance.config(cfg);                    // Apply the settings to the bus.
      _panel_instance.setBus(&_bus_instance);       // Sets the bus to the panel.
    }

    { // Set display panel control.
      auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

      cfg.pin_cs = -1;   // Pin number to which CS is connected (-1 = disable)
      cfg.pin_rst = 4;   // pin number where RST is connected (-1 = disable)
      cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

      // * The following setting values â€‹â€‹are set to general default values â€‹â€‹for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

      cfg.memory_width = 320;  // Maximum width supported by driver IC
      cfg.memory_height = 480; // Maximum height supported by driver IC
      cfg.panel_width = 320;   // actual displayable width
      cfg.panel_height = 480;  // actual displayable height
      cfg.offset_x = 0;        // Panel offset in X direction
      cfg.offset_y = 0;        // Panel offset in Y direction
      cfg.offset_rotation = 0;  // was 2
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;     // was false
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true; // was false something to do with SD?

      _panel_instance.config(cfg);
    }

    { // Set backlight control. (delete if not necessary)
      auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

      cfg.pin_bl = 45;     // pin number to which the backlight is connected
      cfg.invert = false;  // true to invert backlight brightness
      cfg.freq = 44100;    // backlight PWM frequency
      cfg.pwm_channel = 0; // PWM channel number to use (7??)

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
    }

    { // Configure settings for touch screen control. (delete if not necessary)
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;   // Minimum X value (raw value) obtained from the touchscreen
      cfg.x_max = 319; // Maximum X value (raw value) obtained from the touchscreen
      cfg.y_min = 0;   // Minimum Y value obtained from touchscreen (raw value)
      cfg.y_max = 479; // Maximum Y value (raw value) obtained from the touchscreen
      cfg.pin_int = 7; // pin number to which INT is connected
      cfg.bus_shared = false; // set true if you are using the same bus as the screen
      cfg.offset_rotation = 0;

      // For I2C connection
      cfg.i2c_port = 0;    // Select I2C to use (0 or 1)
      cfg.i2c_addr = 0x38; // I2C device address number
      cfg.pin_sda = 6;     // pin number where SDA is connected
      cfg.pin_scl = 5;     // pin number to which SCL is connected
      cfg.freq = 400000;   // set I2C clock

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
    }

    setPanel(&_panel_instance); // Sets the panel to use.
  }
};

// TBD static const uint16_t screenWidth = 240;
// TBD static const uint16_t screenHeight = 320;

#define screenWidth 480
#define screenHeight 320

static lv_disp_draw_buf_t draw_buf; 
static lv_color_t buf[screenWidth * 10];

LGFX tft;

#include "ui/ui.h"
#include "touch.h"
#include "xtouch/globals.h"

bool xtouch_screen_touchFromPowerOff = false;

void xtouch_screen_setBrightness(byte brightness)
{
    tft.setBrightness(brightness);
}

void xtouch_screen_setBackLedOff()
{
    // TBD!!!
    //pinMode(4, OUTPUT);
    //pinMode(16, OUTPUT);
    //pinMode(17, OUTPUT);
    //digitalWrite(4, HIGH);
    //digitalWrite(16, HIGH);
    //digitalWrite(17, HIGH); // The LEDs are "active low", meaning HIGH == off, LOW == on
}

void xtouch_screen_wakeUp()
{
    lv_timer_reset(xtouch_screen_onScreenOffTimer);
    xtouch_screen_touchFromPowerOff = false;
    loadScreen(0);
    xtouch_screen_setBrightness(xTouchConfig.xTouchBacklightLevel);
}

void xtouch_screen_onScreenOff(lv_timer_t *timer)
{
    if (bambuStatus.print_status == XTOUCH_PRINT_STATUS_RUNNING)
    {
        return;
    }

    if (xTouchConfig.xTouchTFTOFFValue < XTOUCH_LCD_MIN_SLEEP_TIME)
    {
        return;
    }

    ConsoleInfo.println("[XTouch][SCREEN] Screen Off");
    xtouch_screen_setBrightness(0);
    xtouch_screen_touchFromPowerOff = true;
}

void xtouch_screen_setupScreenTimer()
{
    xtouch_screen_onScreenOffTimer = lv_timer_create(xtouch_screen_onScreenOff, xTouchConfig.xTouchTFTOFFValue * 1000 * 60, NULL);
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

void xtouch_screen_invertColors()
{
    tft.invertDisplay(xTouchConfig.xTouchTFTInvert);
}

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
    byte eepromTFTFlip = xtouch_screen_getTFTFlip();
    tft.setRotation(eepromTFTFlip == 1 ? 3 : 1);
    // TBD x_touch_touchScreen.setRotation(eepromTFTFlip == 1 ? 3 : 1);
}

void xtouch_screen_dispFlush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void xtouch_screen_touchRead(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;
    bool touched = tft.getTouch(&touchX, &touchY);
    if (touched)
    {
        lv_timer_reset(xtouch_screen_onScreenOffTimer);
        // dont pass first touch after power on
        if (xtouch_screen_touchFromPowerOff)
        {
            xtouch_screen_wakeUp();
            while (tft.getTouch(&touchX, &touchY))
                ;
            return;
        }

        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
  
        #if DEBUG_TOUCH !=0
        Serial.print( "Data x " ); Serial.println( touchX );
        Serial.print( "Data y " ); Serial.println( touchY );
        #endif
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void xtouch_screen_setup()
{

    ConsoleInfo.println("[XTouch][SCREEN] Setup");

    xtouch_screen_setBackLedOff();

    tft.begin();

    xtouch_screen_setupTFTFlip();

    xtouch_screen_setBrightness(255);

    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = xtouch_screen_dispFlush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the input device driver*/
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
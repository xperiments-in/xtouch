#ifndef _XLCD_TOUCH_5
#define _XLCD_TOUCH_5

/*
 * Touch driver for the JC8048W550C (Guition ESP32-S3 5" display)
 * Touch controller: GT911 (capacitive, I2C)
 *
 * Default I2C pins on this board:
 *   SDA  = GPIO19  (also USB D-)
 *   SCL  = GPIO20  (also USB D+)
 *   INT  = GPIO18  (only available if board R17 solder-bridge is closed)
 *   RST  = -1      (not connected to a GPIO, held HIGH via pull-up)
 *
 * If R17 is NOT bridged the INT pin is floating; the driver falls back to
 * I2C polling (slightly higher CPU load but fully functional).
 */

#include <Wire.h>
#include <TAMC_GT911.h>

/* ── GT911 pin definitions ────────────────────────────────────────────── */
#define TOUCH_SDA    19
#define TOUCH_SCL    20
#define TOUCH_INT    18   /* set to -1 if R17 is not bridged */
#define TOUCH_RST    (-1) /* not connected */

#define TOUCH_WIDTH  800
#define TOUCH_HEIGHT 480

/* ── Global GT911 instance ────────────────────────────────────────────── */
TAMC_GT911 x_touch_touchScreen(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST,
                                TOUCH_WIDTH, TOUCH_HEIGHT);

/* ── Compatibility shim used by settings.h ─────────────────────────────
 * settings.h calls  x_touch_touchScreen.setRotation(val)
 * TAMC_GT911 already provides setRotation(), so nothing extra is needed.
 * ───────────────────────────────────────────────────────────────────── */

void xtouch_touch_setup()
{
    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    x_touch_touchScreen.begin();
    x_touch_touchScreen.setRotation(TAMC_GT911_ROTATE_0);
}

/* Called from settings.h when the user toggles screen flip.
 * On the 5" board we don't store a separate touch calibration
 * so this is intentionally empty. */
void xtouch_resetTouchConfig() {}

#endif /* _XLCD_TOUCH_5 */

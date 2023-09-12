#ifndef _XLCD_DEBUG
#define _XLCD_DEBUG

#define XTOUCH_USE_SERIAL true
#define XTOUCH_DEBUG_INFO false
#define XTOUCH_DEBUG_WARNING false
#define XTOUCH_DEBUG_ERROR false
#define ConsoleLog if(XTOUCH_USE_SERIAL)Serial
#define ConsoleInfo if(XTOUCH_DEBUG_INFO)Serial
#define ConsoleWarn if(XTOUCH_DEBUG_WARNING)Serial
#define ConsoleError if(XTOUCH_DEBUG_ERROR)Serial

#include <Arduino.h>

void xtouch_debug_setup()
{
#if XTOUCH_USE_SERIAL == true || XTOUCH_DEBUG_ERROR == true || XTOUCH_DEBUG_WARNING == true || XTOUCH_DEBUG_INFO == true
    Serial.begin(115200);
    while (!Serial)
        ;
#endif
}

#endif

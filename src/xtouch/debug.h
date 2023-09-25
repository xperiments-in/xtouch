#ifndef _XLCD_DEBUG
#define _XLCD_DEBUG

#define XTOUCH_DEBUG_LOG true
#define XTOUCH_DEBUG_INFO true
#define XTOUCH_DEBUG_DEBUG true
#define XTOUCH_DEBUG_ERROR XTOUCH_DEBUG_LOG || XTOUCH_DEBUG_INFO || XTOUCH_DEBUG_DEBUG

#define ConsoleLog                                                                         \
    if (XTOUCH_DEBUG_LOG || XTOUCH_DEBUG_INFO || XTOUCH_DEBUG_DEBUG || XTOUCH_DEBUG_ERROR) \
    Serial
#define ConsoleInfo                                                    \
    if (XTOUCH_DEBUG_INFO || XTOUCH_DEBUG_DEBUG || XTOUCH_DEBUG_ERROR) \
    Serial
#define ConsoleDebug                              \
    if (XTOUCH_DEBUG_DEBUG || XTOUCH_DEBUG_ERROR) \
    Serial
#define ConsoleError        \
    if (XTOUCH_DEBUG_ERROR) \
    Serial

#include <Arduino.h>
#include <ArduinoJson.h>

void xtouch_debug_json(const JsonDocument &doc)
{
#if XTOUCH_DEBUG_DEBUG == true
    String output;
    serializeJsonPretty(doc, output);
    ConsoleDebug.println(output);
#endif
}

#endif

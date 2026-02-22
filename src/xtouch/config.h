#ifndef _XLCD_JSONCONFIG
#define _XLCD_JSONCONFIG

#include <ArduinoJson.h>
#include "filesystem.h"
#include "paths.h"

/*
  Local mode (default – direct LAN connection to the printer):
  {
    "ssid": "MyWifi",
    "pwd":  "secret",
    "timeout":  "3000",
    "coldboot": "5000",
    "mqtt": {
      "host":         "192.168.1.42",
      "accessCode":   "12345678",
      "serialNumber": "01S00C342600288",
      "printerModel": "P1P",
      "lanMode":      "local"
    }
  }

  Cloud mode (Bambulab Cloud MQTT):
  Choose the "host" that matches the region of your Bambulab account:
    EU region  → eu.mqtt.bambulab.com
    US region  → us.mqtt.bambulab.com
    CN region  → cn.mqtt.bambulab.com

  {
    "ssid": "MyWifi",
    "pwd":  "secret",
    "mqtt": {
      "host":         "eu.mqtt.bambulab.com",
      "accessCode":   "<your_bambulab_access_token>",
      "userId":       "<your_bambulab_user_id>",
      "serialNumber": "01S00C342600288",
      "printerModel": "P1P",
      "lanMode":      "cloud"
    }
  }

  Get accessCode and userId from:
    https://bambulab.com/api/v1/iot-service/api/user/bind
  (log in to bambulab.com first, then call the API in your browser)
*/
DynamicJsonDocument xtouch_load_config()
{
    DynamicJsonDocument config = xtouch_filesystem_readJson(SD, xtouch_paths_config);

    strcpy(xTouchConfig.xTouchAccessCode,   config["mqtt"]["accessCode"].as<const char *>());
    strcpy(xTouchConfig.xTouchSerialNumber, config["mqtt"]["serialNumber"].as<const char *>());
    strcpy(xTouchConfig.xTouchHost,         config["mqtt"]["host"].as<const char *>());
    strcpy(xTouchConfig.xTouchPrinterModel, config["mqtt"]["printerModel"].as<const char *>());

    /* ── Cloud fields (optional – default to local mode) ────────────── */
    const char *lanMode = config["mqtt"]["lanMode"].as<const char *>();
    strcpy(xTouchConfig.xTouchLanMode,
           (lanMode && strlen(lanMode) > 0) ? lanMode : "local");

    const char *userId = config["mqtt"]["userId"].as<const char *>();
    strcpy(xTouchConfig.xTouchUserId,
           (userId && strlen(userId) > 0) ? userId : "");

    return xtouch_filesystem_readJson(SD, xtouch_paths_config);
}

#endif
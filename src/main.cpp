#include <Arduino.h>
#include <ArduinoJson.h>
#include "xtouch/types.h"
#include "xtouch/globals.h"
#include "xtouch/filesystem.h"
#include "ui/ui.h"
#include "screens/intro.h"
#include "xtouch/sdcard.h"
#include "xtouch/hms.h"
#include "xtouch/ssdp.h"

#if defined(__XTOUCH_SCREEN_28__)
#include "devices/2.8/screen.h"
#endif

#include "xtouch/pair.h"
#include "xtouch/mqtt.h"
#include "xtouch/events.h"
#include "xtouch/connection.h"

void setup()
{

  Serial.begin(115200);

  xtouch_globals_init();

  xtouch_screen_setup();

  xtouch_intro_show();

  while (!xtouch_sdcard_setup())
    ;

  xtouch_ssdp_clear_device_list();

  while (!xtouch_wifi_setup())
    ;

  xtouch_touch_setup();

  xtouch_screen_setupScreenTimer();
  xtouch_setupGlobalEvents();

  xtouch_ssdp_start();

  if (!xtouch_ssdp_is_paired())
  {
    xtouch_pair_start();
  }
  else
  {
    xtouch_ssdp_load_pair();
  }

  xtouch_intro_show();
  xtouch_mqtt_setup();
}

void loop()
{
  lv_timer_handler();
  lv_task_handler();
  xtouch_mqtt_loop();
}

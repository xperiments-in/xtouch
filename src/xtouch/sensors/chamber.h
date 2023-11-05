#ifndef _XLCD_SENSORS_CHAMBER_TEMP
#define _XLCD_SENSORS_CHAMBER_TEMP

#include <OneWire.h>
#include <DallasTemperature.h>

#define XTOUCH_CHAMBER_TEMP_PIN 22

// Setup a temperatureSensorsOneWire instance to communicate with any temperatureSensorsOneWire devices
OneWire temperatureSensorsOneWire(XTOUCH_CHAMBER_TEMP_PIN);

// Pass our temperatureSensorsOneWire reference to Dallas Temperature sensor
DallasTemperature xtouch_chamber_sensors(&temperatureSensorsOneWire);

lv_timer_t *xtouch_chambertemp_requestTemperaturesTimer;

void xtouch_chamber_requestTemperatures(lv_timer_t *timer);

void xtouch_chamber_timer_create()
{
    xtouch_chambertemp_requestTemperaturesTimer = lv_timer_create(xtouch_chamber_requestTemperatures, 2500, NULL);
    lv_timer_set_repeat_count(xtouch_chambertemp_requestTemperaturesTimer, 1);
}

void xtouch_chamber_requestTemperatures(lv_timer_t *timer)
{
    int temperatureC = xtouch_chamber_sensors.getTempCByIndex(0) + xTouchConfig.xTouchChamberSensorReadingDiff;
    bambuStatus.chamber_temper = temperatureC;
    xtouch_mqtt_sendMsg(XTOUCH_ON_CHAMBER_TEMP, temperatureC);
    xtouch_chamber_sensors.requestTemperatures();
    xtouch_chamber_timer_create();
}

bool xtouch_chamber_started = false;
void xtouch_chamber_timer_start()
{
    if (!xtouch_chamber_started)
    {
        xtouch_chamber_sensors.begin();
        xtouch_chamber_sensors.setWaitForConversion(false);
        xtouch_chamber_started = true;
    }
    xtouch_chamber_timer_create();
}

void xtouch_chamber_timer_stop()
{
    lv_timer_pause(xtouch_chambertemp_requestTemperaturesTimer);
}

void xtouch_chamber_timer_init()
{
    if (!xtouch_bblp_is_p1Series())
    {
        return;
    }

    if (xTouchConfig.xTouchChamberSensorEnabled)
    {
        xtouch_chamber_timer_start();
    }
    else
    {
        if (xtouch_chamber_started)
        {

            xtouch_chamber_timer_stop();
        }
    }
}

#endif

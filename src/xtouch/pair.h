#ifndef _XLCD_PAIR
#define _XLCD_PAIR

#include <WiFi.h>

bool xtouch_pair_loop_exit = false;

void xtouch_pair_start()
{
    xtouch_ssdp_setupButtonTimer();
    xtouch_pair_loop_exit = false;
    loadScreen(5);
    while (!xtouch_pair_loop_exit)
    {
        xtouch_ssdp_loop();
        lv_timer_handler();
        lv_task_handler();
    }

    String storedCode = xtouch_ssdp_getStoredCode(xTouchConfig.xTouchSerialNumber);

    if (storedCode.length() > 0)
    {
        strcpy(xTouchConfig.xTouchAccessCode, storedCode.c_str());
    }
    else
    {
        xtouch_pair_loop_exit = false;
        loadScreen(6);
        while (!xtouch_pair_loop_exit)
        {
            lv_timer_handler();
            lv_task_handler();
        }
    }
}

void xtouch_pair_init()
{
    xtouch_ssdp_start();
    xtouch_pair_start();
    loadScreen(-1);
    xtouch_ssdp_stop();
    xtouch_ssdp_save_pair(xTouchConfig.xTouchSerialNumber, xTouchConfig.xTouchAccessCode);
}

bool xtouch_pair_isPortAlive(const char *host, int port)
{
    WiFiClient client;
    if (client.connect(host, port))
    {
        client.stop();
        return true;
    }
    return false;
}

bool xtouch_pair_checkPrinterPorts(const char *host, const int *ports, int numPorts)
{
    // https://wiki.bambulab.com/en/general/printer-network-ports

    for (int i = 0; i < numPorts; i++)
    {
        if (xtouch_pair_isPortAlive(host, ports[i]))
        {
            return true; // If at least one port is open, consider it a success
        }
    }
    return false; // Both ports are closed, consider it a failure
}

void xtouch_pair_check()
{
    if (!xtouch_ssdp_is_paired())
    {
        xtouch_pair_init();
    }

    xtouch_ssdp_load_pair();

    IPAddress ip;
    JsonDocument printerIps = xtouch_ssdp_load_printerIPs();
    ip.fromString(printerIps[xTouchConfig.xTouchSerialNumber].as<String>());

    const int ports[] = {1883, 8883};
    if (!xtouch_pair_checkPrinterPorts(printerIps[xTouchConfig.xTouchSerialNumber].as<String>().c_str(), ports, 2))
    {
        xtouch_ssdp_clear_printerIPs();
        delay(2000);
        ESP.restart();
    }
}

#endif
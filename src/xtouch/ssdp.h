#ifndef _XLCD_SSDP
#define _XLCD_SSDP

#include <WiFi.h>
#include <WiFiUdp.h>

#define XTOUCH_SSDP_SEARCH_TIME 15000
#define XTOUCH_SSDP_PACKET_SIZE 512
#define XTOUCH_SSDP_UDP_PORT 2021
#define XTOUCH_SSDP_MAX_DEVICES 20

// StaticJsonDocument<512> xtouch_ssdp_deviceList[XTOUCH_SSDP_MAX_DEVICES];
WiFiUDP xtouch_ssdp_udp;

char xtouch_ssdp_packetBuffer[XTOUCH_SSDP_PACKET_SIZE];
int xtouch_ssdp_search_count = 0;

JsonDocument xtouch_ssdp_load_printer()
{
    return xtouch_filesystem_readJson(SD, xtouch_paths_printers, false);
}

JsonDocument xtouch_ssdp_load_printerIPs()
{
    return xtouch_filesystem_readJson(SD, xtouch_paths_printer_ips, false);
}

bool xtouch_ssdp_clear_printerIPs()
{
    return xtouch_filesystem_deleteFile(SD, xtouch_paths_printer_ips);
}

void xtouch_ssdp_clear_device_list()
{
    JsonDocument pairDoc;
    xtouch_filesystem_writeJson(SD, xtouch_paths_printers, pairDoc);
}

void xtouch_ssdp_clear_pair_list()
{
    xtouch_filesystem_deleteFile(SD, xtouch_paths_pair);
}

bool xtouch_ssdp_is_paired()
{
    JsonDocument printerIps = xtouch_ssdp_load_printerIPs();
    JsonDocument pairDoc = xtouch_filesystem_readJson(SD, xtouch_paths_pair, false);

    if (pairDoc.isNull() || printerIps.isNull())
    {
        return false;
    }

    if (pairDoc.containsKey("paired"))
    {

        String pairedSN = pairDoc["paired"].as<String>();
        if (pairDoc.containsKey(pairedSN))
        {
            JsonDocument pairDevices = xtouch_filesystem_readJson(SD, xtouch_paths_printers, false);
            if (pairDevices.containsKey(pairedSN))
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

String xtouch_ssdp_getStoredCode(String usn)
{
    JsonDocument pairDoc = xtouch_filesystem_readJson(SD, xtouch_paths_pair, false);
    if (pairDoc.containsKey(usn))
    {
        return pairDoc[usn].as<String>();
    }
    return "";
};

void xtouch_ssdp_load_pair()
{
    JsonDocument pairFile = xtouch_filesystem_readJson(SD, xtouch_paths_pair, false);
    JsonDocument printers = xtouch_ssdp_load_printer();
    String usn = pairFile["paired"].as<String>();
    String name = printers[usn]["name"].as<String>();
    strcpy(xTouchConfig.xTouchSerialNumber, pairFile["paired"].as<String>().c_str());
    strcpy(xTouchConfig.xTouchAccessCode, pairFile[usn].as<String>().c_str());
    strcpy(xTouchConfig.xTouchPrinterName, name.c_str());
}

void xtouch_ssdp_unpair()
{
    ConsoleInfo.println("[XTOUCH][SSDP] Unpairing device");
    JsonDocument pairFile = xtouch_filesystem_readJson(SD, xtouch_paths_pair, false);
    pairFile.remove("paired");
    xtouch_filesystem_writeJson(SD, xtouch_paths_pair, pairFile);
    ESP.restart();
}

void xtouch_ssdp_save_pair(String usn, String accessCode)
{
    ConsoleInfo.println("[XTOUCH][SSDP] Saving AccessCode Pair");
    JsonDocument doc = xtouch_filesystem_readJson(SD, xtouch_paths_pair, false);

    doc["paired"] = usn.c_str();
    doc[usn] = accessCode.c_str();

    xtouch_filesystem_writeJson(SD, xtouch_paths_pair, doc);
}

void xtouch_ssdp_parseResponse(String input)
{
    JsonDocument doc;
    int startPos = 0;
    int endPos = 0;
    String keyIndex;
    String ip;
    bool isEmptyDoc = true;
    while (endPos < input.length())
    {
        endPos = input.indexOf('\n', startPos);
        if (endPos == -1)
        {
            endPos = input.length();
        }
        String line = input.substring(startPos, endPos);

        // Parse each line and extract key-value pair
        int colonPos = line.indexOf(':');
        if (colonPos != -1)
        {
            String key = line.substring(0, colonPos);
            String value = line.substring(colonPos + 1);

            key.trim();
            key.toLowerCase();
            value.trim();

            // Check if the key is one of the desired keys
            if (key == "location" || key == "usn" || key == "devmodel.bambu.com" || key == "devconnect.bambu.com" || key == "devbind.bambu.com" || key == "devname.bambu.com")
            {
                isEmptyDoc = false;
                if (key == "devname.bambu.com")
                {
                    key = "name";
                }
                if (key == "devmodel.bambu.com")
                {
                    key = "model";
                }
                else if (key == "devconnect.bambu.com")
                {
                    key = "lanMode";
                }
                else if (key == "devbind.bambu.com")
                {
                    key = "bind";
                }
                else if (key == "usn")
                {
                    key = "usn";
                    keyIndex = value;
                }
                else if (key == "location")
                {
                    key = "ip";
                    ip = value;
                }

                doc[key] = value;
            }
        }

        startPos = endPos + 1;
    }

    JsonDocument printerIPs = xtouch_ssdp_load_printerIPs();
    printerIPs[keyIndex] = ip;
    xtouch_filesystem_writeJson(SD, xtouch_paths_printer_ips, printerIPs);

    JsonDocument printers = xtouch_ssdp_load_printer();
    if (!isEmptyDoc && !printers.containsKey(keyIndex))
    {
        doc.remove("ip");
        printers[keyIndex] = doc;
        xtouch_filesystem_writeJson(SD, xtouch_paths_printers, printers);
    }
}

void xtouch_ssdp_loop()
{
    int packetSize = xtouch_ssdp_udp.parsePacket();
    if (packetSize)
    {
        int len = xtouch_ssdp_udp.read(xtouch_ssdp_packetBuffer, sizeof(xtouch_ssdp_packetBuffer));
        if (len > 0)
        {
            xtouch_ssdp_packetBuffer[len] = 0;
        }
        xtouch_ssdp_parseResponse(xtouch_ssdp_packetBuffer);
    }
}

void xtouch_ssdp_onButtonTimer(lv_timer_t *timer);

void xtouch_ssdp_setupButtonTimer()
{
    xtouch_ssdp_onButtonTimerTimer = lv_timer_create(xtouch_ssdp_onButtonTimer, XTOUCH_SSDP_SEARCH_TIME, NULL);
    lv_timer_set_repeat_count(xtouch_ssdp_onButtonTimerTimer, 1);
}

void xtouch_ssdp_onButtonTimer(lv_timer_t *timer)
{
    JsonDocument printers = xtouch_ssdp_load_printer();
    String output = "";
    for (JsonPair keyValue : printers.as<JsonObject>())
    {
        String name = keyValue.value()["name"].as<String>();
        output = output + LV_SYMBOL_CHARGE + " " + name + "   " + LV_SYMBOL_USB + " " + keyValue.key().c_str() + "\n";
    }

    if (!output.isEmpty())
    {
        output.remove(output.length() - 1);
        lv_roller_set_options(ui_printerPairScreenRoller, output.c_str(), LV_ROLLER_MODE_NORMAL);
        lv_obj_clear_flag(ui_printerPairScreenSubmitButton, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        xtouch_ssdp_search_count++;
        String a = String(LV_SYMBOL_CHARGE " Printer Search. Please wait...(") + xtouch_ssdp_search_count + ")";
        lv_roller_set_options(ui_printerPairScreenRoller, LV_SYMBOL_CHARGE " Printer Search. Please wait...", LV_ROLLER_MODE_NORMAL);
        xtouch_ssdp_setupButtonTimer();
    }
}

void xtouch_ssdp_start()
{
    xtouch_ssdp_udp.begin(XTOUCH_SSDP_UDP_PORT);
}

void xtouch_ssdp_stop()
{
    xtouch_ssdp_udp.stop();
}

#endif
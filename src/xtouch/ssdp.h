#ifndef _XLCD_SSDP
#define _XLCD_SSDP

#include <WiFi.h>
#include <WiFiUdp.h>
#define XTOUCH_SSDP_PACKET_SIZE 512
#define XTOUCH_SSDP_UDP_PORT 2021
#define XTOUCH_SSDP_MAX_DEVICES 20

// StaticJsonDocument<512> xtouch_ssdp_deviceList[XTOUCH_SSDP_MAX_DEVICES];
WiFiUDP xtouch_ssdp_udp;

char xtouch_ssdp_packetBuffer[XTOUCH_SSDP_PACKET_SIZE];
bool xtouch_ssdp_loop_exit = false;
const char *xtouch_ssdp_devices = "/ssdp-devices.json";
const char *xtouch_ssdp_pair = "/ssdp-pair.json";

DynamicJsonDocument xtouch_ssdp_load()
{
    return xtouch_filesystem_readJson(SD, xtouch_ssdp_devices, false);
}

void xtouch_ssdp_clear_devices()
{
    DynamicJsonDocument pairDoc(32);
    xtouch_filesystem_writeJson(SD, xtouch_ssdp_devices, pairDoc);
}

bool xtouch_ssdp_is_paired()
{
    DynamicJsonDocument pairDoc = xtouch_filesystem_readJson(SD, xtouch_ssdp_pair, false);
    if (pairDoc.isNull())
    {
        Serial.println("Pair file is null");
        return false;
    }

    if (pairDoc.containsKey("paired"))
    {

        String pairedSN = pairDoc["paired"].as<String>();
        if (pairDoc.containsKey(pairedSN))
        {
            DynamicJsonDocument pairDevices = xtouch_filesystem_readJson(SD, xtouch_ssdp_devices, false);
            if (pairDevices.containsKey(pairedSN) && pairDevices[pairedSN].containsKey("ip"))
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
    DynamicJsonDocument pairDoc = xtouch_filesystem_readJson(SD, xtouch_ssdp_pair, false);
    if (pairDoc.containsKey(usn))
    {
        return pairDoc[usn].as<String>();
    }
    return "";
};

void xtouch_ssdp_load_pair()
{
    DynamicJsonDocument pairFile = xtouch_filesystem_readJson(SD, xtouch_ssdp_pair, false);
    String usn = pairFile["paired"].as<String>();
    strcpy(xTouchConfig.xTouchSerialNumber, pairFile["paired"].as<String>().c_str());
    strcpy(xTouchConfig.xTouchAccessCode, pairFile[usn].as<String>().c_str());
}

void xtouch_ssdp_unpair()
{
    Serial.println("Unpairing device");
    DynamicJsonDocument pairFile = xtouch_filesystem_readJson(SD, xtouch_ssdp_pair, false);
    pairFile.remove("paired");
    xtouch_filesystem_writeJson(SD, xtouch_ssdp_pair, pairFile);
    ESP.restart();
}

void xtouch_ssdp_save_pair(String usn, String accessCode)
{
    Serial.println("Saving pair");
    Serial.println(usn);
    Serial.println(accessCode);
    DynamicJsonDocument pairFile = xtouch_filesystem_readJson(SD, xtouch_ssdp_pair, false);

    pairFile["paired"] = usn;
    pairFile[usn] = accessCode;

    xtouch_filesystem_writeJson(SD, xtouch_ssdp_pair, pairFile);
}

void xtouch_ssdp_parseResponse(String input)
{
    StaticJsonDocument<512> doc;
    // Split input into lines
    int startPos = 0;
    int endPos = 0;
    String keyIndex;
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
            if (key == "location" || key == "usn" || key == "devmodel.bambu.com" || key == "devconnect.bambu.com" || key == "devbind.bambu.com")
            {
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
                }
                // Store key-value pair in JSON document
                doc[key] = value;
            }
        }

        startPos = endPos + 1;
    }

    DynamicJsonDocument ssdpjson = xtouch_ssdp_load();
    serializeJson(ssdpjson, Serial);
    if (ssdpjson.containsKey(keyIndex))
    {
        ssdpjson.remove(keyIndex);
    }
    ssdpjson[keyIndex] = doc;
    xtouch_filesystem_writeJson(SD, xtouch_ssdp_devices, ssdpjson);

    serializeJson(ssdpjson, Serial);
    Serial.println("----");

    String output = "";
    for (JsonPair keyValue : ssdpjson.as<JsonObject>())
    {
        output = output + keyValue.key().c_str() + "\n";
    }

    if (!output.isEmpty())
    {
        output.remove(output.length() - 1);
        lv_roller_set_options(ui_printerPairScreenRoller, output.c_str(), LV_ROLLER_MODE_NORMAL);
        lv_obj_clear_flag(ui_printerPairScreenSubmitButton, LV_OBJ_FLAG_HIDDEN);
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

void xtouch_ssdp_start()
{
    xtouch_ssdp_udp.begin(XTOUCH_SSDP_UDP_PORT);

    // lv_label_set_text(introScreenCaption, LV_SYMBOL_SETTINGS " Pairing device");
    // lv_timer_handler();
}

void xtouch_ssdp_stop()
{
    xtouch_ssdp_udp.stop();
    // lv_label_set_text(introScreenCaption, LV_SYMBOL_SETTINGS " Device paired");
    // lv_timer_handler();
    // delay(1500);
}

#endif
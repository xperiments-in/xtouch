#ifndef _XLCD_WEBSERVER
#define _XLCD_WEBSERVER

#include <Arduino.h>
#include <ArduinoJson.h>
#include "ESPmDNS.h"
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SD.h"
#include "xtouch/cloud.hpp"
#include "xtouch/mqtt.h"

AsyncWebServer server(80);

unsigned char h2int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return ((unsigned char)c - '0');
    }
    if (c >= 'a' && c <= 'f')
    {
        return ((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <= 'F')
    {
        return ((unsigned char)c - 'A' + 10);
    }
    return (0);
}

String urldecode(String str)
{

    String encodedString = "";
    char c;
    char code0;
    char code1;
    for (int i = 0; i < str.length(); i++)
    {
        c = str.charAt(i);
        if (c == '+')
        {
            encodedString += ' ';
        }
        else if (c == '%')
        {
            i++;
            code0 = str.charAt(i);
            i++;
            code1 = str.charAt(i);
            c = (h2int(code0) << 4) | h2int(code1);
            encodedString += c;
        }
        else
        {

            encodedString += c;
        }

        yield();
    }

    return encodedString;
}
void xtouch_webserver_end()
{
    server.reset();
    server.end();
    MDNS.end();
}
void sendError(AsyncWebServerRequest *request, String desc)
{

    String action = request->arg("action");
    String path = request->arg("path");

    DynamicJsonDocument jsonDoc(256);
    jsonDoc["error"] = action.c_str();
    jsonDoc["desc"] = desc.c_str();
    jsonDoc["path"] = path.c_str();
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    request->send(500, "application/json", jsonString);
}

void xtouch_webserver_begin()
{
    Serial.println("Starting webserver...");
    if (!MDNS.begin("xtouch"))
    {
        Serial.println("Error starting mDNS");
        return;
    }

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance()
        .addHeader("Access-Control-Allow-Methods", "DELETE, POST, GET, OPTIONS");
    DefaultHeaders::Instance()
        .addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");

    // Handle form submission
    server.on(
        "/provision",
        HTTP_POST,
        [](AsyncWebServerRequest *request) {},
        NULL,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            StaticJsonDocument<2048> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, data, len);
            serializeJsonPretty(jsonDoc, Serial);

            xtouch_filesystem_writeJson(SD, xtouch_paths_config, jsonDoc);

            request->send(200, "application/json", "{\"status\":\"ok\"}");

            delay(3000);
            ESP.restart();
            //
        });

    server.on(
        "/",
        HTTP_GET,
        [](AsyncWebServerRequest *request)
        {
            const char *html = R"rawliteral(<html lang="en"><head><meta charset="UTF-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><meta name="viewport" content="width=device-width,initial-scale=1"><title>XTouch Web Installer</title><style>:root{--color-black:black;--color-cod-gray:#101010;--color-white:white;--color-error:rgb(191, 95, 95);--color-primary-rgba:0,192,251;--color-primary:#666666;--color-secondary-rgba:234,182,56;--color-secondary:#eab638;--esp-tools-button-color:#cccccc;--esp-tools-button-text-color:#101010;--improv-primary-color:#484}esp-web-install-button :host{--mdc-theme-primary:#2aff00}ewt-install-dialog:host{--mdc-theme-primary:#2aff00}body,html{background-color:var(--color-cod-gray);padding:0;margin:0;overflow:hidden}.tiles{display:flex;flex-direction:column;justify-content:center;left:50%;position:fixed;top:50%;-webkit-transform:translateX(-50%) translateY(-50%) rotate(22.5deg)}.tiles__line{-webkit-animation:runner 20s linear infinite;display:flex;transform:translateX(25%)}.tiles__line:nth-child(2){-webkit-animation-duration:64s}.tiles__line:nth-child(3){-webkit-animation-duration:44s}@keyframes runner{to{-webkit-transform:translateX(-25%)}}.tiles__line-img{--tile-margin:3vw;background-position:50% 50%;background-size:cover;border-radius:50%;flex:none;height:30vh;margin:var(--tile-margin);width:30vh;background-color:var(--color-primary);opacity:.3}.tiles__line-img--large{border-radius:20vh;width:100vh;opacity:.1}.xhost__webusb{position:relative;background-color:#fff;padding:64px;display:table-cell;border-radius:16px;text-align:center;font-family:"Segoe UI",Tahoma,Geneva,Verdana,sans-serif;font-weight:700}.xhost__webusb svg{display:block;margin-top:32px}.xhost__webusb-container{display:flex;justify-content:center;align-items:center;height:100vh}</style></head><body><div class="tiles"><div class="tiles__line"><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div></div></div><div class="xhost__webusb-container"><div class="xhost__webusb"><img width="200" src="data:image/png;base64,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"></div></div></body></html>)rawliteral";
            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", html);
            request->send(response);
            //
        });

    server.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.println("Webserver started");
    Serial.println("http://xtouch.local");
    Serial.println(WiFi.localIP());
}

#endif
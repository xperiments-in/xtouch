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
    server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
              StaticJsonDocument<200> jsonDoc;
              DeserializationError error = deserializeJson(jsonDoc, data, len);
              
              if (error)
              {
                  Serial.println("Failed to parse JSON");
                  request->send(400, "text/plain", "Invalid JSON");
                  return;
              }

              String code = jsonDoc["verificationCode"].as<String>();
              Serial.println("Received verification code: " + code);
              
              // Send confirmation response
              request->send(200, "text/plain", "Code received: " + code);

              // Process the verification code
              if (cloud.mainLogin(code))
              {
                //   xtouch_webserver_end();
                  xtouch_mqtt_setup();
              } });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {

                const char *html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bambu Lab Verification Code</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f4f4f4;
        }
        .container {
            text-align: center;
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            max-width: 400px;
            width: 100%;
        }
        input[type="text"] {
            padding: 10px;
            margin: 10px 0;
            border: 1px solid #ccc;
            border-radius: 4px;
            font-size: 16px;
        }
        button {
            padding: 10px 20px;
            font-size: 16px;
            color: #fff;
            background-color: #007bff;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        button:hover {
            background-color: #0056b3;
        }
        .message {
            margin-top: 10px;
            font-size: 14px;
            color: green;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Enter Bambu Lab Verification Code</h1>
        <h3>Check your email for the code</h3>
        <form id="verificationForm">
            <input type="text" id="verificationCode" name="verificationCode" placeholder="Enter your code" minlength="6" maxlength="6" required>
            <button type="submit">Submit</button>
            <div id="message" class="message"></div>
        </form>
    </div>

    <script>
        document.getElementById('verificationForm').addEventListener('submit', async function(event) {
            event.preventDefault(); // Prevent form from submitting traditionally

            const code = document.getElementById('verificationCode').value;
            const messageElement = document.getElementById('message');

            try {
                const response = await fetch('/submit', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ verificationCode: code })
                });

                if (response.ok) {
                    messageElement.textContent = 'Verification code submitted successfully!';
                    messageElement.style.color = 'green';
                } else {
                    messageElement.textContent = 'Failed to submit the code. Please try again.';
                    messageElement.style.color = 'red';
                }
            } catch (error) {
                messageElement.textContent = 'An error occurred. Please try again later.';
                messageElement.style.color = 'red';
            }
        });
    </script>
</body>
</html>
)rawliteral";

    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", html);
//   response->addHeader("Content-Encoding", "gzip");
    request->send(response); });

    server.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.println("Webserver started");
    Serial.println("http://xtouch.local");
    Serial.println(WiFi.localIP());
}

#endif
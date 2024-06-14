#ifndef _XLCD_NET
#define _XLCD_NET

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <MD5Builder.h>
#include "bbl-certs.h"

int downloadFileToSDCard(const char *url, const char *fileName, void (*onProgress)(int) = NULL, void (*onMD5Check)(int) = NULL, const char *otaMD5 = NULL)
{

    WiFiClientSecure wifiClient;
    wifiClient.setCACert(xperiments_in);

    HTTPClient http;

    String forceHttpsUrl = url;
    forceHttpsUrl.replace("http://", "https://");

    // Begin the HTTP request
    http.begin(wifiClient, forceHttpsUrl);

    int httpCode = http.GET();

    // Check for successful HTTP request
    bool success = false;
    MD5Builder md5Checker;

    if (httpCode == HTTP_CODE_OK)
    {
        File file = SD.open(fileName, FILE_WRITE);
        if (file)
        {
            Stream *response = &http.getStream();
            int responseTotalSize = http.getSize();
            int responseSize = 0;
            int lastProgress = 0;

            // Define a buffer size (e.g., 512 bytes)
            const int bufferSize = 512;
            uint8_t buffer[bufferSize];
            int bytesRead;

            while ((bytesRead = response->readBytes(buffer, bufferSize)) > 0)
            {
                int progress = (responseSize * 100) / responseTotalSize;
                if (onProgress && progress != lastProgress)
                {
                    onProgress(progress);
                }

                file.write(buffer, bytesRead);
                responseSize += bytesRead;
                lastProgress = progress;
            }

            file.close();
            success = true;
        }
        else
        {
            Serial.println("Failed to open file for writing");
        }

        if (otaMD5 != NULL && onMD5Check != NULL)
        {
            onMD5Check(-1);

            File fileMD5 = SD.open(fileName, FILE_READ);
            md5Checker.begin();
            md5Checker.addStream(fileMD5, fileMD5.size());
            md5Checker.calculate();
            fileMD5.close();

            success = strcmp(otaMD5, md5Checker.toString().c_str()) == 0;

            onMD5Check(success);
        }
        else
        {
            success = true;
        }
    }

    // End the HTTP request
    http.end();

    return success;
}

#endif
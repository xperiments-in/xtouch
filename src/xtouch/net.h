#ifndef _XLCD_NET
#define _XLCD_NET

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

bool downloadFileToSDCard(const char *url, const char *fileName, void (*callback)(int) = NULL)
{
    HTTPClient http;

    // Begin the HTTP request
    http.begin(url);

    int httpCode = http.GET();

    // Check for successful HTTP request
    bool success = false;
    if (httpCode == HTTP_CODE_OK)
    {
        File file = SD.open(fileName, FILE_WRITE);
        if (file)
        {
            Stream *response = &http.getStream();
            int responseTotalSize = http.getSize();
            int responseSize = 0;
            int lastProgress = 0;

            while (response->available())
            {
                int progress = (responseSize * 100) / responseTotalSize;
                if (callback && progress != lastProgress)
                {
                    callback(progress);
                }
                file.write(response->read());
                responseSize++;
                lastProgress = progress;
            }

            file.close();
            success = true;
        }
    }

    // End the HTTP request
    http.end();

    return success;
}

#endif
#ifndef _XLCD_SD
#define _XLCD_SD

#include "FS.h"
#include "SD.h"
#include <ArduinoJson.h>
#include <Arduino.h>

bool xtouch_filesystem_exist(fs::FS &fs, const char *path)
{
    return fs.exists(path);
}

void xtouch_filesystem_deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("[XTouch][SD] Deleting file: %s\n", path);
    if (fs.remove(path))
    {
        Serial.print(F("[XTouch][SD] File deleted: "));
        Serial.println(path);
    }
    else
    {
        Serial.print(F("[XTouch][SD] Delete failed: "));
        Serial.println(path);
    }
}

void xtouch_filesystem_writeJson(fs::FS &fs, const char *filename, DynamicJsonDocument json, bool defaultsToArray = false, int size = 1024)
{

    File configFile = fs.open(filename, FILE_WRITE);
    if (!configFile)
    {
        Serial.print(F("[XTouch][SD] Failed to write json file: "));
        Serial.println(filename);
        return;
    }

    serializeJson(json, configFile);

    configFile.close();

    delay(32);
}

DynamicJsonDocument xtouch_filesystem_readJson(fs::FS &fs, const char *filename, bool defaultsToArray = false, int size = 1024)
{
    DynamicJsonDocument doc(size); // Adjust the size as needed

    if (!fs.exists(filename))
    {
        if (defaultsToArray)
        {
            return doc.createNestedArray();
        }
        else
        {
            return doc.to<JsonObject>();
        }
    }

    File configFile = fs.open(filename);
    DeserializationError error = deserializeJson(doc, configFile);

    if (error)
    {
        Serial.print(F("[XTouch][SD] Failed to parse file: "));
        Serial.println(filename);
    }

    configFile.close();
    delay(32);
    return doc;
}

#endif
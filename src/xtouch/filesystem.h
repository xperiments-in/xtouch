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
    Serial.print(F("[XTouch][SD] Writting JSON file: "));
    Serial.println(filename);
    File configFile = fs.open(filename, FILE_WRITE);
    if (!configFile)
    {
        Serial.print(F("[XTouch][SD] Failed to write json file: "));
        Serial.println(filename);
        return;
    }

    serializeJson(json, configFile);
    configFile.close();
}

DynamicJsonDocument xtouch_filesystem_readJson(fs::FS &fs, const char *filename, bool defaultsToArray = false, int size = 1024)
{
    Serial.print(F("[XTouch][SD] Reading JSON file: "));
    Serial.println(filename);
    DynamicJsonDocument doc(size); // Adjust the size as needed

    if (!fs.exists(filename))
    {
        Serial.print(F("[XTouch][SD] Error Reading JSON File: "));
        Serial.println(filename);
        if (defaultsToArray)
        {
            return doc.createNestedArray();
        }
        else
        {
            return doc;
        }
    }

    File configFile = fs.open(filename);
    DeserializationError error = deserializeJson(doc, configFile);

    if (error)
    {
        Serial.print(F("[XTouch][SD] Error Parsing JSON File: "));
        Serial.println(filename);
    }

    configFile.close();
    return doc;
}

#endif
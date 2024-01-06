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

File xtouch_filesystem_open(fs::FS &fs, const char *path)
{
    return fs.open(path);
}

bool xtouch_filesystem_deleteFile(fs::FS &fs, const char *path)
{
    return fs.remove(path);
}

bool xtouch_filesystem_mkdir(fs::FS &fs, const char *path)
{
    if (!xtouch_filesystem_exist(SD, path))
    {
        return fs.mkdir(path);
    }
    return true;
}

bool xtouch_filesystem_rmdir(fs::FS &fs, const char *path)
{
    return fs.rmdir(path);
}

void xtouch_filesystem_writeJson(fs::FS &fs, const char *filename, JsonDocument json, bool defaultsToArray = false, int size = 1024)
{
    ConsoleDebug.print(F("[XTouch][SD] Writting JSON file: "));
    ConsoleDebug.println(filename);
    File configFile = fs.open(filename, FILE_WRITE);
    if (!configFile)
    {
        ConsoleError.print(F("[XTouch][SD] Failed to write json file: "));
        ConsoleError.println(filename);
        return;
    }

    serializeJson(json, configFile);
    configFile.close();
}

JsonDocument xtouch_filesystem_readJson(fs::FS &fs, const char *filename, bool defaultsToArray = false, int size = 1024)
{
    ConsoleDebug.print(F("[XTouch][SD] Reading JSON file: "));
    ConsoleDebug.println(filename);
    JsonDocument doc; // Adjust the size as needed


    if (!fs.exists(filename))
    {
        ConsoleError.print(F("[XTouch][SD] Error Reading JSON File: "));
        ConsoleError.println(filename);
        if (defaultsToArray)
        {
            return doc.add<JsonArray>();
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
        ConsoleError.print(F("[XTouch][SD] Error Parsing JSON File: "));
        ConsoleError.println(filename);
    }

    configFile.close();
    return doc;
}

#endif
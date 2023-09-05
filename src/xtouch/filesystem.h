#ifndef _XLCD_SD
#define _XLCD_SD

#include "FS.h"
#include "SD.h"
#include <ArduinoJson.h>
#include <Arduino.h>

void xtouch_filesystem_listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("[XTouch][SD] Listing directory: %s\n", dirname);
    if (dirname[0] == 46)
        return;

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println(F("[XTouch][SD] Failed to open directory"));
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(F("[XTouch][SD] Not a directory"));
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print(F("[XTouch][SD]  DIR : "));
            Serial.println(file.name());
            if (levels)
            {
                xtouch_filesystem_listDir(fs, file.name(), levels - 1);
            }
        }
        else
        {
            Serial.print(F("[XTouch][SD]  FILE: "));
            Serial.print(file.name());
            Serial.print(F("[XTouch][SD]  SIZE: "));
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void xtouch_filesystem_createDir(fs::FS &fs, const char *path)
{
    Serial.printf("[XTouch][SD] Creating Dir: %s\n", path);
    if (fs.mkdir(path))
    {
        Serial.println(F("[XTouch][SD] Dir created"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] mkdir failed"));
    }
}

void xtouch_filesystem_removeDir(fs::FS &fs, const char *path)
{
    Serial.printf("[XTouch][SD] Removing Dir: %s\n", path);
    if (fs.rmdir(path))
    {
        Serial.println(F("[XTouch][SD] Dir removed"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] rmdir failed"));
    }
}

void xtouch_filesystem_readFile(fs::FS &fs, const char *path)
{
    Serial.printf("[XTouch][SD] Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file)
    {
        Serial.println(F("[XTouch][SD] Failed to open file for reading"));
        return;
    }

    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void xtouch_filesystem_writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("[XTouch][SD] Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("[XTouch][SD] Failed to open file for writing"));
        return;
    }
    if (file.print(message))
    {
        Serial.println(F("[XTouch][SD] File written"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] Write failed"));
    }
    file.close();
}

void xtouch_filesystem_appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("[XTouch][SD] Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println(F("[XTouch][SD] Failed to open file for appending"));
        return;
    }
    if (file.print(message))
    {
        Serial.println(F("[XTouch][SD] Message appended"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] Append failed"));
    }
    file.close();
}

void xtouch_filesystem_renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    Serial.printf("[XTouch][SD] Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2))
    {
        Serial.println(F("[XTouch][SD] File renamed"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] Rename failed"));
    }
}

void xtouch_filesystem_deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("[XTouch][SD] Deleting file: %s\n", path);
    if (fs.remove(path))
    {
        Serial.println(F("[XTouch][SD] File deleted"));
    }
    else
    {
        Serial.println(F("[XTouch][SD] Delete failed"));
    }
}

void xtouch_filesystem_writeJson(fs::FS &fs, const char *filename, DynamicJsonDocument json, bool defaultsToArray = false, int size = 1024)
{

    File configFile = fs.open(filename, FILE_WRITE);
    if (!configFile)
    {
        Serial.println(F("[XTouch][SD] Failed to open file"));
        return;
    }

    serializeJson(json, configFile);

    configFile.close();
}

DynamicJsonDocument xtouch_filesystem_readJson(fs::FS &fs, const char *filename, bool defaultsToArray = false, int size = 1024)
{
    DynamicJsonDocument doc(size); // Adjust the size as needed

    File configFile = fs.open(filename);
    if (!configFile)
    {
        Serial.println(F("[XTouch][SD] Failed to open config file"));
        if (defaultsToArray)
        {
            return doc.createNestedArray();
        }
        else
        {
            return doc.to<JsonObject>();
        }
    }

    DeserializationError error = deserializeJson(doc, configFile);
    if (error)
    {
        Serial.println(F("[XTouch][SD] Failed to parse config file"));
        configFile.close();
        return doc; // Return an empty JSON document
    }

    configFile.close();
    return doc;
}

#endif
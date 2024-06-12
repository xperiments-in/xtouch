#ifndef _XLCD_FIRMWARE
#define _XLCD_FIRMWARE

#include <Arduino.h>
#include <Update.h>
#include <SD.h>
#include <stdio.h>
// #include <semver.h>

struct SemVer
{
    int major;
    int minor;
    int patch;
};

bool parseSemVer(const char *version, SemVer &semver)
{
    int parsed = sscanf(version, "%d.%d.%d", &semver.major, &semver.minor, &semver.patch);
    return parsed == 3;
}

int compareSemVer(const SemVer &v1, const SemVer &v2)
{
    if (v1.major != v2.major)
    {
        return v1.major - v2.major;
    }
    if (v1.minor != v2.minor)
    {
        return v1.minor - v2.minor;
    }
    if (v1.patch != v2.patch)
    {
        return v1.patch - v2.patch;
    }
    return 0; // Both versions are equal
}

bool isSemVerGreaterThan(const SemVer &v1, const SemVer &v2)
{
    return compareSemVer(v1, v2) > 0;
}

bool isSemVerLessThan(const SemVer &v1, const SemVer &v2)
{
    return compareSemVer(v1, v2) < 0;
}

bool isSemVerEqualTo(const SemVer &v1, const SemVer &v2)
{
    return compareSemVer(v1, v2) == 0;
}

#define XTOUCH_FIRMWARE_DOWNLOAD_RETRIES 5
byte xtouch_firmware_updateDownloadRetries = 0;

bool xtouch_firmware_semverNeedsUpdate(const char *compare)
{
    SemVer version1, version2;

    if (parseSemVer(XTOUCH_FIRMWARE_VERSION, version1) && parseSemVer(compare, version2))
    {
        if (isSemVerGreaterThan(version2, version1))
        {
            return true;
        }
        return false;
    }

    return false;
}

void xtouch_firmware_onProgress(size_t currSize, size_t totalSize)
{
    int16_t progress = (currSize * 100) / totalSize;
    lv_label_set_text_fmt(introScreenCaption, LV_SYMBOL_CHARGE " Updating %d%%", progress);
    lv_timer_handler();
    lv_task_handler();
}

void xtouch_firmware_checkOnlineFirmwareUpdate(void)
{
    if (!xTouchConfig.xTouchOTAEnabled)
    {
        return;
    }

    lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Checking for OTA Update");
    lv_timer_handler();
    lv_task_handler();

    bool hasOTAConfigFile = downloadFileToSDCard(xtouch_paths_firmware_ota_file, xtouch_paths_firmware_ota_json);

    if (hasOTAConfigFile)
    {

        DynamicJsonDocument doc = xtouch_filesystem_readJson(SD, xtouch_paths_firmware_ota_json);
        if (xtouch_firmware_semverNeedsUpdate(doc["version"]))
        {

            lv_label_set_text_fmt(introScreenCaption, LV_SYMBOL_CHARGE " Downloading Update %d%%", 0);
            lv_timer_handler();
            lv_task_handler();

            bool xtouch_firmware_hasFirmwareUpdate = downloadFileToSDCard(
                doc["url"],
                xtouch_paths_firmware_ota_fw,
                [](int progress)
                {
                    lv_label_set_text_fmt(introScreenCaption, LV_SYMBOL_CHARGE " Downloading Update %d%%", progress);
                    lv_timer_handler();
                    lv_task_handler();
                },
                [](int state)
                {
                    switch (state)
                    {
                    case -1:
                        lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Verifying Update");
                        break;
                    case 0:
                        lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Invalid Update MD5");
                        break;
                    case 1:
                        lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Update Verified");
                        break;
                    }
                    lv_timer_handler();
                    lv_task_handler();
                },
                doc["md5"]);

            if (xtouch_firmware_hasFirmwareUpdate)
            {
                lv_label_set_text(introScreenCaption, LV_SYMBOL_OK " Update downloaded");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                ESP.restart();
            }
            else
            {
                lv_label_set_text_fmt(introScreenCaption, LV_SYMBOL_WARNING " Failed to download update. Retry (%d/%d)", xtouch_firmware_updateDownloadRetries + 1, XTOUCH_FIRMWARE_DOWNLOAD_RETRIES);
                lv_timer_handler();
                lv_task_handler();
                delay(32);
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                xtouch_firmware_updateDownloadRetries++;
                if (xtouch_firmware_updateDownloadRetries == XTOUCH_FIRMWARE_DOWNLOAD_RETRIES)
                {
                    // we are unable to download correctly the file
                    // disable OTA to be able to boot
                    xTouchConfig.xTouchOTAEnabled = false;
                    xtouch_settings_save();
                    xtouch_filesystem_deleteFile(SD, xtouch_paths_firmware_ota_fw);
                    xtouch_filesystem_deleteFile(SD, xtouch_paths_firmware_ota_json);
                    ESP.restart();
                }
                else
                {
                    xtouch_firmware_checkOnlineFirmwareUpdate();
                }
            }
        }
        else
        {
            xtouch_filesystem_deleteFile(SD, xtouch_paths_firmware_ota_json);
        }
    }
    else
    {
        lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " Failed to download update");
        lv_timer_handler();
        lv_task_handler();
        delay(3000);
    }
}

void xtouch_firmware_checkFirmwareUpdate(void)
{

    if (xtouch_filesystem_exist(SD, xtouch_paths_firmware_ota_fw))
    {
        DynamicJsonDocument doc = xtouch_filesystem_readJson(SD, xtouch_paths_firmware_ota_json);
        File firmware = xtouch_filesystem_open(SD, xtouch_paths_firmware_ota_fw);
        Update.onProgress(xtouch_firmware_onProgress);
        Update.begin(firmware.size(), U_FLASH);
        if (doc.containsKey("md5"))
        {
            Update.setMD5(doc["md5"]);
        }
        Update.writeStream(firmware);
        bool updateSucceeded = Update.end();
        firmware.close();

        if (updateSucceeded)
        {
            lv_label_set_text(introScreenCaption, LV_SYMBOL_OK " Update finished");
            lv_timer_handler();
            lv_task_handler();
        }
        else
        {
            lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " Update error");
            lv_timer_handler();
            lv_task_handler();
            delay(3000);
            lv_label_set_text(introScreenCaption, LV_SYMBOL_TRASH " Deleting firmware file");
            lv_timer_handler();
            lv_task_handler();
        }

        xtouch_filesystem_deleteFile(SD, xtouch_paths_firmware_ota_json);
        xtouch_filesystem_deleteFile(SD, xtouch_paths_firmware_ota_fw);

        delay(2000);
        ESP.restart();
    }
}
#endif
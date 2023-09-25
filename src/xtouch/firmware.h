#ifndef _XLCD_FIRMWARE
#define _XLCD_FIRMWARE

#include <Arduino.h>
#include <Update.h>
#include <SD.h>
#include <stdio.h>
#include <semver.h>

#define XTOUCH_FIRMWARE_DOWNLOAD_RETRIES 5
byte xtouch_firmware_updateDownloadRetries = 0;

byte xtouch_firmware_semverNeedsUpdate(const char *compare)
{
    semver_t current_version = {};
    semver_t compare_version = {};

    if (semver_parse(XTOUCH_FIRMWARE_VERSION, &current_version) || semver_parse(compare, &compare_version))
    {
        return -1;
    }

    int resolution = semver_compare(compare_version, current_version);

    // Free allocated memory when we're done
    semver_free(&current_version);
    semver_free(&compare_version);

    if (resolution == 0 || resolution == -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
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

    bool hasOTAConfigFile = downloadFileToSDCard(xtouch_paths_firmware_ota_file, xtouch_paths_firmware_ota_json);

    if (hasOTAConfigFile)
    {

        DynamicJsonDocument doc = xtouch_filesystem_readJson(SD, xtouch_paths_firmware_ota_json);
        if (xtouch_firmware_semverNeedsUpdate(doc["version"]) == 1)
        {

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
        Update.setMD5(doc["md5"]);
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
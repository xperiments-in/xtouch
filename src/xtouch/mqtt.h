#ifndef _XLCD_MQTT
#define _XLCD_MQTT

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "ui/ui_msgs.h"
#include "types.h"
WiFiClientSecure xtouch_wiFiClientSecure;
PubSubClient xtouch_pubSubClient(xtouch_wiFiClientSecure);
#include "ams.h"
#include "xtouch.h"

#define XTOUCH_MQTT_SERVER_TIMEOUT 20
#define XTOUCH_MQTT_SERVER_BUFFER_SIZE 8192
#define XTOUCH_MQTT_SERVER_JSON_PARSE_SIZE 8192

/* ---------------------------------------------- */
bool xtouch_mqtt_firstConnectionDone = false;
int xtouch_mqtt_connection_fail_count = 5;

void sendMsg(XTOUCH_MESSAGE message, unsigned long long data = 0)
{
    XTOUCH_MESSAGE_DATA eventData;
    eventData.data = data;
    lv_msg_send(message, &eventData);
}

String xtouch_mqtt_parse_printer_type(String type_str)
{
    if (type_str == "3DPrinter-X1")
    {
        return "BL-P002";
    }
    else if (type_str == "3DPrinter-X1-Carbon")
    {
        return "BL-P001";
    }
    else if (type_str == "BL-P001")
    {
        return type_str;
    }
    else if (type_str == "BL-P003")
    {
        return type_str;
    }
    return "";
}

void xtouch_mqtt_processPushStatus(JsonDocument &incomingJson)
{
    ConsoleDebug.println(F("[XTouch][MQTT] ProcessPushStatus"));

    if (incomingJson != NULL && incomingJson.containsKey("print"))
    {

        if (incomingJson["print"].containsKey("gcode_state"))
        {
            xtouch_device_set_print_state(incomingJson["print"]["gcode_state"].as<String>());
        }

        if (incomingJson["print"].containsKey("layer_num"))
        {
            bambuStatus.current_layer = incomingJson["print"]["layer_num"].as<int>();
        }

        if (incomingJson["print"].containsKey("total_layer_num"))
        {
            bambuStatus.total_layers = incomingJson["print"]["total_layer_num"].as<int>();
        }

        if (incomingJson["print"].containsKey("mc_remaining_time"))
        {
            if (incomingJson["print"]["mc_remaining_time"].is<String>())
            {
                String timeStr = incomingJson["print"]["mc_remaining_time"].as<String>();

                bambuStatus.mc_left_time = atoi(timeStr.c_str()) * 60;
            }
            else if (incomingJson["print"]["mc_remaining_time"].is<int>())
            {
                bambuStatus.mc_left_time = incomingJson["print"]["mc_remaining_time"].as<int>() * 60;
            }
        }

        if (incomingJson["print"].containsKey("mc_percent"))
        {
            if (incomingJson["print"]["mc_percent"].is<String>())
                bambuStatus.mc_print_percent = atoi(incomingJson["print"]["mc_percent"].as<String>().c_str());
            else if (incomingJson["print"]["mc_percent"].is<int>())
                bambuStatus.mc_print_percent = incomingJson["print"]["mc_percent"].as<int>();
        }

        if (incomingJson["print"].containsKey("spd_lvl"))
        {
            bambuStatus.printing_speed_lvl = incomingJson["print"]["spd_lvl"].as<int>();
        }

        if (incomingJson["print"].containsKey("spd_mag"))
        {
            bambuStatus.printing_speed_mag = incomingJson["print"]["spd_mag"].as<int>();
        }

        if (incomingJson["print"].containsKey("gcode_state") ||
            incomingJson["print"].containsKey("layer_num") ||
            incomingJson["print"].containsKey("total_layer_num") ||
            incomingJson["print"].containsKey("mc_remaining_time") ||
            incomingJson["print"].containsKey("mc_percent") ||
            incomingJson["print"].containsKey("spd_lvl") ||
            incomingJson["print"].containsKey("spd_mag"))
        {

            sendMsg(XTOUCH_ON_PRINT_STATUS);
        }

        if (incomingJson["print"].containsKey("ipcam"))
        {

            if (incomingJson["print"]["ipcam"].containsKey("ipcam_record"))
            {
                bambuStatus.camera_recording_when_printing = incomingJson["ipcam"]["ipcam_record"].as<String>() == "enable";
            }
            if (incomingJson["print"]["ipcam"].containsKey("timelapse"))
            {
                bambuStatus.camera_timelapse = incomingJson["print"]["ipcam"]["timelapse"].as<String>() == "enable";
            }
            if (incomingJson["print"]["ipcam"].containsKey("ipcam_dev"))
            {
                bambuStatus.has_ipcam = incomingJson["print"]["ipcam"]["ipcam_dev"].as<String>() == "1";
            }
            sendMsg(XTOUCH_ON_IPCAM);
        }

        if (incomingJson["print"].containsKey("stg_cur"))
        {
            // ConsoleDebug.println(F("[XTouch][MQTT] stg_cur"));
            // ConsoleDebug.println(incomingJson["print"]["stg_cur"].as<int>());
            // ConsoleDebug.println(F("[XTouch][MQTT] stg_cur B"));
        }

        if (incomingJson["print"].containsKey("lights_report"))
        {

            if (incomingJson["print"]["lights_report"][0].containsKey("mode"))
            {
                XTOUCH_MESSAGE_DATA eventData;
                if (incomingJson["print"]["lights_report"][0]["mode"] == "on")
                {
                    bambuStatus.led = true;
                    eventData.data = 1;
                }
                else
                {
                    bambuStatus.led = false;
                    eventData.data = 0;
                }
                lv_msg_send(XTOUCH_ON_LIGHT_REPORT, &eventData);
            }
        }

        if (incomingJson["print"].containsKey("bed_temper"))
        {
            bambuStatus.bed_temper = incomingJson["print"]["bed_temper"].as<double>();
            sendMsg(XTOUCH_ON_BED_TEMP, bambuStatus.bed_temper);
        }

        if (incomingJson["print"].containsKey("bed_target_temper"))
        {
            bambuStatus.bed_target_temper = incomingJson["print"]["bed_target_temper"].as<double>();
            sendMsg(XTOUCH_ON_BED_TARGET_TEMP, bambuStatus.bed_target_temper);
        }

        if (incomingJson["print"].containsKey("nozzle_temper"))
        {
            bambuStatus.nozzle_temper = incomingJson["print"]["nozzle_temper"].as<double>();
            sendMsg(XTOUCH_ON_NOZZLE_TEMP, bambuStatus.nozzle_temper);
        }

        if (incomingJson["print"].containsKey("nozzle_target_temper"))
        {
            bambuStatus.nozzle_target_temper = incomingJson["print"]["nozzle_target_temper"].as<double>();
            sendMsg(XTOUCH_ON_NOZZLE_TARGET_TEMP, bambuStatus.nozzle_target_temper);
        }

        if (incomingJson["print"].containsKey("chamber_temper"))
        {
            bambuStatus.chamber_temper = incomingJson["print"]["chamber_temper"].as<double>();
            sendMsg(XTOUCH_ON_CHAMBER_TEMP, bambuStatus.chamber_temper);
        }

        if (incomingJson["print"].containsKey("wifi_signal"))
        {
            String wifi_signal = incomingJson["print"]["wifi_signal"].as<String>();
            wifi_signal.replace("dBm", "");
            bambuStatus.wifi_signal = abs(wifi_signal.toInt());
            sendMsg(XTOUCH_ON_WIFI_SIGNAL, bambuStatus.wifi_signal);
        }

        if (incomingJson["print"].containsKey("cooling_fan_speed"))
        {
            int speed = incomingJson["print"]["cooling_fan_speed"].as<int>();
            bambuStatus.cooling_fan_speed = round(floor(speed / float(1.5)) * float(25.5));
            sendMsg(XTOUCH_ON_PART_FAN_SPEED, bambuStatus.cooling_fan_speed);
        }

        if (incomingJson["print"].containsKey("big_fan1_speed"))
        {
            int speed = incomingJson["print"]["big_fan1_speed"].as<int>();
            bambuStatus.big_fan1_speed = round(floor(speed / float(1.5)) * float(25.5));
            sendMsg(XTOUCH_ON_PART_AUX_SPEED, bambuStatus.big_fan1_speed);
        }

        // if (incomingJson["print"].containsKey("big_fan2_speed"))
        // {
        //     int speed = incomingJson["print"]["big_fan1_speed"].as<int>();
        //     bambuStatus.big_fan2_speed = round(floor(speed / float(1.5)) * float(25.5));
        //     sendMsg(XTOUCH_ON_PART_AUX_SPEED, bambuStatus.big_fan2_speed);
        // }

        if (incomingJson["print"].containsKey("hw_switch_state"))
        {
            bambuStatus.hw_switch_state = incomingJson["print"]["hw_switch_state"].as<int>();
        }

        if (incomingJson["print"].containsKey("ams"))
        {

            if (incomingJson["ams"].containsKey("ams_exist_bits"))
            {
                bambuStatus.ams_exist_bits = incomingJson["ams"]["ams_exist_bits"].as<String>().toInt();
            }

            if (incomingJson.containsKey("ams_status"))
            {
                int ams_status = incomingJson["ams_status"].as<int>();
                xtouch_ams_parse_status(ams_status);
            }

            if (incomingJson["print"]["ams"].containsKey("ams"))
            {

                JsonArray array = incomingJson["print"]["ams"]["ams"].as<JsonArray>();
                bambuStatus.ams = array.size() > 0;
                sendMsg(XTOUCH_ON_AMS, array.size() > 0 ? 1 : 0);

                long int last_ams_exist_bits = bambuStatus.ams_exist_bits;
                long int last_tray_exist_bits = bambuStatus.tray_exist_bits;
                long int last_is_bbl_bits = bambuStatus.tray_is_bbl_bits;
                long int last_read_done_bits = bambuStatus.tray_read_done_bits;
                long int last_ams_version = bambuStatus.ams_version;

                if (incomingJson["ams"].containsKey("ams_exist_bits"))
                {
                    bambuStatus.ams_exist_bits = incomingJson["ams"]["ams_exist_bits"].as<String>().toInt();
                }
                if (incomingJson["ams"].containsKey("tray_exist_bits"))
                {
                    bambuStatus.tray_exist_bits = incomingJson["ams"]["tray_exist_bits"].as<String>().toInt();
                }
                if (incomingJson["ams"].containsKey("tray_read_done_bits"))
                {
                    bambuStatus.tray_read_done_bits = incomingJson["ams"]["tray_read_done_bits"].as<String>().toInt();
                }
                if (incomingJson["ams"].containsKey("tray_reading_bits"))
                {
                    bambuStatus.tray_reading_bits = incomingJson["ams"]["tray_reading_bits"].as<String>().toInt();
                    bambuStatus.ams_support_use_ams = true;
                }
                if (incomingJson["ams"].containsKey("tray_is_bbl_bits"))
                {
                    bambuStatus.tray_is_bbl_bits = incomingJson["ams"]["tray_is_bbl_bits"].as<String>().toInt();
                }
                if (incomingJson["ams"].containsKey("version"))
                {
                    if (incomingJson["ams"]["version"].is<int>())
                    {

                        bambuStatus.ams_version = incomingJson["ams"]["version"].as<int>();
                    }
                }
                if (incomingJson["ams"].containsKey("tray_now"))
                {
                    xtouch_ams_parse_tray_now(incomingJson["ams"]["tray_now"].as<String>());
                }
                if (incomingJson["ams"].containsKey("tray_tar"))
                {
                    bambuStatus.m_tray_tar = incomingJson["ams"]["tray_tar"].as<int>();
                }
                if (incomingJson["ams"].containsKey("ams_rfid_status"))
                {
                    bambuStatus.ams_rfid_status = incomingJson["ams"]["ams_rfid_status"].as<int>();
                }

                if (incomingJson["ams"].containsKey("humidity"))
                {
                    if (incomingJson["ams"]["humidity"].is<String>())
                    {
                        String humidity_str = incomingJson["ams"]["humidity"].as<String>();

                        bambuStatus.ams_humidity = atoi(humidity_str.c_str());
                    }
                }
                if (incomingJson["ams"].containsKey("insert_flag") || incomingJson["ams"].containsKey("power_on_flag") || incomingJson["ams"].containsKey("calibrate_remain_flag"))
                {
                    if (bambuStatus.ams_user_setting_hold_count > 0)
                    {
                        bambuStatus.ams_user_setting_hold_count--;
                    }
                    else
                    {
                        if (incomingJson["ams"].containsKey("insert_flag"))
                        {
                            bambuStatus.ams_insert_flag = incomingJson["ams"]["insert_flag"].as<bool>();
                        }
                        if (incomingJson["ams"].containsKey("power_on_flag"))
                        {
                            bambuStatus.ams_power_on_flag = incomingJson["ams"]["power_on_flag"].as<bool>();
                        }
                        if (incomingJson["ams"].containsKey("calibrate_remain_flag"))
                        {
                            bambuStatus.ams_calibrate_remain_flag = incomingJson["ams"]["calibrate_remain_flag"].as<bool>();
                        }
                    }
                }

                if (bambuStatus.ams_exist_bits != last_ams_exist_bits || last_tray_exist_bits != last_tray_exist_bits || bambuStatus.tray_is_bbl_bits != last_is_bbl_bits || bambuStatus.tray_read_done_bits != last_read_done_bits || last_ams_version != bambuStatus.ams_version)
                {
                    bambuStatus.is_ams_need_update = true;
                    sendMsg(XTOUCH_ON_AMS_BITS, 0);
                }

                if (incomingJson.containsKey("printer_type"))
                {
                    strcpy(bambuStatus.printer_type, xtouch_mqtt_parse_printer_type(incomingJson["printer_type"].as<String>()).c_str());
                }
            }
        }

        // parse hms msg

        // hms_list.clear();
        if (incomingJson["print"].containsKey("hms"))
        {
            if (incomingJson["print"]["hms"].is<JsonArray>())
            {

                for (JsonVariant value : incomingJson["print"]["hms"].as<JsonArray>())
                {
                    JsonObject element = value.as<JsonObject>();
                    unsigned attr = element["attr"].as<unsigned>();
                    unsigned code = element["code"].as<unsigned>();
                    int module_id;
                    unsigned module_num;
                    unsigned part_id;
                    unsigned reserved;
                    int msg_level;
                    int msg_code;
                    unsigned int model_id_int = (attr >> 24) & 0xFF;
                    if (model_id_int < MODULE_MAX)
                        module_id = model_id_int;
                    else
                        module_id = MODULE_UKNOWN;
                    module_num = (attr >> 16) & 0xFF;
                    part_id = (attr >> 8) & 0xFF;
                    reserved = (attr >> 0) & 0xFF;
                    unsigned msg_level_int = code >> 16;
                    if (msg_level_int < HMS_MSG_LEVEL_MAX)
                        msg_level = msg_level_int;
                    else
                        msg_level = HMS_UNKNOWN;
                    msg_code = code & 0xFFFF;

                    char buffer[17]; // The buffer to store the formatted string
                    sprintf(buffer, "%02X%02X%02X00000%01X%04X",
                            module_id,
                            module_num,
                            part_id,
                            msg_level,
                            msg_code);

                    char *endPtr; // Puntero para almacenar el primer carácter no convertido

                    // Convertir el valor hexadecimal a unsigned long long utilizando strtoull()
                    unsigned long long intValue = strtoull(buffer, &endPtr, 16);

                    hms_enqueue(intValue);

                    sendMsg(XTOUCH_ON_HMS_ERROR, 0);
                }
            }
        }
    }
}

void xtouch_mqtt_parseMessage(char *topic, byte *payload, unsigned int length)
{

    ConsoleDebug.println(F("[XTouch][MQTT] ParseMessage"));
    DynamicJsonDocument incomingJson(XTOUCH_MQTT_SERVER_JSON_PARSE_SIZE);
    auto deserializeError = deserializeJson(incomingJson, payload, length);
    xtouch_debug_json(incomingJson);
    if (!deserializeError)
    {

        if (incomingJson.containsKey("print") && incomingJson["print"].containsKey("command"))
        {

            String command = incomingJson["print"]["command"].as<String>();

            if (command == "push_status")
            {
                xtouch_mqtt_processPushStatus(incomingJson);
            }
            else if (command == "gcode_line")
            {
                ConsoleDebug.println(F("[XTouch][MQTT] gcode_line"));
                ConsoleDebug.println(String((char *)payload));
            }
        }

        if (incomingJson.containsKey("camera"))
        {
            if (incomingJson["camera"].containsKey("command"))
            {
                if (incomingJson["camera"]["command"].as<String>() == "ipcam_timelapse")
                {
                    bambuStatus.camera_timelapse = incomingJson["camera"]["control"].as<String>() == "enable";
                }
                else if (incomingJson["camera"]["command"].as<String>() == "ipcam_record_set")
                {
                    bambuStatus.camera_recording_when_printing = incomingJson["camera"]["control"].as<String>() == "enable";
                }
                sendMsg(XTOUCH_ON_IPCAM);
            }
        }
    }
    else
    {
        ConsoleError.println(F("[XTouch][MQTT] ParseMessage deserializeJson failed"));
    }
}

int xtouch_mqtt_connect_retries = 100;

const char *generateRandomKey(int keyLength)
{
    // Define the character set from which to generate the key
    char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    // Initialize an empty key
    static char key[17]; // 16 characters + null-terminator

    // Generate random characters for the key
    for (int i = 0; i < keyLength; i++)
    {
        int randomIndex = random(sizeof(charset) - 1);
        key[i] = charset[randomIndex];
    }

    // Null-terminate the key
    key[keyLength] = '\0';

    // Return a pointer to the key
    return key;
}

void xtouch_mqtt_onMqttReady()
{
    if (!xtouch_mqtt_firstConnectionDone)
    {
        loadScreen(0);
        xtouch_screen_startScreenTimer();
    }
    xtouch_mqtt_firstConnectionDone = true;
}

void xtouch_mqtt_connect()
{

    ConsoleInfo.println(F("[XTouch][MQTT] Connecting"));

    String deviceTopic = String("device/") + xTouchConfig.xTouchSerialNumber;
    String reportTopic = deviceTopic + String("/report");
    lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Connecting to Printer");
    lv_timer_handler();
    lv_task_handler();
    delay(32);
    xtouch_mqtt_firstConnectionDone = false;

    while (!xtouch_pubSubClient.connected())
    {
        String clientId = "XTOUCH-CLIENT-" + String(generateRandomKey(16));
        // String clientId = "XTOUCH-CLIENT";
        if (xtouch_pubSubClient.connect(clientId.c_str(), "bblp", xTouchConfig.xTouchAccessCode))
        {
            ConsoleInfo.println(F("[XTouch][MQTT] ---- CONNECTED ----"));

            xtouch_pubSubClient.subscribe(reportTopic.c_str());
            xtouch_device_pushall();
            xtouch_device_get_version();
            xtouch_mqtt_onMqttReady();
            break;
        }
        else
        {
            ConsoleError.printf("[XTouch][MQTT] ---- CONNECTION FAIL ----: %d\n", xtouch_pubSubClient.state());

            switch (xtouch_pubSubClient.state())
            {

            case -4: // MQTT_CONNECTION_TIMEOUT
                xtouch_mqtt_connection_fail_count--;
                if (xtouch_mqtt_connection_fail_count == 0)
                {
                    ESP.restart();
                }
                break;
            case -3: // MQTT_CONNECTION_LOST
            case -1: // MQTT_DISCONNECTED
            case -2: // MQTT_CONNECT_FAILED
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT ERROR");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                ESP.restart();
                break;
            case 1: // MQTT BAD_PROTOCOL
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT BAD PROTOCOL");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                ESP.restart();
                break;
            case 2: // MQTT BAD_CLIENT_ID
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT BAD CLIENT ID");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                ESP.restart();
                break;
            case 3: // MQTT UNAVAILABLE
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT UNAVAILABLE");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                ESP.restart();
                break;
            case 4: // MQTT BAD_CREDENTIALS
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT BAD CREDENTIALS");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                xtouch_ssdp_clear_device_list();
                xtouch_ssdp_clear_pair_list();
                ESP.restart();
                break;
            case 5: // MQTT UNAUTHORIZED
                lv_label_set_text(introScreenCaption, LV_SYMBOL_WARNING " MQTT UNAUTHORIZED");
                lv_timer_handler();
                lv_task_handler();
                delay(3000);
                lv_label_set_text(introScreenCaption, LV_SYMBOL_REFRESH " REBOOTING");
                lv_timer_handler();
                lv_task_handler();
                xtouch_ssdp_clear_device_list();
                xtouch_ssdp_clear_pair_list();
                ESP.restart();

                break;
            };
        }
        lv_timer_handler();
        lv_task_handler();
        delay(32);
    }
}

void xtouch_mqtt_setup()
{
    lv_label_set_text(introScreenCaption, LV_SYMBOL_CHARGE " Connecting to Printer");
    lv_timer_handler();
    lv_task_handler();
    delay(32);

    IPAddress ip;
    DynamicJsonDocument printer = xtouch_ssdp_load_printer();
    DynamicJsonDocument printerIps = xtouch_ssdp_load_printerIPs();
    String pairedModel = printer[xTouchConfig.xTouchSerialNumber]["model"].as<String>();

    ip.fromString(printerIps[xTouchConfig.xTouchSerialNumber].as<String>());
    strcpy(xTouchConfig.xTouchPrinterModel, pairedModel.c_str());

    xtouch_mqtt_topic_setup();
    xtouch_wiFiClientSecure.setInsecure();
    xtouch_pubSubClient.setBufferSize(XTOUCH_MQTT_SERVER_BUFFER_SIZE);
    xtouch_pubSubClient.setServer(ip, 8883);
    xtouch_pubSubClient.setCallback(xtouch_mqtt_parseMessage);
    xtouch_pubSubClient.setSocketTimeout(XTOUCH_MQTT_SERVER_TIMEOUT);

    /* home */
    lv_msg_subscribe(XTOUCH_COMMAND_LIGHT_TOGGLE, (lv_msg_subscribe_cb_t)xtouch_device_onLightToggleCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_STOP, (lv_msg_subscribe_cb_t)xtouch_device_onStopCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_PAUSE, (lv_msg_subscribe_cb_t)xtouch_device_onPauseCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_RESUME, (lv_msg_subscribe_cb_t)xtouch_device_onResumeCommand, NULL);

    /* control */
    lv_msg_subscribe(XTOUCH_COMMAND_HOME, (lv_msg_subscribe_cb_t)xtouch_device_onHomeCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_LEFT, (lv_msg_subscribe_cb_t)xtouch_device_onLeftCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_RIGHT, (lv_msg_subscribe_cb_t)xtouch_device_onRightCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_UP, (lv_msg_subscribe_cb_t)xtouch_device_onUpCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_DOWN, (lv_msg_subscribe_cb_t)xtouch_device_onDownCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_BED_TARGET_TEMP, (lv_msg_subscribe_cb_t)xtouch_device_onBedTargetTempCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_NOZZLE_TARGET_TEMP, (lv_msg_subscribe_cb_t)xtouch_device_onNozzleTargetCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_PART_FAN_SPEED, (lv_msg_subscribe_cb_t)xtouch_device_onPartSpeedCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_AUX_FAN_SPEED, (lv_msg_subscribe_cb_t)xtouch_device_onAuxSpeedCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_PRINT_SPEED, (lv_msg_subscribe_cb_t)xtouch_device_onPrintSpeedCommand, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_UNLOAD_FILAMENT, (lv_msg_subscribe_cb_t)xtouch_device_onUnloadFilament, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_LOAD_FILAMENT, (lv_msg_subscribe_cb_t)xtouch_device_onLoadFilament, NULL);

    /* filament */
    lv_msg_subscribe(XTOUCH_COMMAND_EXTRUDE_UP, (lv_msg_subscribe_cb_t)xtouch_device_onNozzleUp, NULL);
    lv_msg_subscribe(XTOUCH_COMMAND_EXTRUDE_DOWN, (lv_msg_subscribe_cb_t)xtouch_device_onNozzleDown, NULL);
}

void xtouch_mqtt_loop()
{
    if (!xtouch_pubSubClient.connected())
    {
        xtouch_mqtt_connect();
        return;
    }
    xtouch_pubSubClient.loop();
    delay(10);
}

#endif
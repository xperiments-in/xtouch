#ifndef _XLCD_DEVICE
#define _XLCD_DEVICE

#include <Arduino.h>

#define XTOUCH_DEVICE_CONTROL_MOVE_SPEED_XY 3000
#define XTOUCH_DEVICE_CONTROL_MOVE_SPEED_Z 1500

uint32_t xtouch_device_sequence_id = 0;

String xtouch_device_next_sequence()
{
    xtouch_device_sequence_id++;
    xtouch_device_sequence_id %= (UINT32_MAX - 1);
    return String(xtouch_device_sequence_id);
}

String xtouch_device_print_action(char const *action)
{
    DynamicJsonDocument json(256);
    json["print"]["command"] = action;
    json["print"]["param"] = "";
    json["print"]["sequence_id"] = xtouch_device_next_sequence();

    String result;
    serializeJson(json, result);
    return result;
}

String lastPrintState = "IDLE";
void xtouch_device_set_print_state(String state)
{
    if (state == "IDLE")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_IDLE;
    else if (state == "RUNNING")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_RUNNING;
    else if (state == "PAUSE")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_PAUSED;
    else if (state == "FINISH")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_FINISHED;
    else if (state == "PREPARE")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_PREPARE;
    else if (state == "FAILED")
        bambuStatus.print_status = XTOUCH_PRINT_STATUS_FAILED;

    if (lastPrintState != state && xTouchConfig.xTouchWakeOnPrint && state != "IDLE" && state != "FINISH" && state != "FAILED")
    {
        xtouch_screen_wakeUp();
    }

    lastPrintState = state;
}

void xtouch_device_publish(String request)
{
    xtouch_pubSubClient.publish(xtouch_mqtt_request_topic.c_str(), request.c_str());
    delay(10);
}

void xtouch_device_get_version()
{
    DynamicJsonDocument json(256);
    json["info"]["command"] = "get_version";
    json["info"]["sequence_id"] = xtouch_device_next_sequence();
    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);
}

void xtouch_device_pushall()
{
    DynamicJsonDocument json(256);
    json["pushing"]["command"] = "pushall";
    json["pushing"]["version"] = 1;
    json["pushing"]["push_target"] = 1;
    json["pushing"]["sequence_id"] = xtouch_device_next_sequence();
    json["user_id"] = "123456789";

    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);
}

void xtouch_device_set_printing_speed(int lvl)
{
    DynamicJsonDocument json(256);
    json["print"]["command"] = "print_speed";
    json["print"]["sequence_id"] = xtouch_device_next_sequence();
    json["print"]["param"] = String(lvl);

    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);
}

void xtouch_device_gcode_line(String line)
{
    DynamicJsonDocument json(line.length() + 256);
    json["print"]["command"] = "gcode_line";
    json["print"]["sequence_id"] = xtouch_device_next_sequence();
    json["print"]["param"] = line.c_str();
    json["user_id"] = "123456789";

    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);
}

void xtouch_device_move_axis(String axis, double value, int speed)
{
    char cmd[256];
    sprintf(cmd, "M211 S \nM211 X1 Y1 Z1\nM1002 push_ref_mode\nG91 \nG1 %s%0.1f F%d\nM1002 pop_ref_mode\nM211 R\n", axis.c_str(), value, speed);
    xtouch_device_gcode_line(String(cmd));
}

void xtouch_device_onLightToggleCommand(lv_msg_t *m)
{

    DynamicJsonDocument json(256);
    json["system"]["command"] = "ledctrl";
    json["system"]["led_node"] = "chamber_light";
    json["system"]["sequence_id"] = xtouch_device_next_sequence();
    json["system"]["led_mode"] = bambuStatus.chamberLed ? "off" : "on";
    json["system"]["led_on_time"] = 500;
    json["system"]["led_off_time"] = 500;
    json["system"]["loop_times"] = 0;
    json["system"]["interval_time"] = 0;
    json["user_id"] = "123456789";

    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);
    delay(10);
}

void xtouch_device_onHomeCommand(lv_msg_t *m)
{
    xtouch_device_gcode_line("G28 \n");
}

void xtouch_device_onLeftCommand(lv_msg_t *m)
{
    xtouch_device_move_axis("X", controlMode.inc == 10 ? -10 : -1, XTOUCH_DEVICE_CONTROL_MOVE_SPEED_XY);
}

void xtouch_device_onRightCommand(lv_msg_t *m)
{
    xtouch_device_move_axis("X", controlMode.inc == 10 ? 10 : 1, XTOUCH_DEVICE_CONTROL_MOVE_SPEED_XY);
}

void xtouch_device_onUpCommand(lv_msg_t *m)
{
    String axis = controlMode.axis == ControlAxisXY ? "Y" : "Z";
    int multiplier = axis == "Y" ? 1 : -1;
    xtouch_device_move_axis(axis, controlMode.inc == 10 ? 10 * multiplier : 1 * multiplier, axis == "Y" ? XTOUCH_DEVICE_CONTROL_MOVE_SPEED_XY : XTOUCH_DEVICE_CONTROL_MOVE_SPEED_Z);
}

void xtouch_device_onDownCommand(lv_msg_t *m)
{
    String axis = controlMode.axis == ControlAxisXY ? "Y" : "Z";
    int multiplier = axis == "Y" ? -1 : 1;
    xtouch_device_move_axis(axis, controlMode.inc == 10 ? 10 * multiplier : 1 * multiplier, axis == "Y" ? XTOUCH_DEVICE_CONTROL_MOVE_SPEED_XY : XTOUCH_DEVICE_CONTROL_MOVE_SPEED_Z);
}

void xtouch_device_onBedTargetTempCommand(lv_msg_t *m)
{
    bambuStatus.bed_target_temper = controlMode.target_bed_temper;
    xtouch_device_gcode_line("M140 S" + String(controlMode.target_bed_temper) + "\n");
    xtouch_device_pushall();
}

void xtouch_device_onNozzleTargetCommand(lv_msg_t *m)
{
    bambuStatus.nozzle_target_temper = controlMode.target_nozzle_temper;
    xtouch_device_gcode_line("M104 S" + String(controlMode.target_nozzle_temper) + "\n");
    xtouch_device_pushall();
}

void xtouch_device_onPartSpeedCommand(lv_msg_t *m)
{
    xtouch_device_gcode_line("M106 P1 S" + String(bambuStatus.cooling_fan_speed) + " \n");
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onAuxSpeedCommand(lv_msg_t *m)
{
    xtouch_device_gcode_line("M106 P2 S" + String(bambuStatus.big_fan1_speed) + "\n");
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onChamberSpeedCommand(lv_msg_t *m)
{
    xtouch_device_gcode_line("M106 P3 S" + String(bambuStatus.big_fan2_speed) + "\n");
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onPrintSpeedCommand(lv_msg_t *m)
{
    xtouch_device_set_printing_speed(bambuStatus.printing_speed_lvl);
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onIncSwitchCommand(lv_msg_t *m)
{
    controlMode.inc = controlMode.inc == 1 ? 10 : 1;
}

void xtouch_device_onStopCommand(lv_msg_t *m)
{
    xtouch_device_publish(xtouch_device_print_action("stop"));
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onPauseCommand(lv_msg_t *m)
{
    xtouch_device_publish(xtouch_device_print_action("pause"));
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onResumeCommand(lv_msg_t *m)
{
    xtouch_device_publish(xtouch_device_print_action("resume"));
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onNozzleUp(lv_msg_t *m)
{
    xtouch_device_gcode_line("M83 \nG0 E-10.0 F900\n");
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onNozzleDown(lv_msg_t *m)
{
    xtouch_device_gcode_line("M83 \nG0 E10.0 F900\n");
    delay(10);
    xtouch_device_pushall();
}

void xtouch_device_onLoadFilament(lv_msg_t *m)
{
    if (xtouch_can_load_filament())
    {
        xtouch_device_gcode_line("M620 S254\nM106 S255\nM104 S250\nM17 S\nM17 X0.5 Y0.5\nG91\nG1 Y-5 F1200\nG1 Z3\nG90\nG28 X\nM17 R\nG1 X70 F21000\nG1 Y245\nG1 Y265 F3000\nG4\nM106 S0\nM109 S250\nG1 X90\nG1 Y255\nG1 X120\nG1 X20 Y50 F21000\nG1 Y-3\nT254\nG1 X54\nG1 Y265\nG92 E0\nG1 E40 F180\nG4\nM104 S0\nG1 X70 F15000\nG1 X76\nG1 X65\nG1 X76\nG1 X65\nG1 X90 F3000\nG1 Y255\nG1 X100\nG1 Y265\nG1 X70 F10000\nG1 X100 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X165 F12000\nG1 Y245\nG1 X70\nG1 Y265 F3000\nG91\nG1 Z-3 F1200\nG90\nM621 S254\n\n");
    }
}

void xtouch_device_onUnloadFilament(lv_msg_t *m)
{
    if (xtouch_bblp_is_x1Series() && !bambuStatus.ams_support_virtual_tray)
    {

        DynamicJsonDocument json(256);
        json["print"]["command"] = "gcode_file";
        json["print"]["param"] = "/usr/etc/print/filament_unload.gcode";
        json["print"]["sequence_id"] = xtouch_device_next_sequence();
        String result;
        serializeJson(json, result);
        xtouch_device_publish(result);
    }
    else if (xtouch_bblp_is_p1Series() || (xtouch_bblp_is_x1Series() && bambuStatus.ams_support_virtual_tray))
    {
        xtouch_device_gcode_line("M620 S255\nM106 P1 S255\nM104 S250\nM17 S\nM17 X0.5 Y0.5\nG91\nG1 Y-5 F3000\nG1 Z3 F1200\nG90\nG28 X\nM17 R\nG1 X70 F21000\nG1 Y245\nG1 Y265 F3000\nG4\nM106 P1 S0\nM109 S250\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 X120 F21000\nG1 X20 Y50\nG1 Y-3\nT255\nG4\nM104 S0\nG1 X70 F3000\n\nG91\nG1 Z-3 F1200\nG90\nM621 S255\n\n");
    }
    else
    {
        DynamicJsonDocument json(256);
        json["print"]["command"] = "unload_filament";
        json["print"]["sequence_id"] = xtouch_device_next_sequence();
        String result;
        serializeJson(json, result);
        xtouch_device_publish(result);
    }
}

void xtouch_device_command_ams_control(void *s, lv_msg_t *m)
{
    const char *action = (const char *)m->payload;

    if (
        strcmp(action, "resume") == 0 ||
        strcmp(action, "reset") == 0 ||
        strcmp(action, "pause") == 0 ||
        strcmp(action, "done") == 0)
    {
        DynamicJsonDocument json(256);
        json["print"]["command"] = "ams_control";
        json["print"]["sequence_id"] = xtouch_device_next_sequence();
        json["print"]["param"] = action;
        String result;
        serializeJson(json, result);
        xtouch_device_publish(result);
    }
}

void xtouch_device_command_clean_print_error(void *s, lv_msg_t *m)
{

    if (m->payload != NULL)
    {
        const ClearErrorMessage *message = static_cast<const ClearErrorMessage *>(m->payload);

        DynamicJsonDocument json(256);
        json["print"]["command"] = "clean_print_error";
        json["print"]["sequence_id"] = xtouch_device_next_sequence();
        json["print"]["subtask_id"] = message->subtask_id;
        json["print"]["print_error"] = message->print_error;
        String result;
        serializeJson(json, result);
        xtouch_device_publish(result);
    }
}

// void xtouch_device_command_getPaCalibration()
// {

//     Serial.println("getPaCalibration");
//     DynamicJsonDocument doc(1024);
//     doc["print"]["command"] = "extrusion_cali_get";
//     doc["print"]["sequence_id"] = "456";
//     doc["print"]["filament_id"] = "";
//     doc["print"]["nozzle_diameter"] = "0.4";

//     // {"print":{"command":"extrusion_cali_get","filament_id":"","nozzle_diameter":"0.4","sequence_id":"20313","filaments":[],"reason":"success","result":"success"}}
//     String result;
//     serializeJson(doc, result);
//     xtouch_device_publish(result);
// }

#endif
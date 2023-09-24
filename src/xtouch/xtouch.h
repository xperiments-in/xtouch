#ifndef _XLCD_XTOUCH
#define _XLCD_XTOUCH

#include <Arduino.h>

#define XTOUCH_CONTROL_MOVE_SPEED_XY 3000
#define XTOUCH_CONTROL_MOVE_SPEED_Z 1500
#define XTOUCH_COMMAND_TIME_OUT 3

String xtouch_device_topic;
String xtouch_device_request_topic;
uint32_t xtouch_device_sequence_id = 0;

String get_stage_string(int stage)
{
    switch (stage)
    {
    case 0:
        // return _L("Printing");
        return F("Printing");
    case 1:
        return F("Auto bed leveling");
    case 2:
        return F("Heatbed preheating");
    case 3:
        return F("Sweeping XY mech mode");
    case 4:
        return F("Changing filament");
    case 5:
        return F("M400 pause");
    case 6:
        return F("Paused due to filament runout");
    case 7:
        return F("Heating hotend");
    case 8:
        return F("Calibrating extrusion");
    case 9:
        return F("Scanning bed surface");
    case 10:
        return F("Inspecting first layer");
    case 11:
        return F("Identifying build plate type");
    case 12:
        return F("Calibrating Micro Lidar");
    case 13:
        return F("Homing toolhead");
    case 14:
        return F("Cleaning nozzle tip");
    case 15:
        return F("Checking extruder temperature");
    case 16:
        return F("Printing was paused by the user");
    case 17:
        return F("Pause of front cover falling");
    case 18:
        return F("Calibrating the micro lida");
    case 19:
        return F("Calibrating extrusion flow");
    case 20:
        return F("Paused due to nozzle temperature malfunction");
    case 21:
        return F("Paused due to heat bed temperature malfunction");
    default:;
    }
    return "";
}

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

void xtouch_mqtt_topic_setup()
{
    xtouch_device_topic = String("device/") + xTouchConfig.xTouchSerialNumber;
    xtouch_device_request_topic = xtouch_device_topic + String("/request");
}

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

    // bambuStatus.print_status = XTOUCH_PRINT_STATUS_RUNNING;
}

void xtouch_device_publish(String request)
{
    xtouch_pubSubClient.publish(xtouch_device_request_topic.c_str(), request.c_str());
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
    String command = "{\"pushing\":{\"sequence_id\":\"$seq\",\"command\":\"pushall\"},\"user_id\":\"123456789\"}";
    command.replace("$seq", xtouch_device_next_sequence());
    xtouch_device_publish(command);
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

    String gcode = "{\"print\":{\"sequence_id\":\"$sequence_id\",\"command\":\"gcode_line\",\"param\":\"$gcode\"},\"user_id\":\"1234567890\"}";
    gcode.replace("$sequence_id", xtouch_device_next_sequence());
    gcode.replace("$gcode", line);
    xtouch_device_publish(gcode);
}

void xtouch_device_move_axis(String axis, double value, int speed)
{
    String deviceTopic = String("device/") + xTouchConfig.xTouchSerialNumber;
    String requestTopic = deviceTopic + String("/request");

    char cmd[256];
    sprintf(cmd, "M211 S \nM211 X1 Y1 Z1\nM1002 push_ref_mode\nG91 \nG1 %s%0.1f F%d\nM1002 pop_ref_mode\nM211 R\n", axis.c_str(), value, speed);
    xtouch_device_gcode_line(String(cmd));
}

void xtouch_device_onLightToggleCommand(lv_msg_t *m)
{
    String deviceTopic = String("device/") + xTouchConfig.xTouchSerialNumber;
    String requestTopic = deviceTopic + String("/request");
    String on;
    String off;
    on = "{\"system\":{\"sequence_id\":\"$sequence_id\",\"command\":\"ledctrl\",\"led_node\":\"chamber_light\",\"led_mode\":\"on\",\"led_on_time\": 500,\"led_off_time\": 500,\"loop_times\": 0,\"interval_time\":0},\"user_id\":\"123456789\"}";
    on.replace("$sequence_id", xtouch_device_next_sequence());
    off = "{\"system\":{\"sequence_id\":\"$sequence_id\",\"command\":\"ledctrl\",\"led_node\":\"chamber_light\",\"led_mode\":\"off\",\"led_on_time\": 500,\"led_off_time\": 500,\"loop_times\": 0,\"interval_time\":0},\"user_id\":\"123456789\"}";
    off.replace("$sequence_id", xtouch_device_next_sequence());
    xtouch_pubSubClient.publish(requestTopic.c_str(), bambuStatus.led ? off.c_str() : on.c_str());
    delay(10);
}

void xtouch_device_onHomeCommand(lv_msg_t *m)
{
    xtouch_device_gcode_line("G28 \n");
}

void xtouch_device_onLeftCommand(lv_msg_t *m)
{
    xtouch_device_move_axis("X", controlMode.inc == 10 ? -10 : -1, XTOUCH_CONTROL_MOVE_SPEED_XY);
}

void xtouch_device_onRightCommand(lv_msg_t *m)
{
    xtouch_device_move_axis("X", controlMode.inc == 10 ? 10 : 1, XTOUCH_CONTROL_MOVE_SPEED_XY);
}

void xtouch_device_onUpCommand(lv_msg_t *m)
{
    String axis = controlMode.axis == ControlAxisXY ? "Y" : "Z";
    int multiplier = axis == "Y" ? 1 : -1;
    xtouch_device_move_axis(axis, controlMode.inc == 10 ? 10 * multiplier : 1 * multiplier, axis == "Y" ? XTOUCH_CONTROL_MOVE_SPEED_XY : XTOUCH_CONTROL_MOVE_SPEED_Z);
}

void xtouch_device_onDownCommand(lv_msg_t *m)
{
    String axis = controlMode.axis == ControlAxisXY ? "Y" : "Z";
    int multiplier = axis == "Y" ? -1 : 1;
    xtouch_device_move_axis(axis, controlMode.inc == 10 ? 10 * multiplier : 1 * multiplier, axis == "Y" ? XTOUCH_CONTROL_MOVE_SPEED_XY : XTOUCH_CONTROL_MOVE_SPEED_Z);
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
    Serial.println("xtouch_device_onChamberSpeedCommand");
    Serial.println(bambuStatus.big_fan2_speed);
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
        // xtouch_device_gcode_line("M620 S2\nM104 S250\nG28 X\nG91\nG1 Z3.0 F1200\nG90\n\nG1 X70 F12000\nG1 Y245\nG1 Y265 F3000\nM109 S250\nG1 X120 F12000\n\nG1 X20 Y50 F12000\nG1 Y-3\n\nT2\n\nG1 X54  F12000\nG1 Y265\nM400\nM106 P1 S0\nG92 E0\nG1 E40 F200\nM400\nM109 S210\nM400\nM106 P1 S255\nG92 E0\nG1 E5 F300\nM400\nM106 P1 S0\nG1 X70  F9000\nG1 X76 F15000\nG1 X65 F15000\nG1 X76 F15000\nG1 X65 F15000\n\nG1 X70 F6000\nG1 X100 F5000\nG1 X70 F15000\nG1 X100 F5000\nG1 X70 F15000\nG1 X165 F5000\nG1 Y245\n\nG91\nG1 Z-3.0 F1200\nG90\nM621 S2\n");
        xtouch_device_gcode_line("M620 S255\nM104 S250\nG28 X\nG91\nG1 Z3.0 F1200\nG90\n\nG1 X70 F12000\nG1 Y245\nG1 Y265 F3000\nM109 S250\nG1 X120 F12000\n\nG1 X20 Y50 F12000\nG1 Y-3\n\nT2\n\nG1 X54  F12000\nG1 Y265\nM400\nM106 P1 S0\nG92 E0\nG1 E40 F200\nM400\nM109 S210\nM400\nM106 P1 S255\nG92 E0\nG1 E5 F300\nM400\nM106 P1 S0\nG1 X70 F9000\nG1 X76 F15000\nG1 X65 F15000\nG1 X76 F15000\nG1 X65 F15000\n\nG1 X70 F6000\nG1 X100 F5000\nG1 X70 F15000\nG1 X100 F5000\nG1 X70 F15000\nG1 X165 F5000\nG1 Y245\n\nG91\nG1 Z-3.0 F1200\nG90\nM621 S255\nM104 S0\n");
    }
}

void xtouch_device_onUnloadFilament(lv_msg_t *m)
{
    if (xtouch_can_unload_filament())
    {
        xtouch_device_gcode_line("M620 S255\nM106 P1 S255\nM104 S250\nM17 S\nM17 X0.5 Y0.5\nG91\nG1 Y-5 F3000\nG1 Z3 F1200\nG90\nG28 X\nM17 R\nG1 X70 F21000\nG1 Y245\nG1 Y265 F3000\nG4\nM106 P1 S0\nM109 S250\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 X120 F21000\nG1 X20 Y50\nG1 Y-3\nT255\nG4\nM104 S0\nG1 X70 F3000\nG91\nG1 Z-3 F1200\nG90\nM621 S255\n");
    }
}

#endif
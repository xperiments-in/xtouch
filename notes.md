xtouch_device_print_remote_file("AMS-Silica pod_plate_1.gcode.3mf");

void xtouch_device_print_remote_file(String filename)
{

    /*
    {
    "print": {
        "sequence_id": "0",
        "command": "project_file",
        "param": "Metadata/plate_X.gcode", // X being a number, this represents which plate in a 3mf file to print
        "project_id": "0", // Always 0 for local prints
        "profile_id": "0", // Always 0 for local prints
        "task_id": "0", // Always 0 for local prints
        "subtask_id": "0", // Always 0 for local prints
        "subtask_name": "",

        "file": "", // Filename to print, not needed when "url" is specified with filepath
        "url": "file:///mnt/sdcard", // URL to print. Root path, protocol can vary. E.g., if sd card, "ftp:///myfile.3mf", "ftp:///cache/myotherfile.3mf"
        "md5": "",

        "timelapse": true,
        "bed_type": "auto", // Always "auto" for local prints
        "bed_levelling": true,
        "flow_cali": true,
        "vibration_cali": true,
        "layer_inspect": true,
        "ams_mapping": "",
        "use_ams": false
    }

}

    */
    // https://community.home-assistant.io/t/bambu-lab-x1-x1c-mqtt/489510/605
    DynamicJsonDocument json(256);
    json["print"]["command"] = "project_file";
    json["print"]["sequence_id"] = xtouch_device_next_sequence();
    json["print"]["param"] = "Metadata/plate_1.gcode";

    json["print"]["project_id"] = "0";
    json["print"]["profile_id"] = "0";
    json["print"]["task_id"] = "0";
    json["print"]["subtask_id"] = "0";
    json["print"]["subtask_name"] = "";

    json["print"]["file"] = "";
    json["print"]["url"] = "http://192.168.0.28:8080/ams_holder_plate_1.gcode.3mf";
    json["print"]["md5"] = "";

    json["print"]["timelapse"] = false;
    json["print"]["bed_type"] = "auto";
    json["print"]["bed_leveling"] = false;
    json["print"]["flow_cali"] = false;
    json["print"]["vibration_cali"] = false;
    json["print"]["layer_inspect"] = false;
    json["print"]["ams_mapping"] = "";
    json["print"]["use_ams"] = false;

    String result;
    serializeJson(json, result);
    xtouch_device_publish(result);

}

134184967

get_hms_info_version https://e.bambulab.com/GetVersion.php
download_hms_info https://e.bambulab.com/query.php?lang=en
get_hms_wiki_url https://e.bambulab.com/index.php?e=%2%&s=device_hms&lang=en
get_error_message https://e.bambulab.com/query.php?lang=en&e=134184967

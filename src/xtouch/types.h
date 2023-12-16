#ifndef _XLCD_TYPES
#define _XLCD_TYPES

#define XTOUCH_LCD_MIN_SLEEP_TIME 5

#ifdef __cplusplus
extern "C"
{
#endif

    enum XTouchPrinterSeries {
        SERIES_X1 = 0,
        SERIES_P1P,
        SERIES_UNKNOWN,
    };

    struct XTouchPanelConfig
    {
        float xCalM;
        float yCalM;
        float xCalC;
        float yCalC;
    };

    enum XTouchPrintStatus
    {
        XTOUCH_PRINT_STATUS_IDLE,
        XTOUCH_PRINT_STATUS_RUNNING,
        XTOUCH_PRINT_STATUS_PAUSED,
        XTOUCH_PRINT_STATUS_FINISHED,
        XTOUCH_PRINT_STATUS_PREPARE,
        XTOUCH_PRINT_STATUS_FAILED,
    };

    enum XTouchPrintingSpeedLevel
    {
        XTOUCH_SPEED_LEVEL_INVALID = 0,
        XTOUCH_SPEED_LEVEL_SILENCE = 1,
        XTOUCH_SPEED_LEVEL_NORMAL = 2,
        XTOUCH_SPEED_LEVEL_RAPID = 3,
        XTOUCH_SPEED_LEVEL_RAMPAGE = 4,
        XTOUCH_SPEED_LEVEL_COUNT
    };

    enum XTouchAmsStatusMain
    {
        AMS_STATUS_MAIN_IDLE = 0x00,
        AMS_STATUS_MAIN_FILAMENT_CHANGE = 0x01,
        AMS_STATUS_MAIN_RFID_IDENTIFYING = 0x02,
        AMS_STATUS_MAIN_ASSIST = 0x03,
        AMS_STATUS_MAIN_CALIBRATION = 0x04,
        AMS_STATUS_MAIN_SELF_CHECK = 0x10,
        AMS_STATUS_MAIN_DEBUG = 0x20,
        AMS_STATUS_MAIN_UNKNOWN = 0xFF,
    };

    typedef struct BambuMQTTPayload
    {
        char print_type[32];
        int home_flag;
        int hw_switch_state;
        int mc_left_time;
        int mc_print_percent;
        int mc_print_sub_stage;
        int mc_print_stage;
        int mc_print_error_code;
        int mc_print_line_number;
        int print_error;
        char printer_type[32];
        char subtask_name[32];
        int current_layer;
        int total_layers;
        int print_status;
        int queue_number;
        int gcode_file_prepare_percent;
        char obj_subtask_id[32];
        char project_id_[32];
        char profile_id_[32];
        char subtask_id_[32];
        char gcode_file[128];
        int plate_index;
        char task_id[32];
        double bed_temper;
        double bed_target_temper;
        double frame_temp;
        double nozzle_temper;
        double nozzle_target_temper;
        double chamber_temper;
        int wifi_signal;
        int cooling_fan_speed;
        int big_fan1_speed;
        int big_fan2_speed;
        int printing_speed_lvl;
        int printing_speed_mag;
        bool chamberLed;
        float nozzle_diameter;
        bool camera_recording_when_printing;
        bool camera_timelapse;
        bool has_ipcam;
        long int ams_exist_bits;
        bool ams;
        int ams_status_sub;
        int ams_status_main;
        long int ams_version;
        bool ams_support_use_ams;
        int ams_rfid_status;
        int ams_humidity;
        int ams_user_setting_hold_count;
        bool ams_insert_flag;
        bool ams_power_on_flag;
        bool ams_calibrate_remain_flag;
        bool ams_support_virtual_tray;
        bool is_ams_need_update;
        long tray_exist_bits;
        long tray_is_bbl_bits;
        long tray_read_done_bits;
        long tray_reading_bits;
        int m_ams_id;   // local ams  : "0" ~ "3"
        int m_tray_id;  // local tray id : "0" ~ "3"
        int m_tray_now; // tray_now : "0" ~ "15" or "254", "255"
        int m_tray_tar; // tray_tar : "0" ~ "15" or "255"

    } XTouchBambuStatus;

    XTouchBambuStatus bambuStatus;

    enum XTouchControlAxis
    {
        ControlAxisXY,
        ControlAxisZ,
    };

    typedef struct XTouchControlModeStruct
    {
        int inc;
        int axis;
        int target_bed_temper;
        int target_nozzle_temper;
    } XtouchControlMode;

    XtouchControlMode controlMode;

    typedef struct XTouchTouchConfigStruct
    {
        bool xTouchAuxFanEnabled;
        bool xTouchChamberFanEnabled;
        bool xTouchChamberSensorEnabled;
        int8_t xTouchChamberSensorReadingDiff;
        bool xTouchOTAEnabled;
        bool xTouchTFTFlip;
        bool xTouchTFTInvert;
        char xTouchAccessCode[9];
        char xTouchSerialNumber[16];
        char xTouchPrinterModel[32];
        char xTouchPrinterName[32];
        int xTouchBacklightLevel;
        int xTouchTFTOFFValue;
        bool xTouchWakeOnPrint;
        int currentScreenIndex;
    } XTouchConfig;

    XTouchConfig xTouchConfig;

    /* HMS */

    enum ModuleID
    {
        MODULE_UKNOWN = 0x00,
        MODULE_01 = 0x01,
        MODULE_02 = 0x02,
        MODULE_MC = 0x03,
        MODULE_04 = 0x04,
        MODULE_MAINBOARD = 0x05,
        MODULE_06 = 0x06,
        MODULE_AMS = 0x07,
        MODULE_TH = 0x08,
        MODULE_09 = 0x09,
        MODULE_10 = 0x0A,
        MODULE_11 = 0x0B,
        MODULE_XCAM = 0x0C,
        MODULE_13 = 0x0D,
        MODULE_14 = 0x0E,
        MODULE_15 = 0x0F,
        MODULE_MAX = 0x10
    };

    enum HMSMessageLevel
    {
        HMS_UNKNOWN = 0,
        HMS_FATAL = 1,
        HMS_SERIOUS = 2,
        HMS_COMMON = 3,
        HMS_INFO = 4,
        HMS_MSG_LEVEL_MAX,
    };

    typedef struct
    {
        int module_id;
        unsigned module_num;
        unsigned part_id;
        unsigned reserved;
        int msg_level;
        int msg_code;
    } HMSItem;

    typedef struct
    {
        char subtask_id[32];
        int print_error;
    } ClearErrorMessage;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
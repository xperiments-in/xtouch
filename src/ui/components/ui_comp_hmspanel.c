#include "../ui.h"
#include <stdio.h>
#include "xtouch/hms.h"

const char *hms_error_codes[] = {
    "0300010000010001: The heatbed temperature is abnormal; the heater may have a short circuit.",
    "0300010000010002: The heatbed temperature is abnormal; the heater may have an open circuit, or the thermal switch may be open.",
    "0300010000010003: The heatbed temperature is abnormal; the heater is over temperature.",
    "0300010000010006: The heatbed temperature is abnormal; the sensor may have a short circuit.",
    "0300010000010007: The heatbed temperature is abnormal; the sensor may have an open circuit.",
    "0300010000030008: The temperature of the heated bed exceeds the limit and automatically adjusts to the limit temperature.",
    "0300020000010001: The nozzle temperature is abnormal; the heater may have a short circuit.",
    "0300020000010002: The nozzle temperature is abnormal; the heater may have an open circuit.",
    "0300020000010003: The nozzle temperature is abnormal; the heater is over temperature.",
    "0300020000010006: The nozzle temperature is abnormal; the sensor may have a short circuit, please check whether the connector is properly plugged.",
    "0300020000010007: The nozzle temperature is abnormal; the sensor may have an open circuit.",
    "0300030000010001: The speed of the nozzle fan is too slow or stopped. It may be stuck or the connector is not plugged in properly.",
    "0300030000020002: ",
    "0300040000020001: The speed of the part cooling fan is too slow or stopped. It may be stuck or the connector is not plugged in properly.",
    "0300050000010001: The motor driver is overheating. Its radiator may be loose, or its cooling fan may be damaged.",
    "0300060000010001: Motor-A has an open-circuit. There may be a loose connection, or the motor may have failed.",
    "0300060000010002: Motor-A has a short-circuit. It may have failed.",
    "0300060000010003: The resistance of Motor-A is abnormal, the motor may have failed.",
    "0300070000010001: Motor-B has an open-circuit. The connection may be loose, or the motor may have failed.",
    "0300070000010002: Motor-B has a short-circuit. It may have failed.",
    "0300070000010003: The resistance of Motor-B is abnormal, the motor may have failed.",
    "0300080000010001: Motor-Z has an open-circuit. The connection may be loose, or the motor may have failed.",
    "0300080000010002: Motor-Z has a short-circuit. It may have failed.",
    "0300080000010003: The resistance of Motor-Z is abnormal, the motor may have failed.",
    "0300090000010001: Motor-E has an open-circuit. The connection may be loose, or the motor may have failed.",
    "0300090000010002: Motor-E has a short-circuit. It may have failed.",
    "0300090000010003: The resistance of Motor-E is abnormal, the motor may have failed.",
    "03000A0000010001: Heatbed force sensor 1 is too sensitive. It may be stuck between the strain arm and heatbed support, or the adjusting screw may be too tight.",
    "03000A0000010002: The signal of heatbed force sensor 1 is weak. The force sensor may be broken or have poor electric connection.",
    "03000A0000010003: The signal of heatbed force sensor 1 is too weak. The electronic connection to the sensor may be broken.",
    "03000A0000010004: An external disturbance was detected on force sensor 1. The heatbed plate may have touched something outside the heatbed.",
    "03000A0000010005: Force sensor 1 detected unexpected continuous force. The heatbed may be stuck, or the analog front end may be broken.",
    "03000B0000010001: Heatbed force sensor 2 is too sensitive. It may be stuck between the strain arm and heatbed support, or the adjusting screw may be too tight.",
    "03000B0000010002: The signal of heatbed force sensor 2 is weak. The force sensor may be broken or have poor electric connection.",
    "03000B0000010003: The signal of heatbed force sensor 2 is too weak. The electronic connection to the sensor may be broken.",
    "03000B0000010004: An external disturbance was detected on force sensor 2. The heatbed plate may have touched something outside the heatbed.",
    "03000B0000010005: Force sensor 2 detected unexpected continuous force. The heatbed may be stuck, or the analog front end may be broken.",
    "03000C0000010001: Heatbed force sensor 3 is too sensitive. It may be stuck between the strain arm and heatbed support, or the adjusting screw may be too tight.",
    "03000C0000010002: The signal of heatbed force sensor 3 is weak. The force sensor may be broken or have poor electric connection.",
    "03000C0000010003: The signal of heatbed force sensor 3 is too weak. The electronic connection to the sensor may be broken.",
    "03000C0000010004: An external disturbance was detected on force sensor 3. The heatbed plate may have touched something outside the heatbed.",
    "03000C0000010005: Force sensor 3 detected unexpected continuous force. The heatbed may be stuck, or the analog front end may be broken.",
    "03000D0000010002: Heatbed homing failed. The environmental vibration is too great.",
    "03000D0000010003: The build plate is not placed properly. Please adjust it.",
    "03000D0000010004: The build plate is not placed properly. Please adjust it.",
    "03000D0000010005: The build plate is not placed properly. Please adjust it.",
    "03000D0000010006: The build plate is not placed properly. Please adjust it.",
    "03000D0000010007: The build plate is not placed properly. Please adjust it.",
    "03000D0000010008: The build plate is not placed properly. Please adjust it.",
    "03000D0000010009: The build plate is not placed properly. Please adjust it.",
    "03000D000001000A: The build plate is not placed properly. Please adjust it.",
    "03000D000001000B: The Z axis motor seems got stuck when moving up. Please check if there is any foreign matter on the Z sliders or Z timing belt wheels .",
    "03000D0000020001: Heatbed homing abnormal. There may be a bulge on the heated bed or the nozzle tip is not clean.",
    "03000F0000010001: The accelerometer data is unavailable. The communication connection to the tool head may be broken, or the accelerometer may be damaged.",
    "0300100000020001: The resonance frequency of the X axis is low. The timing belt may be loose.",
    "0300100000020002: The resonance frequency of the X axis differ much from last calibration. Please clean the carbon rod and rerun the machine calibration later.",
    "0300110000020001: The resonance frequency of the Y axis is low. The timing belt may be loose.",
    "0300110000020002: The resonance frequency of the Y axis differs greatly from the last calibration. Please clean the carbon rod and rerun the machine calibration later.",
    "0300120000020001: The front cover of the toolhead fell off.",
    "0300130000010001: The current sensor of Motor-A is abnormal. This may be caused by a failure of the hardware sampling circuit.",
    "0300140000010001: The current sensor of Motor-B is abnormal. This may be caused by a failure of the hardware sampling circuit.",
    "0300150000010001: The current sensor of Motor-Z is abnormal. This may be caused by a failure of the hardware sampling circuit.",
    "0300160000010001: The current sensor of Motor-E is abnormal. This may be caused by a failure of the hardware sampling circuit.",
    "0300200000010001: X axis homing abnormal: please check if the tool head is stuck or the carbon rod has too much resistance.",
    "0300200000010002: Y axis homing abnormal: please check if the tool head is stuck or the Y carriage has too much resistance.",
    "0300200000010003: X axis homing abnormal: the timing belt may be loose.",
    "0300200000010004: Y axis homing abnormal: the timing belt may be loose.",
    "0300400000020001: Data transmission over the serial port is abnormal; the software system may be faulty.",
    "0300410000010001: The system voltage is unstable; triggering the power failure protection function.",
    "0500010000020001: The media pipeline is malfunctioning.",
    "0500010000020002: USB camera is not connected. Please check video camera cable connection.",
    "0500010000020003: USB camera is malfunctioning.",
    "0500010000030004: Not enough space in MicroSD Card, please clear some space.",
    "0500010000030005: MicroSD Card error: please reinsert, format or replace it.",
    "0500010000030006: Unformatted MicroSD Card: please format it.",
    "0500010000030007: Unable to record time-lapse photography without MicroSD card inserted.",
    "0500020000020001: Failed to connect internet. Please check the network connection.",
    "0500020000020002: Device login failed; please check your account information.",
    "0500020000020003: Failed to connect internet; please check the network connection.",
    "0500020000020004: Unauthorized user: please check your account information.",
    "0500020000020005: Failed to connect internet; please check the network connection.",
    "0500020000020006: Liveview service is malfunctioning; please check your network connection.",
    "0500020000020007: Liveview service login failed; please check your network connection.",
    "0500030000010001: The MC module is malfunctioning; please restart the device or check device cable connection.",
    "0500030000010002: The toolhead is malfunctioning. Please restart the device.",
    "0500030000010003: The AMS module is malfunctioning. Please restart the device.",
    "0500030000010004: Internal communication is malfunctioning. Please restart the device.",
    "0500030000010005: Internal service is malfunctioning. Please restart the device.",
    "0500030000010006: A system panic occurred. Please restart the device.",
    "0500030000010008: A system hang occurred. Please restart the device.",
    "0500030000010009: A system hang occurred. It has been recovered by automatic restart.",
    "050003000001000a: System state is abnormal; please restore factory settings.",
    "050003000001000b: The screen is malfunctioning; please restart the device.",
    "0500030000010021: Hardware incompatible, please check the laser.",
    "050003000002000c: Wireless hardware error: please turn off/on WiFi or restart the device.",
    "050003000002000d: The SD Card controller is malfunctioning.",
    "0500030000020010: forward coredump, it is recovering.",
    "0500030000020011: upgrade coredump, it is recovering.",
    "0500030000020012: ipcam coredump, it is recovering.",
    "0500030000020013: xcam coredump, it is recovering.",
    "0500030000020014: bbl_screen coredump, it is recovering.",
    "0500030000020015: device_gate coredump, it is recovering.",
    "0500030000020016: device_manager coredump, it is recovering.",
    "0500030000020017: recorder coredump, it is recovering.",
    "0500030000020018: security coredump, it is recovering.",
    "0500030000020020: SD Card capacity is insufficient to cache print files.",
    "0500030000030007: A system panic occurred. It has been recovered by automatic restart.",
    "0500030000030022: MicroSD Card performance degradation has been detected. It may affect print jobs, logs, and video records. Please try to format or change the MicroSD card.",
    "0500040000010001: Failed to download print job. Please check your network connection.",
    "0500040000010002: Failed to report print state. Please check your network connection.",
    "0500040000010003: The content of print file is unreadable. Please resend the print job.",
    "0500040000010004: The print file is unauthorized.",
    "0500040000010006: Failed to resume previous print.",
    "0500040000020007: The bed temperature exceeds the filament's vitrification temperature, which may cause a nozzle clog. Please keep the front door of the printer open or lower the bed temperature.",
    "0500040000020010: The RFID-tag on AMS1 Slot1 cannot be identified.",
    "0500040000020011: The RFID-tag on AMS1 Slot2 cannot be identified.",
    "0500040000020012: The RFID-tag on AMS1 Slot3 cannot be identified.",
    "0500040000020013: The RFID-tag on AMS1 Slot4 cannot be identified.",
    "0500040000020014: The RFID-tag on AMS2 Slot1 cannot be identified.",
    "0500040000020015: The RFID-tag on AMS2 Slot2 cannot be identified.",
    "0500040000020016: The RFID-tag on AMS2 Slot3 cannot be identified.",
    "0500040000020017: The RFID-tag on AMS2 Slot4 cannot be identified.",
    "0500040000020018: The RFID-tag on AMS3 Slot1 cannot be identified.",
    "0500040000020019: The RFID-tag on AMS3 Slot2 cannot be identified.",
    "050004000002001A: The RFID-tag on AMS3 Slot3 cannot be identified.",
    "050004000002001B: The RFID-tag on AMS3 Slot4 cannot be identified.",
    "050004000002001C: The RFID-tag on AMS4 Slot1 cannot be identified.",
    "050004000002001D: The RFID-tag on AMS4 Slot2 cannot be identified.",
    "050004000002001E: The RFID-tag on AMS4 Slot3 cannot be identified.",
    "050004000002001F: The RFID-tag on AMS4 Slot4 cannot be identified.",
    "0500040000030008: The door is detected to be open.",
    "0700010000010001: The AMS1 assist motor has slipped. The extrusion wheel may be worn down, or the filament may be too thin.",
    "0700010000010003: The AMS1 assist motor torque control is malfunctioning. The current sensor may be faulty.",
    "0700010000010004: The AMS1 assist motor speed control is malfunctioning. The speed sensor may be faulty.",
    "0700010000020002: The AMS1 assist motor is overloaded. The filament may be tangled or stuck.",
    "0700020000010001: AMS1 Filament speed and length error: The filament odometry may be faulty.",
    "0700100000010001: The AMS1 slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0700100000010003: The AMS1 slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0700100000020002: The AMS1 slot1 motor is overloaded. The filament may be tangled or stuck.",
    "0700110000010001: The AMS1 slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0700110000010003: The AMS1 slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0700110000020002: The AMS1 slot2 motor is overloaded. The filament may be tangled or stuck.",
    "0700120000010001: The AMS1 slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0700120000010003: The AMS1 slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0700120000020002: The AMS1 slot3 motor is overloaded. The filament may be tangled or stuck.",
    "0700130000010001: The AMS1 slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0700130000010003: The AMS1 slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0700130000020002: The AMS1 slot4 motor is overloaded. The filament may be tangled or stuck.",
    "0700200000020001: AMS1 Slot1 filament has run out. Please insert a new filament.",
    "0700200000020002: AMS1 Slot1 is empty; please load a new filament.",
    "0700200000020003: AMS1 Slot1's filament may be broken in AMS.",
    "0700200000020004: AMS1 Slot1 filament may be broken in the tool head.",
    "0700200000020005: AMS1 Slot1 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0700200000030001: AMS1 Slot1 filament has run out. Please wait while old filament is purged.",
    "0700200000030002: AMS1 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "0700210000020001: AMS1 Slot2 filament has run out. Please insert a new filament.",
    "0700210000020002: AMS1 Slot2 is empty; please load a new filament.",
    "0700210000020003: AMS1 Slot2's filament may be broken in AMS.",
    "0700210000020004: AMS1 Slot2 filament may be broken in the tool head.",
    "0700210000020005: AMS1 Slot2 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0700210000030001: AMS1 Slot2 filament has run out. Please wait while old filament is purged.",
    "0700210000030002: AMS1 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "0700220000020001: AMS1 Slot3 filament has run out. Please insert a new filament.",
    "0700220000020002: AMS1 Slot3 is empty; please load a new filament.",
    "0700220000020003: AMS1 Slot3's filament may be broken in AMS.",
    "0700220000020004: AMS1 Slot3 filament may be broken in the tool head.",
    "0700220000020005: AMS1 Slot3 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0700220000030001: AMS1 Slot3 filament has run out. Please wait while old filament is purged.",
    "0700220000030002: AMS1 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "0700230000020001: AMS1 Slot4 filament has run out. Please insert a new filament.",
    "0700230000020002: AMS1 Slot4 is empty; please load a new filament.",
    "0700230000020003: AMS1 Slot4's filament may be broken in AMS.",
    "0700230000020004: AMS1 Slot4 filament may be broken in the tool head.",
    "0700230000020005: AMS1 Slot4 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0700230000030001: AMS1 Slot4 filament has run out. Please wait while old filament is purged.",
    "0700230000030002: AMS1 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "0700300000010001: The RFID board between AMS1 Slot1 & Slot2 has an error.",
    "0700300000010004: Encryption chip failure.",
    "0700300000020002: The RFID-tag on AMS1 Slot1 is damaged or the it's content cannot be identified.",
    "0700300000030003: RFID cannot be read because of a hardware or structural error.",
    "0700310000010001: The RFID board between AMS1 Slot3 & Slot4 has an error.",
    "0700310000010004: Encryption chip failure.",
    "0700310000020002: The RFID-tag on AMS1 Slot2 is damaged or the it's content cannot be identified.",
    "0700310000030003: RFID cannot be read because of a hardware or structural error.",
    "0700320000020002: The RFID-tag on AMS1 Slot3 is damaged or the it's content cannot be identified.",
    "0700330000020002: The RFID-tag on AMS1 Slot4 is damaged or the it's content cannot be identified.",
    "0700350000010001: The temperature and humidity sensor has an error. The chip may be faulty.",
    "0700400000020001: The filament buffer position signal lost: the cable or position sensor may be malfunctioning.",
    "0700400000020002: The filament buffer position signal error: the position sensor may be malfunctioning.",
    "0700400000020003: The AMS Hub communication is abnormal, the cable may be not well connected.",
    "0700400000020004: The filament buffer signal is abnormal; the spring may be stuck or the filament may be tangle.",
    "0700450000020001: The filament cutter sensor is malfunctioning; please check whether the connector is properly plugged in.",
    "0700450000020002: The filament cutter's cutting distance is too large. The XY motor may lose steps.",
    "0700450000020003: The filament cutter handle has not released. The handle or blade may be stuck.",
    "0700500000020001: AMS1 communication is abnormal; please check the connection cable.",
    "0700510000030001: The AMS is disabled; please load filament from spool holder.",
    "0700600000020001: The AMS1 slot1 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0700610000020001: The AMS1 slot2 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0700620000020001: The AMS1 slot3 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0700630000020001: The AMS1 slot4 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0701010000010001: The AMS2 assist motor has slipped. The extrusion wheel may be worn down, or the filament may be too thin.",
    "0701010000010003: The AMS2 assist motor torque control is malfunctioning. The current sensor may be faulty.",
    "0701010000010004: The AMS2 assist motor speed control is malfunctioning. The speed sensor may be faulty.",
    "0701010000020002: The AMS2 assist motor is overloaded. The filament may be tangled or stuck.",
    "0701020000010001: AMS2 Filament speed and length error: The filament odometry may be faulty.",
    "0701100000010001: The AMS2 slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0701100000010003: The AMS2 slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0701100000020002: The AMS2 slot1 motor is overloaded. The filament may be tangled or stuck.",
    "0701110000010001: The AMS2 slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0701110000010003: The AMS2 slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0701110000020002: The AMS2 slot2 motor is overloaded. The filament may be tangled or stuck.",
    "0701120000010001: The AMS2 slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0701120000010003: The AMS2 slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0701120000020002: The AMS2 slot3 motor is overloaded. The filament may be tangled or stuck.",
    "0701130000010001: The AMS2 slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0701130000010003: The AMS2 slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0701130000020002: The AMS2 slot4 motor is overloaded. The filament may be tangled or stuck.",
    "0701200000020001: AMS2 Slot1 filament has run out. Please insert a new filament.",
    "0701200000020002: AMS2 Slot1 is empty; please load a new filament.",
    "0701200000020003: AMS2 Slot1's filament may be broken in AMS.",
    "0701200000020004: AMS2 Slot1 filament may be broken in the tool head.",
    "0701200000020005: AMS2 Slot1 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0701200000030001: AMS2 Slot1 filament has run out. Please wait while old filament is purged.",
    "0701200000030002: AMS2 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "0701210000020001: AMS2 Slot2 filament has run out. Please insert a new filament.",
    "0701210000020002: AMS2 Slot2 is empty; please load a new filament.",
    "0701210000020003: AMS2 Slot2's filament may be broken in AMS.",
    "0701210000020004: AMS2 Slot2 filament may be broken in the tool head.",
    "0701210000020005: AMS2 Slot2 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0701210000030001: AMS2 Slot2 filament has run out. Please wait while old filament is purged.",
    "0701210000030002: AMS2 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "0701220000020001: AMS2 Slot3 filament has run out. Please insert a new filament.",
    "0701220000020002: AMS2 Slot3 is empty; please load a new filament.",
    "0701220000020003: AMS2 Slot3's filament may be broken in AMS.",
    "0701220000020004: AMS2 Slot3 filament may be broken in the tool head.",
    "0701220000020005: AMS2 Slot3 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0701220000030001: AMS2 Slot3 filament has run out. Please wait while old filament is purged.",
    "0701220000030002: AMS2 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "0701230000020001: AMS2 Slot4 filament has run out. Please insert a new filament.",
    "0701230000020002: AMS2 Slot4 is empty; please load a new filament.",
    "0701230000020003: AMS2 Slot4's filament may be broken in AMS.",
    "0701230000020004: AMS2 Slot4 filament may be broken in the tool head.",
    "0701230000020005: AMS2 Slot4 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0701230000030001: AMS2 Slot4 filament has run out. Please wait while old filament is purged.",
    "0701230000030002: AMS2 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "0701300000010001: The RFID board between AMS2 Slot1 & Slot2 has an error.",
    "0701300000010004: Encryption chip failure.",
    "0701300000020002: The RFID-tag on AMS2 Slot1 is damaged or the it's content cannot be identified.",
    "0701300000030003: RFID cannot be read because of a hardware or structural error.",
    "0701310000010001: The RFID board between AMS2 Slot3 & Slot4 has an error.",
    "0701310000010004: Encryption chip failure.",
    "0701310000020002: The RFID-tag on AMS2 Slot2 is damaged or the it's content cannot be identified.",
    "0701310000030003: RFID cannot be read because of a hardware or structural error.",
    "0701320000020002: The RFID-tag on AMS2 Slot3 is damaged or the it's content cannot be identified.",
    "0701330000020002: The RFID-tag on AMS2 Slot4 is damaged or the it's content cannot be identified.",
    "0701350000010001: The temperature and humidity sensor has an error. The chip may be faulty.",
    "0701500000020001: AMS2 communication is abnormal; please check the connection cable.",
    "0701600000020001: The AMS2 slot1 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0701610000020001: The AMS2 slot2 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0701620000020001: The AMS2 slot3 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0701630000020001: The AMS2 slot4 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0702010000010001: The AMS3 assist motor has slipped. The extrusion wheel may be worn down, or the filament may be too thin.",
    "0702010000010003: The AMS3 assist motor torque control is malfunctioning. The current sensor may be faulty.",
    "0702010000010004: The AMS3 assist motor speed control is malfunctioning. The speed sensor may be faulty.",
    "0702010000020002: The AMS3 assist motor is overloaded. The filament may be tangled or stuck.",
    "0702020000010001: AMS3 Filament speed and length error: The filament odometry may be faulty.",
    "0702100000010001: The AMS3 slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0702100000010003: The AMS3 slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0702100000020002: The AMS3 slot1 motor is overloaded. The filament may be tangled or stuck.",
    "0702110000010001: The AMS3 slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0702110000010003: The AMS3 slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0702110000020002: The AMS3 slot2 motor is overloaded. The filament may be tangled or stuck.",
    "0702120000010001: The AMS3 slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0702120000010003: The AMS3 slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0702120000020002: The AMS3 slot3 motor is overloaded. The filament may be tangled or stuck.",
    "0702130000010001: The AMS3 slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0702130000010003: The AMS3 slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0702130000020002: The AMS3 slot4 motor is overloaded. The filament may be tangled or stuck.",
    "0702200000020001: AMS3 Slot1 filament has run out. Please insert a new filament.",
    "0702200000020002: AMS3 Slot1 is empty; please load a new filament.",
    "0702200000020003: AMS3 Slot1's filament may be broken in AMS.",
    "0702200000020004: AMS3 Slot1 filament may be broken in the tool head.",
    "0702200000020005: AMS3 Slot1 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0702200000030001: AMS3 Slot1 filament has run out. Please wait while old filament is purged.",
    "0702200000030002: AMS3 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "0702210000020001: AMS3 Slot2 filament has run out. Please insert a new filament.",
    "0702210000020002: AMS3 Slot2 is empty; please load a new filament.",
    "0702210000020003: AMS3 Slot2's filament may be broken in AMS.",
    "0702210000020004: AMS3 Slot2 filament may be broken in the tool head.",
    "0702210000020005: AMS3 Slot2 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0702210000030001: AMS3 Slot2 filament has run out. Please wait while old filament is purged.",
    "0702210000030002: AMS3 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "0702220000020001: AMS3 Slot3 filament has run out. Please insert a new filament.",
    "0702220000020002: AMS3 Slot3 is empty; please load a new filament.",
    "0702220000020003: AMS3 Slot3's filament may be broken in AMS.",
    "0702220000020004: AMS3 Slot3 filament may be broken in the tool head.",
    "0702220000020005: AMS3 Slot3 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0702220000030001: AMS3 Slot3 filament has run out. Please wait while old filament is purged.",
    "0702220000030002: AMS3 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "0702230000020001: AMS3 Slot4 filament has run out. Please insert a new filament.",
    "0702230000020002: AMS3 Slot4 is empty; please load a new filament.",
    "0702230000020003: AMS3 Slot4's filament may be broken in AMS.",
    "0702230000020004: AMS3 Slot4 filament may be broken in the tool head.",
    "0702230000020005: AMS3 Slot4 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0702230000030001: AMS3 Slot4 filament has run out. Please wait while old filament is purged.",
    "0702230000030002: AMS3 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "0702300000010001: The RFID board between AMS3 Slot1 & Slot2 has an error.",
    "0702300000010004: Encryption chip failure.",
    "0702300000020002: The RFID-tag on AMS3 Slot1 is damaged or the it's content cannot be identified.",
    "0702300000030003: RFID cannot be read because of a hardware or structural error.",
    "0702310000010001: The RFID board between AMS3 Slot3 & Slot4 has an error.",
    "0702310000010004: Encryption chip failure.",
    "0702310000020002: The RFID-tag on AMS3 Slot2 is damaged or the it's content cannot be identified.",
    "0702310000030003: RFID cannot be read because of a hardware or structural error.",
    "0702320000020002: The RFID-tag on AMS3 Slot3 is damaged or the it's content cannot be identified.",
    "0702330000020002: The RFID-tag on AMS3 Slot4 is damaged or the it's content cannot be identified.",
    "0702350000010001: The temperature and humidity sensor has an error. The chip may be faulty.",
    "0702500000020001: AMS3 communication is abnormal; please check the connection cable.",
    "0702600000020001: The AMS3 slot1 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0702610000020001: The AMS3 slot2 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0702620000020001: The AMS3 slot3 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0702630000020001: The AMS3 slot4 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0703010000010001: The AMS4 assist motor has slipped. The extrusion wheel may be worn down, or the filament may be too thin.",
    "0703010000010003: The AMS4 assist motor torque control is malfunctioning. The current sensor may be faulty.",
    "0703010000010004: The AMS4 assist motor speed control is malfunctioning. The speed sensor may be faulty.",
    "0703010000020002: The AMS4 assist motor is overloaded. The filament may be tangled or stuck.",
    "0703020000010001: AMS4 Filament speed and length error: The filament odometry may be faulty.",
    "0703100000010001: The AMS4 slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0703100000010003: The AMS4 slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0703100000020002: The AMS4 slot1 motor is overloaded. The filament may be tangled or stuck.",
    "0703110000010001: The AMS4 slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0703110000010003: The AMS4 slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0703110000020002: The AMS4 slot2 motor is overloaded. The filament may be tangled or stuck.",
    "0703120000010001: The AMS4 slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0703120000010003: The AMS4 slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0703120000020002: The AMS4 slot3 motor is overloaded. The filament may be tangled or stuck.",
    "0703130000010001: The AMS4 slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "0703130000010003: The AMS4 slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "0703130000020002: The AMS4 slot4 motor is overloaded. The filament may be tangled or stuck.",
    "0703200000020001: AMS4 Slot1 filament has run out. Please insert a new filament.",
    "0703200000020002: AMS4 Slot1 is empty; please load a new filament.",
    "0703200000020003: AMS4 Slot1's filament may be broken in AMS.",
    "0703200000020004: AMS4 Slot1 filament may be broken in the tool head.",
    "0703200000020005: AMS4 Slot1 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0703200000030001: AMS4 Slot1 filament has run out. Please wait while old filament is purged.",
    "0703200000030002: AMS4 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "0703210000020001: AMS4 Slot2 filament has run out. Please insert a new filament.",
    "0703210000020002: AMS4 Slot2 is empty; please load a new filament.",
    "0703210000020003: AMS4 Slot2's filament may be broken in AMS.",
    "0703210000020004: AMS4 Slot2 filament may be broken in the tool head.",
    "0703210000020005: AMS4 Slot2 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0703210000030001: AMS4 Slot2 filament has run out. Please wait while old filament is purged.",
    "0703210000030002: AMS4 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "0703220000020001: AMS4 Slot3 filament has run out. Please insert a new filament.",
    "0703220000020002: AMS4 Slot3 is empty; please load a new filament.",
    "0703220000020003: AMS4 Slot3's filament may be broken in AMS.",
    "0703220000020004: AMS4 Slot3 filament may be broken in the tool head.",
    "0703220000020005: AMS4 Slot3 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0703220000030001: AMS4 Slot3 filament has run out. Please wait while old filament is purged.",
    "0703220000030002: AMS4 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "0703230000020001: AMS4 Slot4 filament has run out. Please insert a new filament.",
    "0703230000020002: AMS4 Slot4 is empty; please load a new filament.",
    "0703230000020003: AMS4 Slot4's filament may be broken in AMS.",
    "0703230000020004: AMS4 Slot4 filament may be broken in the tool head.",
    "0703230000020005: AMS4 Slot4 filament has run out, and purging the old filament went abnormally; please check whether the filament is stuck in the tool head.",
    "0703230000030001: AMS4 Slot4 filament has run out. Please wait while old filament is purged.",
    "0703230000030002: AMS4 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "0703300000010001: The RFID board between AMS4 Slot1 & Slot2 has an error.",
    "0703300000010004: Encryption chip failure.",
    "0703300000020002: The RFID-tag on AMS4 Slot1 is damaged or the it's content cannot be identified.",
    "0703300000030003: RFID cannot be read because of a hardware or structural error.",
    "0703310000010001: The RFID board between AMS4 Slot3 & Slot4 has an error.",
    "0703310000010004: Encryption chip failure.",
    "0703310000020002: The RFID-tag on AMS4 Slot2 is damaged or the it's content cannot be identified.",
    "0703310000030003: RFID cannot be read because of a hardware or structural error.",
    "0703320000020002: The RFID-tag on AMS4 Slot3 is damaged or the it's content cannot be identified.",
    "0703330000020002: The RFID-tag on AMS4 Slot4 is damaged or the it's content cannot be identified.",
    "0703350000010001: The temperature and humidity sensor has an error. The chip may be faulty.",
    "0703500000020001: AMS4 communication is abnormal; please check the connection cable.",
    "0703600000020001: The AMS4 slot1 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0703610000020001: The AMS4 slot2 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0703620000020001: The AMS4 slot3 is overloaded. The filament may be tangled or the spool may be stuck.",
    "0703630000020001: The AMS4 slot4 is overloaded. The filament may be tangled or the spool may be stuck.",
    "07FF200000020001: External filament has run out; please load a new filament.",
    "07FF200000020002: External filament is missing; please load a new filament.",
    "07FF200000020004: Please pull the external filament from the extruder.",
    "0C00010000010001: The Micro Lidar camera is offline. Please check the hardware connection.",
    "0C00010000010003: Synchronization between the Micro Lidar camera and MCU is abnormal. Please restart your printer.",
    "0C00010000010004: The Micro Lidar camera lens seems to be dirty. Please clean the lens.",
    "0C00010000010005: Micro Lidar camera OTP parameter is abnormal. Please contact after-sales.",
    "0C00010000010009: The chamber camera lens seems to be dirty. Please clean the lens.",
    "0C0001000001000A: The Micro Lidar LED may be broken.",
    "0C0001000001000B: Failed to calibrate Micro Lidar. Please make sure the calibration chart is clean and not occluded, and run machine calibration again.",
    "0C00010000020002: The Micro Lidar camera is malfunctioning and related functions may fail. Please contact after-sales if this message keeps appearing in multiple prints.",
    "0C00010000020006: Micro Lidar camera extrinsic parameters are abnormal. Please enable flowrate calibration in your next print.",
    "0C00010000020007: Micro Lidar laser parameters are drifted. Please re-calibrate your printer.",
    "0C00010000020008: Failed to get image from chamber camera. Spaghetti and excess chute pileup detection is not available for now.",
    "0C00020000010001: The horizontal laser is not lit. Please check if it's covered or hardware connection is normal.",
    "0C00020000010005: A new Micro Lidar was detected. Please calibrate it on Calibration page before use.",
    "0C00020000020002: The horizontal laser line is too wide. Please check if the heatbed is dirty.",
    "0C00020000020003: The horizontal laser is not bright enough at homing position. Please clean or replace heatbed if this message appears repeatedly.",
    "0C00020000020004: Nozzle height seems too low. Please check if the nozzle is worn or tilted. Re-calibrate Lidar if the nozzle has been replaced.",
    "0C00020000020006: Nozzle height seems too high. Please check if there is filament residual attached to the nozzle.",
    "0C00020000020007: The vertical laser is not lit. Please check if it's covered or hardware connection is normal.",
    "0C00020000020008: The vertical laser line is too wide. Please check if the heatbed is dirty.",
    "0C00020000020009: The vertical laser is not bright enough at homing position. Please clean or replace heatbed if this message appears repeatedly.",
    "0C00030000010009: The first layer inspection module rebooted abnormally. The inspection result may be inaccurate.",
    "0C0003000001000a: Your printer is in factory mode. Please contact Technical Support.",
    "0C00030000020001: Filament exposure metering failed because laser reflection is too weak on this material. First layer inspection may be inaccurate.",
    "0C00030000020002: First layer inspection terminated due to abnormal Lidar data.",
    "0C00030000020004: First layer inspection is not supported for the current print job.",
    "0C00030000020005: First layer inspection timed out abnormally, and the current results may be inaccurate.",
    "0C0003000002000c: The build plate localization marker is not detected. Please check if the build plate is aligned correctly.",
    "0C0003000002000F: Parts skip setted before first layer inspection, the inspection will not be supported for the current print job.",
    "0C00030000030006: Purged filament may have piled up in the excess chute. Please check and clean the excess chute.",
    "0C00030000030007: Possible first layer defects have been detected. Please check the first layer quality and decide if the job should be stopped.",
    "0C00030000030008: Possible spaghetti defects were detected. Please check the print quality and decide if the job should be stopped.",
    "0C0003000003000b: Inspecting the first layer: please wait a moment.",
    "0C0003000003000d: Some objects may have fallen down, or the extruder is not extruding normally. Please check and decide if the printing should be stopped.",
    "0C0003000003000e: Your printer seems to be printing without extruding.",
    "0C0003000003000f: Your nozzle seems to be covered with jammed or clogged material.",
    "1200100000010001: The AMS1 Slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1200100000010003: The AMS1 Slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1200100000020002: The AMS1 Slot1 motor is overloaded. The filament may be tangled or stuck.",
    "1200110000010001: The AMS1 Slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1200110000010003: The AMS1 Slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1200110000020002: The AMS1 Slot2 motor is overloaded. The filament may be tangled or stuck.",
    "1200120000010001: The AMS1 Slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1200120000010003: The AMS1 Slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1200120000020002: The AMS1 Slot3 motor is overloaded. The filament may be tangled or stuck.",
    "1200130000010001: The AMS1 Slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1200130000010003: The AMS1 Slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1200130000020002: The AMS1 Slot4 motor is overloaded. The filament may be tangled or stuck.",
    "1200200000020001: AMS1 Slot1 filament has run out; please insert a new filament.",
    "1200200000020002: AMS1 Slot1 is empty; please insert a new filament.",
    "1200200000020003: AMS1 Slot1 filament may be broken in the PTFE tube.",
    "1200200000020004: AMS1 Slot1 filament may be broken in the tool head.",
    "1200200000020005: AMS1 Slot1 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1200200000030001: AMS1 Slot1 filament has run out. Purging the old filament; please wait.",
    "1200200000030002: AMS1 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "1200210000020001: AMS1 Slot2 filament has run out; please insert a new filament.",
    "1200210000020002: AMS1 Slot2 is empty; please insert a new filament.",
    "1200210000020003: AMS1 Slot2 filament may be broken in the PTFE tube.",
    "1200210000020004: AMS1 Slot2 filament may be broken in the tool head.",
    "1200210000020005: AMS1 Slot2 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1200210000030001: AMS1 Slot2 filament has run out. Purging the old filament; please wait.",
    "1200210000030002: AMS1 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "1200220000020001: AMS1 Slot3 filament has run out; please insert a new filament.",
    "1200220000020002: AMS1 Slot3 is empty; please insert a new filament.",
    "1200220000020003: AMS1 Slot3 filament may be broken in the PTFE tube.",
    "1200220000020004: AMS1 Slot3 filament may be broken in the tool head.",
    "1200220000020005: AMS1 Slot3 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1200220000030001: AMS1 Slot3 filament has run out. Purging the old filament; please wait.",
    "1200220000030002: AMS1 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "1200230000020001: AMS1 Slot4 filament has run out; please insert a new filament.",
    "1200230000020002: AMS1 Slot4 is empty; please insert a new filament.",
    "1200230000020003: AMS1 Slot4 filament may be broken in the PTFE tube.",
    "1200230000020004: AMS1 Slot4 filament may be broken in the tool head.",
    "1200230000020005: AMS1 Slot4 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1200230000030001: AMS1 Slot4 filament has run out. Purging the old filament; please wait.",
    "1200230000030002: AMS1 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "1200240000020001: Filament may be broken in the tool head.",
    "1200250000020001: Failed to extrude the filament and the extruder may be clogged.",
    "1200300000010001: AMS1 Slot1 RFID coil is broken or the RF hardware circuit has an error.",
    "1200300000010004: RFID cannot be read because of an encryption chip failure in AMS1.",
    "1200300000020002: The RFID-tag on AMS1 Slot1 is damaged.",
    "1200300000030003: AMS1 Slot1 RFID cannot be read because of a structural error.",
    "1200310000010001: AMS1 Slot2 RFID coil is broken or the RF hardware circuit has an error.",
    "1200310000020002: The RFID-tag on AMS1 Slot2 is damaged.",
    "1200310000030003: AMS1 Slot2 RFID cannot be read because of a structural error.",
    "1200320000010001: AMS1 Slot3 RFID coil is broken or the RF hardware circuit has an error.",
    "1200320000020002: The RFID-tag on AMS1 Slot3 is damaged.",
    "1200320000030003: AMS1 Slot3 RFID cannot be read because of a structural error.",
    "1200330000010001: AMS1 Slot4 RFID coil is broken or the RF hardware circuit has an error.",
    "1200330000020002: The RFID-tag on AMS1 Slot4 is damaged.",
    "1200330000030003: AMS1 Slot4 RFID cannot be read because of a structural error.",
    "1200450000020001: The filament cutter sensor is malfunctioning. Please check whether the connector is properly plugged in.",
    "1200450000020002: The filament cutter's cutting distance is too large. The X motor may lose steps.",
    "1200450000020003: The filament cutter handle has not released. The handle or blade may be stuck.",
    "1200500000020001: AMS1 communication is abnormal; please check the connection cable.",
    "1200510000030001: AMS is disabled; please load filament from spool holder.",
    "1200700000010001: AMS1 Filament speed and length error: The slot 1 filament odometry may be faulty.",
    "1200710000010001: AMS1 Filament speed and length error: The slot 2 filament odometry may be faulty.",
    "1200720000010001: AMS1 Filament speed and length error: The slot 3 filament odometry may be faulty.",
    "1200730000010001: AMS1 Filament speed and length error: The slot 4 filament odometry may be faulty.",
    "1200800000020001: AMS1 Slot1 filament may be tangled or stuck.",
    "1200810000020001: AMS1 Slot2 filament may be tangled or stuck.",
    "1200820000020001: AMS1 Slot3 filament may be tangled or stuck.",
    "1200830000020001: AMS1 Slot4 filament may be tangled or stuck.",
    "1201100000010001: The AMS2 Slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1201100000010003: The AMS2 Slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1201100000020002: The AMS2 Slot1 motor is overloaded. The filament may be tangled or stuck.",
    "1201110000010001: The AMS2 Slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1201110000010003: The AMS2 Slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1201110000020002: The AMS2 Slot2 motor is overloaded. The filament may be tangled or stuck.",
    "1201120000010001: The AMS2 Slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1201120000010003: The AMS2 Slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1201120000020002: The AMS2 Slot3 motor is overloaded. The filament may be tangled or stuck.",
    "1201130000010001: The AMS2 Slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1201130000010003: The AMS2 Slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1201130000020002: The AMS2 Slot4 motor is overloaded. The filament may be tangled or stuck.",
    "1201200000020001: AMS2 Slot1 filament has run out; please insert a new filament.",
    "1201200000020002: AMS2 Slot1 is empty; please insert a new filament.",
    "1201200000020003: AMS2 Slot1 filament may be broken in the PTFE tube.",
    "1201200000020004: AMS2 Slot1 filament may be broken in the tool head.",
    "1201200000020005: AMS2 Slot1 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1201200000030001: AMS2 Slot1 filament has run out. Purging the old filament; please wait.",
    "1201200000030002: AMS2 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "1201210000020001: AMS2 Slot2 filament has run out; please insert a new filament.",
    "1201210000020002: AMS2 Slot2 is empty; please insert a new filament.",
    "1201210000020003: AMS2 Slot2 filament may be broken in the PTFE tube.",
    "1201210000020004: AMS2 Slot2 filament may be broken in the tool head.",
    "1201210000020005: AMS2 Slot2 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1201210000030001: AMS2 Slot2 filament has run out. Purging the old filament; please wait.",
    "1201210000030002: AMS2 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "1201220000020001: AMS2 Slot3 filament has run out; please insert a new filament.",
    "1201220000020002: AMS2 Slot3 is empty; please insert a new filament.",
    "1201220000020003: AMS2 Slot3 filament may be broken in the PTFE tube.",
    "1201220000020004: AMS2 Slot3 filament may be broken in the tool head.",
    "1201220000020005: AMS2 Slot3 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1201220000030001: AMS2 Slot3 filament has run out. Purging the old filament; please wait.",
    "1201220000030002: AMS2 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "1201230000020001: AMS2 Slot4 filament has run out; please insert a new filament.",
    "1201230000020002: AMS2 Slot4 is empty; please insert a new filament.",
    "1201230000020003: AMS2 Slot4 filament may be broken in the PTFE tube.",
    "1201230000020004: AMS2 Slot4 filament may be broken in the tool head.",
    "1201230000020005: AMS2 Slot4 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1201230000030001: AMS2 Slot4 filament has run out. Purging the old filament; please wait.",
    "1201230000030002: AMS2 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "1201300000010001: AMS2 Slot1 RFID coil is broken or the RF hardware circuit has an error.",
    "1201300000010004: RFID cannot be read because of an encryption chip failure in AMS2.",
    "1201300000020002: The RFID-tag on AMS2 Slot1 is damaged.",
    "1201300000030003: AMS2 Slot1 RFID cannot be read because of a structural error.",
    "1201310000010001: AMS2 Slot2 RFID coil is broken or the RF hardware circuit has an error.",
    "1201310000020002: The RFID-tag on AMS2 Slot2 is damaged.",
    "1201310000030003: AMS2 Slot2 RFID cannot be read because of a structural error.",
    "1201320000010001: AMS2 Slot3 RFID coil is broken or the RF hardware circuit has an error.",
    "1201320000020002: The RFID-tag on AMS2 Slot3 is damaged.",
    "1201320000030003: AMS2 Slot3 RFID cannot be read because of a structural error.",
    "1201330000010001: AMS2 Slot4 RFID coil is broken or the RF hardware circuit has an error.",
    "1201330000020002: The RFID-tag on AMS2 Slot4 is damaged.",
    "1201330000030003: AMS2 Slot4 RFID cannot be read because of a structural error.",
    "1201500000020001: AMS2 communication is abnormal; please check the connection cable.",
    "1201700000010001: AMS2 Filament speed and length error: The slot 1 filament odometry may be faulty.",
    "1201710000010001: AMS2 Filament speed and length error: The slot 2 filament odometry may be faulty.",
    "1201720000010001: AMS2 Filament speed and length error: The slot 3 filament odometry may be faulty.",
    "1201730000010001: AMS2 Filament speed and length error: The slot 4 filament odometry may be faulty.",
    "1201800000020001: AMS2 Slot1 filament may be tangled or stuck.",
    "1201810000020001: AMS2 Slot2 filament may be tangled or stuck.",
    "1201820000020001: AMS2 Slot3 filament may be tangled or stuck.",
    "1201830000020001: AMS2 Slot4 filament may be tangled or stuck.",
    "1202100000010001: The AMS3 Slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1202100000010003: The AMS3 Slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1202100000020002: The AMS3 Slot1 motor is overloaded. The filament may be tangled or stuck.",
    "1202110000010001: The AMS3 Slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1202110000010003: The AMS3 Slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1202110000020002: The AMS3 Slot2 motor is overloaded. The filament may be tangled or stuck.",
    "1202120000010001: The AMS3 Slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1202120000010003: The AMS3 Slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1202120000020002: The AMS3 Slot3 motor is overloaded. The filament may be tangled or stuck.",
    "1202130000010001: The AMS3 Slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1202130000010003: The AMS3 Slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1202130000020002: The AMS3 Slot4 motor is overloaded. The filament may be tangled or stuck.",
    "1202200000020001: AMS3 Slot1 filament has run out; please insert a new filament.",
    "1202200000020002: AMS3 Slot1 is empty; please insert a new filament.",
    "1202200000020003: AMS3 Slot1 filament may be broken in the PTFE tube.",
    "1202200000020004: AMS3 Slot1 filament may be broken in the tool head.",
    "1202200000020005: AMS3 Slot1 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1202200000030001: AMS3 Slot1 filament has run out. Purging the old filament; please wait.",
    "1202200000030002: AMS3 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "1202210000020001: AMS3 Slot2 filament has run out; please insert a new filament.",
    "1202210000020002: AMS3 Slot2 is empty; please insert a new filament.",
    "1202210000020003: AMS3 Slot2 filament may be broken in the PTFE tube.",
    "1202210000020004: AMS3 Slot2 filament may be broken in the tool head.",
    "1202210000020005: AMS3 Slot2 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1202210000030001: AMS3 Slot2 filament has run out. Purging the old filament; please wait.",
    "1202210000030002: AMS3 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "1202220000020001: AMS3 Slot3 filament has run out; please insert a new filament.",
    "1202220000020002: AMS3 Slot3 is empty; please insert a new filament.",
    "1202220000020003: AMS3 Slot3 filament may be broken in the PTFE tube.",
    "1202220000020004: AMS3 Slot3 filament may be broken in the tool head.",
    "1202220000020005: AMS3 Slot3 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1202220000030001: AMS3 Slot3 filament has run out. Purging the old filament; please wait.",
    "1202220000030002: AMS3 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "1202230000020001: AMS3 Slot4 filament has run out; please insert a new filament.",
    "1202230000020002: AMS3 Slot4 is empty; please insert a new filament.",
    "1202230000020003: AMS3 Slot4 filament may be broken in the PTFE tube.",
    "1202230000020004: AMS3 Slot4 filament may be broken in the tool head.",
    "1202230000020005: AMS3 Slot4 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1202230000030001: AMS3 Slot4 filament has run out. Purging the old filament; please wait.",
    "1202230000030002: AMS3 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "1202300000010001: AMS3 Slot1 RFID coil is broken or the RF hardware circuit has an error.",
    "1202300000010004: RFID cannot be read because of an encryption chip failure in AMS3.",
    "1202300000020002: The RFID-tag on AMS3 Slot1 is damaged.",
    "1202300000030003: AMS3 Slot1 RFID cannot be read because of a structural error.",
    "1202310000010001: AMS3 Slot2 RFID coil is broken or the RF hardware circuit has an error.",
    "1202310000020002: The RFID-tag on AMS3 Slot2 is damaged.",
    "1202310000030003: AMS3 Slot2 RFID cannot be read because of a structural error.",
    "1202320000010001: AMS3 Slot3 RFID coil is broken or the RF hardware circuit has an error.",
    "1202320000020002: The RFID-tag on AMS3 Slot3 is damaged.",
    "1202320000030003: AMS3 Slot3 RFID cannot be read because of a structural error.",
    "1202330000010001: AMS3 Slot4 RFID coil is broken or the RF hardware circuit has an error.",
    "1202330000020002: The RFID-tag on AMS3 Slot4 is damaged.",
    "1202330000030003: AMS3 Slot4 RFID cannot be read because of a structural error.",
    "1202500000020001: AMS3 communication is abnormal; please check the connection cable.",
    "1202700000010001: AMS3 Filament speed and length error: The slot 1 filament odometry may be faulty.",
    "1202710000010001: AMS3 Filament speed and length error: The slot 2 filament odometry may be faulty.",
    "1202720000010001: AMS3 Filament speed and length error: The slot 3 filament odometry may be faulty.",
    "1202730000010001: AMS3 Filament speed and length error: The slot 4 filament odometry may be faulty.",
    "1202800000020001: AMS3 Slot1 filament may be tangled or stuck.",
    "1202810000020001: AMS3 Slot2 filament may be tangled or stuck.",
    "1202820000020001: AMS3 Slot3 filament may be tangled or stuck.",
    "1202830000020001: AMS3 Slot4 filament may be tangled or stuck.",
    "1203100000010001: The AMS4 Slot1 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1203100000010003: The AMS4 Slot1 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1203100000020002: The AMS4 Slot1 motor is overloaded. The filament may be tangled or stuck.",
    "1203110000010001: The AMS4 Slot2 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1203110000010003: The AMS4 Slot2 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1203110000020002: The AMS4 Slot2 motor is overloaded. The filament may be tangled or stuck.",
    "1203120000010001: The AMS4 Slot3 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1203120000010003: The AMS4 Slot3 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1203120000020002: The AMS4 Slot3 motor is overloaded. The filament may be tangled or stuck.",
    "1203130000010001: The AMS4 Slot4 motor has slipped. The extrusion wheel may be malfunctioning, or the filament may be too thin.",
    "1203130000010003: The AMS4 Slot4 motor torque control is malfunctioning. The current sensor may be faulty.",
    "1203130000020002: The AMS4 Slot4 motor is overloaded. The filament may be tangled or stuck.",
    "1203200000020001: AMS4 Slot1 filament has run out; please insert a new filament.",
    "1203200000020002: AMS4 Slot1 is empty; please insert a new filament.",
    "1203200000020003: AMS4 Slot1 filament may be broken in the PTFE tube.",
    "1203200000020004: AMS4 Slot1 filament may be broken in the tool head.",
    "1203200000020005: AMS4 Slot1 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1203200000030001: AMS4 Slot1 filament has run out. Purging the old filament; please wait.",
    "1203200000030002: AMS4 Slot1 filament has run out and automatically switched to the slot with the same filament.",
    "1203210000020001: AMS4 Slot2 filament has run out; please insert a new filament.",
    "1203210000020002: AMS4 Slot2 is empty; please insert a new filament.",
    "1203210000020003: AMS4 Slot2 filament may be broken in the PTFE tube.",
    "1203210000020004: AMS4 Slot2 filament may be broken in the tool head.",
    "1203210000020005: AMS4 Slot2 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1203210000030001: AMS4 Slot2 filament has run out. Purging the old filament; please wait.",
    "1203210000030002: AMS4 Slot2 filament has run out and automatically switched to the slot with the same filament.",
    "1203220000020001: AMS4 Slot3 filament has run out; please insert a new filament.",
    "1203220000020002: AMS4 Slot3 is empty; please insert a new filament.",
    "1203220000020003: AMS4 Slot3 filament may be broken in the PTFE tube.",
    "1203220000020004: AMS4 Slot3 filament may be broken in the tool head.",
    "1203220000020005: AMS4 Slot3 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1203220000030001: AMS4 Slot3 filament has run out. Purging the old filament; please wait.",
    "1203220000030002: AMS4 Slot3 filament has run out and automatically switched to the slot with the same filament.",
    "1203230000020001: AMS4 Slot4 filament has run out; please insert a new filament.",
    "1203230000020002: AMS4 Slot4 is empty; please insert a new filament.",
    "1203230000020003: AMS4 Slot4 filament may be broken in the PTFE tube.",
    "1203230000020004: AMS4 Slot4 filament may be broken in the tool head.",
    "1203230000020005: AMS4 Slot4 filament has run out, and purging the old filament went abnormally; please check to see if filament is stuck in the toolhead.",
    "1203230000030001: AMS4 Slot4 filament has run out. Purging the old filament; please wait.",
    "1203230000030002: AMS4 Slot4 filament has run out and automatically switched to the slot with the same filament.",
    "1203300000010001: AMS4 Slot1 RFID coil is broken or the RF hardware circuit has an error.",
    "1203300000010004: RFID cannot be read because of an encryption chip failure in AMS4.",
    "1203300000020002: The RFID-tag on AMS4 Slot1 is damaged.",
    "1203300000030003: AMS4 Slot1 RFID cannot be read because of a structural error.",
    "1203310000010001: AMS4 Slot2 RFID coil is broken or the RF hardware circuit has an error.",
    "1203310000020002: The RFID-tag on AMS4 Slot2 is damaged.",
    "1203310000030003: AMS4 Slot2 RFID cannot be read because of a structural error.",
    "1203320000010001: AMS4 Slot3 RFID coil is broken or the RF hardware circuit has an error.",
    "1203320000020002: The RFID-tag on AMS4 Slot3 is damaged.",
    "1203320000030003: AMS4 Slot3 RFID cannot be read because of a structural error.",
    "1203330000010001: AMS4 Slot4 RFID coil is broken or the RF hardware circuit has an error.",
    "1203330000020002: The RFID-tag on AMS4 Slot4 is damaged.",
    "1203330000030003: AMS4 Slot4 RFID cannot be read because of a structural error.",
    "1203500000020001: AMS4 communication is abnormal; please check the connection cable.",
    "1203700000010001: AMS4 Filament speed and length error: The slot 1 filament odometry may be faulty.",
    "1203710000010001: AMS4 Filament speed and length error: The slot 2 filament odometry may be faulty.",
    "1203720000010001: AMS4 Filament speed and length error: The slot 3 filament odometry may be faulty.",
    "1203730000010001: AMS4 Filament speed and length error: The slot 4 filament odometry may be faulty.",
    "1203800000020001: AMS4 Slot1 filament may be tangled or stuck.",
    "1203810000020001: AMS4 Slot2 filament may be tangled or stuck.",
    "1203820000020001: AMS4 Slot3 filament may be tangled or stuck.",
    "1203830000020001: AMS4 Slot4 filament may be tangled or stuck.",
    "12FF200000020001: Filament at the spool holder has run out; please insert a new filament.",
    "12FF200000020002: Filament on the spool holder is empty; please insert a new filament.",
    "12FF200000020004: Please pull out the filament on the spool holder from the extruder.",
    "12FF200000020005: Filament may be broken in the tool head.",
    "12FF200000020006: Failed to extrude the filament and the extruder may be clogged.",
    "12FF800000020001: The filament on the spool holder may be tangled or stuck."};

// COMPONENT hmsPanel

void ui_hmsPanel_show(const char *title)
{
    lv_obj_clear_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
    lv_obj_t *titleLabel = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION);
    lv_label_set_text(titleLabel, title);
}

void ui_hmsPanel_hide()
{
    lv_obj_add_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
}

const char *ui_hmsPanel_getAMSError(unsigned long long prefix)
{

    int num_error_codes = sizeof(hms_error_codes) / sizeof(hms_error_codes[0]);

    // Convert the prefix to a hexadecimal string for comparison with error codes
    char prefix_str[17];
    sprintf(prefix_str, "%016llX", (unsigned long long)prefix);

    for (int i = 0; i < num_error_codes; i++)
    {
        if (strncmp(prefix_str, hms_error_codes[i], 16) == 0)
        {
            // Get the pointer to the error message without the prefix
            const char *error_message = hms_error_codes[i] + 18; // Skip the first 18 characters (prefix:)
            return error_message;                                // Exit the function after finding the error code
        }
    }
}
void ui_hmsPanelComponent_onXTouchHMSError(lv_event_t *e)
{
    if (!hms_isQueueEmpty())
    {
        unsigned long long item = hms_dequeue();
        unsigned int reversed_msg_level = (item >> 16) & 0x1F;

        switch (reversed_msg_level)
        {
        case 0x1:
        case 0x2:
            if (ui_hmsPanel_getAMSError(item) != "")
            {
                ui_hmsPanel_show(ui_hmsPanel_getAMSError(item));
            }
            else
            {
                ui_hmsPanelComponent_onXTouchHMSError(NULL);
            }
            break;
        default:
            ui_hmsPanelComponent_onXTouchHMSError(NULL);
            break;
        }
    }
}

void ui_event_comp_hmsPanel_hmsPanelOKClose(lv_timer_t *timer)
{
    LV_LOG_USER("ui_event_comp_hmsPanel_hmsPanelOKClose");
    ui_hmsPanelComponent_onXTouchHMSError(NULL);
}

void ui_event_comp_hmsPanel_hmsPanelOK(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hmsPanel_hide();
        if (!hms_isQueueEmpty())
        {
            lv_timer_t *ui_event_comp_hmsPanel_hmsPanelOKTimer = lv_timer_create(ui_event_comp_hmsPanel_hmsPanelOKClose, 500, NULL);
            lv_timer_set_repeat_count(ui_event_comp_hmsPanel_hmsPanelOKTimer, 1);
        }
    }
}

lv_obj_t *ui_hmsPanel_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_hmsPanel;
    cui_hmsPanel = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_hmsPanel, lv_pct(100));
    lv_obj_set_height(cui_hmsPanel, lv_pct(100));
    lv_obj_set_flex_flow(cui_hmsPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(cui_hmsPanel, LV_OBJ_FLAG_FLOATING);                                                                                                                                                                                                       /// Flags
    lv_obj_clear_flag(cui_hmsPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_hmsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_hmsPanel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_hmsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelContainer;
    cui_hmsPanelContainer = lv_obj_create(cui_hmsPanel);
    lv_obj_set_width(cui_hmsPanelContainer, lv_pct(100));
    lv_obj_set_height(cui_hmsPanelContainer, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_hmsPanelContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_hmsPanelContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_hmsPanelContainer, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_hmsPanelContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_hmsPanelContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelCaption;
    cui_hmsPanelCaption = lv_label_create(cui_hmsPanelContainer);

    lv_obj_set_height(cui_hmsPanelCaption, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelCaption, 1);
    lv_label_set_text(cui_hmsPanelCaption, "Are you sure?");
    lv_label_set_long_mode(cui_hmsPanelCaption, LV_LABEL_LONG_WRAP);
    lv_obj_clear_flag(cui_hmsPanelCaption, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelCaption, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_left(cui_hmsPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelOK;
    cui_hmsPanelOK = lv_label_create(cui_hmsPanelContainer);
    lv_obj_set_height(cui_hmsPanelOK, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelOK, 1);
    lv_obj_set_flex_flow(cui_hmsPanelOK, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelOK, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_hmsPanelOK, "q");
    lv_obj_add_flag(cui_hmsPanelOK, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_hmsPanelOK, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelOK, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelOK, &ui_font_xlcdmin, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_hmsPanelOK, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelOK, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelOK, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_hmsPanelOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelOKLabel;
    cui_hmsPanelOKLabel = lv_label_create(cui_hmsPanelOK);
    lv_obj_set_width(cui_hmsPanelOKLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_hmsPanelOKLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_hmsPanelOKLabel, "OK");
    lv_obj_clear_flag(cui_hmsPanelOKLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelOKLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelOKLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_HMSPANEL_NUM);
    children[UI_COMP_HMSPANEL_HMSPANEL] = cui_hmsPanel;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER] = cui_hmsPanelContainer;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION] = cui_hmsPanelCaption;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELNO] = cui_hmsPanelOK;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELNO1_HMSPANELNOLABEL] = cui_hmsPanelOKLabel;
    lv_obj_add_event_cb(cui_hmsPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_hmsPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_hmsPanelOK, ui_event_comp_hmsPanel_hmsPanelOK, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_hmsPanel, ui_hmsPanelComponent_onXTouchHMSError, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_HMS_ERROR, cui_hmsPanel, NULL);

    ui_comp_hmsPanel_create_hook(cui_hmsPanel);
    return cui_hmsPanel;
}

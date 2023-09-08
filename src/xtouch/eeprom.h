#ifndef _XLCD_EEPROM
#define _XLCD_EEPROM

#define XTOUCH_EEPROM_SIZE 12

#include <EEPROM.h>

#define XTOUCH_EEPROM_POS_TFTFLIP 0

void xtouch_eeprom_setup()
{
    EEPROM.begin(XTOUCH_EEPROM_SIZE);
}

void xtouch_eeprom_write(int address, byte value)
{
    EEPROM.write(address, value);
    EEPROM.commit();
}

uint8_t xtouch_eeprom_read(int address)
{
    return EEPROM.readByte(address);
}

#endif
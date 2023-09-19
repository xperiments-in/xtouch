#ifndef _XLCD_EEPROM
#define _XLCD_EEPROM

#define XTOUCH_EEPROM_SIZE 12

#include <EEPROM.h>
#include "SPIFFS.h"

#define XTOUCH_EEPROM_POS_TFTFLIP 0

void xtouch_eeprom_setup()
{
    SPIFFS.begin(true);
    delay(200);

    if (!SPIFFS.exists(xtouch_paths_eeprom))
    {
        byte inputBuffer[XTOUCH_EEPROM_SIZE];
        const uint8_t *outputBuffer = inputBuffer;

        for (int i = 0; i < XTOUCH_EEPROM_SIZE; i++)
        {
            inputBuffer[i] = 0;
        }

        File eepromFile = SPIFFS.open(xtouch_paths_eeprom, "w+");
        eepromFile.write(outputBuffer, XTOUCH_EEPROM_SIZE);
        eepromFile.close();
    }
}

void xtouch_eeprom_write(int address, byte value)
{
    byte inputBuffer[XTOUCH_EEPROM_SIZE];
    const uint8_t *outputBuffer = inputBuffer;

    File eepromFile = SPIFFS.open(xtouch_paths_eeprom, "w+");
    eepromFile.read(inputBuffer, XTOUCH_EEPROM_SIZE);
    inputBuffer[address] = value;
    eepromFile.write(outputBuffer, XTOUCH_EEPROM_SIZE);

    eepromFile.close();
}

uint8_t xtouch_eeprom_read(int address)
{
    byte inputBuffer[XTOUCH_EEPROM_SIZE];
    File eepromFile = SPIFFS.open(xtouch_paths_eeprom, FILE_READ);

    eepromFile.read(inputBuffer, XTOUCH_EEPROM_SIZE);
    uint8_t result = inputBuffer[address];
    eepromFile.close();

    return result;
}

#endif
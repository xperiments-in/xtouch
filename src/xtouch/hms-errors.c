#include "xtouch/bbl/bbl-errors.h"
#include <pgmspace.h>
#include <Arduino.h>

// Function to retrieve a value by key
const char *getValueByKey(const char *key, const char *keys[], const char *values[], int numEntries)
{
    for (int i = 0; i < numEntries; i++)
    {
        if (strcmp_P(key, (PGM_P)pgm_read_ptr(&keys[i])) == 0)
        {
            return (const char *)pgm_read_ptr(&values[i]);
        }
    }
    return (const char *)0; // Key not found
}

bool isKeyPresent(const char *key, const char *keys[], int length)
{
    for (int i = 0; i < length; i++)
    {
        // Retrieve a string from PROGMEM and compare it with the key
        if (strcmp_P(key, (PGM_P)pgm_read_ptr(&keys[i])) == 0)
        {
            return true; // Key found
        }
    }
    return false; // Key not found
}

const char *getHMSError(const char *key)
{
    return getValueByKey(key, hms_error_keys, hms_error_values, hms_error_length);
}
const char *getDeviceError(const char *key)
{
    return getValueByKey(key, device_error_keys, device_error_values, device_error_length);
}
const char *getDeviceErrorHasDone(const char *key)
{
    return getValueByKey(key, device_error_keys, device_error_values, device_error_length);
}

bool deviceErrorHasDone(const char *key)
{
    return isKeyPresent(key, message_containing_done, message_containing_done_total);
}

bool deviceErrorHasRetry(const char *key)
{
    return isKeyPresent(key, message_containing_retry, message_containing_retry_total);
}

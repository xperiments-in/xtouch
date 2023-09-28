#include "xtouch/bbl/bbl-errors.h"
#include <pgmspace.h>
#include <Arduino.h>

bool xtouch_errors_isKeyPresent(const char *key, const char *keys[], int length)
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

bool xtouch_errors_deviceErrorHasDone(const char *key)
{
    return xtouch_errors_isKeyPresent(key, message_containing_done, message_containing_done_total);
}

bool xtouch_errors_deviceErrorHasRetry(const char *key)
{
    return xtouch_errors_isKeyPresent(key, message_containing_retry, message_containing_retry_total);
}

const char *xtouch_errors_getValueByKey(const char *key, const char *keys[], const char *values[], int numEntries)
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

const char *xtouch_errors_getHMSError(const char *key)
{
    return xtouch_errors_getValueByKey(key, hms_error_keys, hms_error_values, hms_error_length);
}

const char *xtouch_errors_getDeviceError(const char *key)
{
    return xtouch_errors_getValueByKey(key, device_error_keys, device_error_values, device_error_length);
}

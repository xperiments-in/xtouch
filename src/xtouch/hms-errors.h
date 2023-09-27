#ifndef _XLCD_HMS_ERRORS
#define _XLCD_HMS_ERRORS
#ifdef __cplusplus
extern "C"
{
#endif

#include "xtouch/bbl/bbl-errors.h"
#include <pgmspace.h>
    // Function to retrieve a value by key
    const char *getValueByKey(const char *key, const char *keys[], const char *values[], int numEntries);
    bool isKeyPresent(const char *key, const char *keys[]);
    const char *getHMSError(const char *key);
    const char *getDeviceError(const char *key);
    const char *getDeviceErrorHasDone(const char *key);
    bool deviceErrorHasDone(const char *key);
    bool deviceErrorHasRetry(const char *key);
#ifdef __cplusplus
}
#endif

#endif
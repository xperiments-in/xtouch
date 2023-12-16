#ifndef _XLCD_HMS_ERRORS
#define _XLCD_HMS_ERRORS
#ifdef __cplusplus
extern "C"
{
#endif

#include "xtouch/bbl/bbl-errors.h"
#include <pgmspace.h>
    // Function to retrieve a value by key
    bool xtouch_errors_isKeyPresent(const char *key, const char *keys[], int length);
    bool xtouch_errors_deviceErrorHasDone(const char *key);
    bool xtouch_errors_deviceErrorHasRetry(const char *key);
    const char *xtouch_errors_getValueByKey(const char *key, const char *keys[], const char *values[], int numEntries);
    const char *xtouch_errors_getHMSError(const char *key);
    const char *xtouch_errors_getDeviceError(const char *key);
#ifdef __cplusplus
}
#endif

#endif
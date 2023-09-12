#ifndef _XLCD_BBLP
#define _XLCD_BBLP

#ifdef __cplusplus
extern "C"
{
    bool xtouch_bblp_is_p1p();
    bool xtouch_bblp_is_p1s();
    bool xtouch_bblp_is_p1Series();
    bool xtouch_bblp_is_x1();
    bool xtouch_bblp_is_x1c();
    bool xtouch_bblp_is_x1Series();

} /*extern "C"*/
#else
bool xtouch_bblp_is_p1p()
{
    return strcmp(xTouchConfig.xTouchPrinterModel, "C11") == 0;
}

bool xtouch_bblp_is_p1s()
{
    return strcmp(xTouchConfig.xTouchPrinterModel, "C12") == 0;
}

bool xtouch_bblp_is_p1Series()
{
    return xtouch_bblp_is_p1p() || xtouch_bblp_is_p1s();
}

bool xtouch_bblp_is_x1()
{
    return strcmp(xTouchConfig.xTouchPrinterModel, "3DPrinter-X1") == 0;
}

bool xtouch_bblp_is_x1c()
{
    return strcmp(xTouchConfig.xTouchPrinterModel, "3DPrinter-X1-Carbon") == 0;
}

bool xtouch_bblp_is_x1Series()
{
    return xtouch_bblp_is_x1() || xtouch_bblp_is_x1c();
}
#endif

#endif
#ifndef _XLCD_PAIR
#define _XLCD_PAIR

bool xtouch_pair_loop_exit = false;

void xtouch_pair_start()
{
    xtouch_ssdp_setupButtonTimer();
    xtouch_pair_loop_exit = false;
    loadScreen(5);
    while (!xtouch_pair_loop_exit)
    {
        xtouch_ssdp_loop();
        lv_timer_handler();
        lv_task_handler();
    }

    String storedCode = xtouch_ssdp_getStoredCode(xTouchConfig.xTouchSerialNumber);

    if (storedCode.length() > 0)
    {
        strcpy(xTouchConfig.xTouchAccessCode, storedCode.c_str());
    }
    else
    {
        xtouch_pair_loop_exit = false;
        loadScreen(6);
        while (!xtouch_pair_loop_exit)
        {
            lv_timer_handler();
            lv_task_handler();
        }
    }
}

void xtouch_pair_check()
{
    if (!xtouch_ssdp_is_paired())
    {
        xtouch_ssdp_start();
        xtouch_pair_start();
        loadScreen(-1);
        xtouch_ssdp_stop();
    }
}

#endif
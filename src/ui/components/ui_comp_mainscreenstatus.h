#ifndef _UI_COMP_MAINSCREENSTATUS_H
#define _UI_COMP_MAINSCREENSTATUS_H

#include "../ui.h"

#ifdef __cplusplus
extern "C"
{
#endif

// COMPONENT mainScreenStatus
#define UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUS 0
#define UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUSLOGO 1
#define UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUSCAPTION 2
#define _UI_COMP_MAINSCREENSTATUS_NUM 3
    lv_obj_t *ui_mainScreenStatus_create(lv_obj_t *comp_parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

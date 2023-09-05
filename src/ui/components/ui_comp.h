#ifndef _UI_COMP__H
#define _UI_COMP__H

#include "../ui.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void get_component_child_event_cb(lv_event_t *e);
    void del_component_child_event_cb(lv_event_t *e);

    lv_obj_t *ui_comp_get_child(lv_obj_t *comp, uint32_t child_idx);
    extern uint32_t LV_EVENT_GET_COMP_CHILD;
#include "ui_comp_sidebarcomponent.h"
#include "ui_comp_controlcomponent.h"
#include "ui_comp_homecomponent.h"
#include "ui_comp_temperaturecomponent.h"
#include "ui_comp_settingscomponent.h"
#include "ui_comp_confirmpanel.h"
#include "ui_comp_hmspanel.h"
#include "ui_comp_mainscreenstatus.h"
#include "ui_comp_filamentcomponent.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

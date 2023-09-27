#ifndef _UI_COMP_HMSPANEL_H
#define _UI_COMP_HMSPANEL_H

#include "../ui.h"

#ifdef __cplusplus
extern "C"
{
#endif

// COMPONENT hmsPanel
#define UI_COMP_HMSPANEL_HMSPANEL 0
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER 1
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION 2
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_OK 3
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_OK_LABEL 4
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_KO 5
#define UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_KO_LABEL 6
#define _UI_COMP_HMSPANEL_NUM 7
    lv_obj_t *ui_hmsPanel_create(lv_obj_t *comp_parent);
    void ui_hmsPanel_show(const char *title, bool hasDone, bool hasRetry);
    void ui_hmsPanel_hide();
    const char *ui_hmsPanel_deviceHMSError(unsigned long long prefix);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

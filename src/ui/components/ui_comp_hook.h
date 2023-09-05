#ifndef _V3CONTROLCOMP_UI_COMP_HOOK_H
#define _V3CONTROLCOMP_UI_COMP_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

    void ui_comp_sidebarComponent_create_hook(lv_obj_t *comp);
    void ui_comp_homeComponent_create_hook(lv_obj_t *comp);
    void ui_comp_temperatureComponent_create_hook(lv_obj_t *comp);
    void ui_comp_controlComponent_create_hook(lv_obj_t *comp);
    void ui_comp_settingsComponent_create_hook(lv_obj_t *comp);
    void ui_comp_confirmPanel_create_hook(lv_obj_t *comp);
    void ui_comp_hmsPanel_create_hook(lv_obj_t *comp);
    void ui_comp_mainScreenStatus_create_hook(lv_obj_t *comp);
    void ui_comp_filamentComponent_create_hook(lv_obj_t *comp);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

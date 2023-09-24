#include "ui.h"
#include "ui_helpers.h"
#include "ui_msgs.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_controlScreen
void ui_introScreen_screen_init(void);
void ui_homeScreen_screen_init(void);
void ui_temperatureScreen_screen_init(void);
void ui_controlScreen_screen_init(void);
void ui_settingsScreen_screen_init(void);
void ui_filamentScreen_screen_init(void);
void ui_accessCodeScreen_screen_init(void);
void ui_printerPairScreen_screen_init(void);

lv_obj_t *introScreen;
lv_obj_t *introScreenIcon;
lv_obj_t *introScreenCaption;

lv_obj_t *ui_sidebarComponent;
lv_obj_t *ui_homeScreen;
lv_obj_t *ui_homeComponent;
lv_obj_t *ui_temperatureScreen;
lv_obj_t *ui_temperatureComponent;
lv_obj_t *ui_controlScreen;
lv_obj_t *ui_controlComponent;
lv_obj_t *ui_settingsScreen;
lv_obj_t *ui_settingsComponent;
lv_obj_t *ui_settingsBackLightPanelSlider;
lv_obj_t *ui_settingsTFTOFFSlider;
lv_obj_t *ui_settingsTFTOFFValue;
lv_obj_t *ui_settingsTFTInvertSwitch;
lv_obj_t *ui_settingsTFTFlipSwitch;
lv_obj_t *ui_settings_auxFanSwitch;
lv_obj_t *ui_settings_chamberFanSwitch;
lv_obj_t *ui_settings_chamberSensorSwitch;
lv_obj_t *ui_settings_otaSwitch;
lv_obj_t *ui_confirmComponent; // layertop
lv_obj_t *ui_hmsComponent;     // layertop
lv_obj_t *ui_mainStatusComponent;
lv_obj_t *ui_filamentScreen;
lv_obj_t *ui_filamentComponent;
lv_obj_t *ui_accessCodeScreen;
lv_obj_t *ui_accessCodeScreenKeyboard;
lv_obj_t *ui_accessCodeInput;
lv_obj_t *ui_printerPairScreen;
lv_obj_t *ui_printerPairScreenRoller;
lv_obj_t *ui_printerPairScreenSubmitButton;
lv_obj_t *ui_mainScreenChamberTempValue;
void ui_event____initial_actions0(lv_event_t *e);
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match lvgl settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match lvgl settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_sidebarHomeButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSidebarHome(e);
    }
}
void ui_event_sidebarTempButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSidebarTemp(e);
    }
}
void ui_event_sidebarControlButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSidebarControl(e);
    }
}
void ui_event_sidebarSettingsButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSidebarSettings(e);
    }
}
void ui_event_sidebarSettingsButton1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        onSidebarSettings(e);
    }
}
void ui_event____initial_actions0(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START)
    {
        initialActions(e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_controlScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_controlScreen);
}

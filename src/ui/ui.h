#ifndef _V3CONTROLCOMP_UI_H
#define _V3CONTROLCOMP_UI_H
#include <Arduino.h>
#include "xtouch/errors.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "xtouch/types.h"

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_msgs.h"
#include "ui_helpers.h"
#include "ui_loaders.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"

  lv_timer_t *xtouch_screen_onScreenOffTimer;
  lv_timer_t *xtouch_ssdp_onButtonTimerTimer;
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
  lv_obj_t *ui_accessCodeScreen;
  lv_obj_t *ui_accessCodeScreenKeyboard;
  lv_obj_t *ui_accessCodeInput;
  lv_obj_t *ui_printerPairScreen;
  lv_obj_t *ui_temperatureComponent;
  lv_obj_t *ui_controlScreen;
  lv_obj_t *ui_controlComponent;
  lv_obj_t *ui_settingsScreen;
  lv_obj_t *ui_settingsComponent;
  lv_obj_t *ui_settingsBackLightPanelSlider;
  lv_obj_t *ui_settingsTFTOFFSlider;
  lv_obj_t *ui_settingsTFTOFFValue;
  lv_obj_t *ui_settingsTFTInvertSwitch;
  lv_obj_t *ui_settingsWOPSwitch;
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
  lv_obj_t *ui_printerPairScreenRoller;
  lv_obj_t *ui_printerPairScreenSubmitButton;
  lv_obj_t *ui_mainScreenChamberTempValue;
  void ui_event____initial_actions0(lv_event_t *e);
  lv_obj_t *ui____initial_actions0;

  LV_FONT_DECLARE(ui_font_xlcd);
  LV_FONT_DECLARE(ui_font_xlcdmin);
  LV_FONT_DECLARE(ui_font_xlcd32);
  LV_FONT_DECLARE(ui_font_xlcd48);
  LV_FONT_DECLARE(ui_font_xperiments);

  extern const lv_font_t *lv_font_small;
  extern const lv_font_t *lv_font_big;
  extern const lv_font_t *lv_icon_font_small;
  extern const lv_font_t *lv_icon_font_big;

  void ui_init(void);

  bool xtouch_bblp_is_p1p();
  bool xtouch_bblp_is_p1Series();
  bool xtouch_bblp_is_x1();
  bool xtouch_bblp_is_x1s();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

SET(SOURCES components/ui_comp_controlcomponent.c
    components/ui_comp.c
    screens/ui_controlScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    fonts/ui_font_xlcd.c
    fonts/ui_font_xlcdmin.c
    fonts/ui_font_xperiments.c)

add_library(ui ${SOURCES})

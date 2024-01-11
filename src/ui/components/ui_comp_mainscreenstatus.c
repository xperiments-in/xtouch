#include "../ui.h"

// COMPONENT mainScreenStatus

lv_obj_t *ui_mainScreenStatus_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_mainScreenStatus;
    cui_mainScreenStatus = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_mainScreenStatus, lv_pct(100));
    lv_obj_set_flex_grow(cui_mainScreenStatus, 3);
    lv_obj_set_x(cui_mainScreenStatus, 389);
    lv_obj_set_y(cui_mainScreenStatus, 177);
    lv_obj_set_flex_flow(cui_mainScreenStatus, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_mainScreenStatus, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_mainScreenStatus, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_mainScreenStatus, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_mainScreenStatus, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_mainScreenStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_mainScreenStatus, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_mainScreenStatus, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_mainScreenStatus, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_mainScreenStatus, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_mainScreenStatus, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_mainScreenStatus, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_mainScreenStatus, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenStatus, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(cui_mainScreenStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenStatusLogo;
    cui_mainScreenStatusLogo = lv_label_create(cui_mainScreenStatus);
    lv_obj_set_width(cui_mainScreenStatusLogo, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenStatusLogo, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_mainScreenStatusLogo, "4");
    lv_obj_set_style_text_font(cui_mainScreenStatusLogo, &ui_font_xperiments, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(cui_mainScreenStatusLogo, lv_color_hex(0xAAAAAA), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_mainScreenStatusCaption;
    cui_mainScreenStatusCaption = lv_label_create(cui_mainScreenStatus);
    lv_obj_set_width(cui_mainScreenStatusCaption, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_mainScreenStatusCaption, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_mainScreenStatusCaption, "N/A");
    lv_obj_set_style_text_font(cui_mainScreenStatusCaption, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_MAINSCREENSTATUS_NUM);
    children[UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUS] = cui_mainScreenStatus;
    children[UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUSLOGO] = cui_mainScreenStatusLogo;
    children[UI_COMP_MAINSCREENSTATUS_MAINSCREENSTATUSCAPTION] = cui_mainScreenStatusCaption;
    lv_obj_add_event_cb(cui_mainScreenStatus, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_mainScreenStatus, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_mainScreenStatus_create_hook(cui_mainScreenStatus);
    return cui_mainScreenStatus;
}

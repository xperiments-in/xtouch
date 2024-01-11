#include "../ui.h"

// COMPONENT confirmPanel

void (*ui_confirmPanel_showOnYes)();

void ui_confirmPanel_NOOP(){};

void ui_confirmPanel_show(const char *title, void (*onYES)(void))
{
    ui_confirmPanel_showOnYes = onYES;

    lv_obj_clear_flag(ui_confirmComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
    lv_obj_t *titleLabel = ui_comp_get_child(ui_confirmComponent, UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELCAPTION);
    lv_label_set_text(titleLabel, title);

    // [](int a){
}

void ui_confirmPanel_hide()
{
    lv_obj_add_flag(ui_confirmComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
    // [](int a){
}

void ui_event_comp_confirmPanel_confirmPanelNO(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_confirmPanel = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_confirmPanel_hide();
    }
}
void ui_event_comp_confirmPanel_confirmPanelYES(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t **comp_confirmPanel = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_confirmPanel_showOnYes();
        ui_confirmPanel_hide();
        ui_confirmPanel_showOnYes = NULL;
    }
}

lv_obj_t *ui_confirmPanel_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_confirmPanel;
    cui_confirmPanel = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_confirmPanel, lv_pct(100));
    lv_obj_set_height(cui_confirmPanel, lv_pct(100));
    lv_obj_set_flex_flow(cui_confirmPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_confirmPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(cui_confirmPanel, LV_OBJ_FLAG_FLOATING);                                                                                                                                                                                                       /// Flags
    lv_obj_clear_flag(cui_confirmPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_confirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_confirmPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_confirmPanel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_confirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelContainer;
    cui_confirmPanelContainer = lv_obj_create(cui_confirmPanel);
    lv_obj_set_width(cui_confirmPanelContainer, lv_pct(100));
    lv_obj_set_height(cui_confirmPanelContainer, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_confirmPanelContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_confirmPanelContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_confirmPanelContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_confirmPanelContainer, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_confirmPanelContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_confirmPanelContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelCaption;
    cui_confirmPanelCaption = lv_label_create(cui_confirmPanelContainer);
    lv_obj_set_width(cui_confirmPanelCaption, lv_pct(100));      /// 1
    lv_obj_set_height(cui_confirmPanelCaption, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_confirmPanelCaption, "Are you sure?");
    lv_obj_clear_flag(cui_confirmPanelCaption, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelCaption, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_left(cui_confirmPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_confirmPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_confirmPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_confirmPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelNO;
    cui_confirmPanelNO = lv_label_create(cui_confirmPanelContainer);
    lv_obj_set_height(cui_confirmPanelNO, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_confirmPanelNO, 1);
    lv_obj_set_flex_flow(cui_confirmPanelNO, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_confirmPanelNO, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_confirmPanelNO, "r");
    lv_obj_add_flag(cui_confirmPanelNO, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_confirmPanelNO, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelNO, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_confirmPanelNO, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_confirmPanelNO, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_confirmPanelNO, lv_color_hex(0xAA2A00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_confirmPanelNO, lv_color_hex(0x552A00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_confirmPanelNO, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_confirmPanelNO, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_confirmPanelNO, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_confirmPanelNO, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_confirmPanelNO, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelNOLabel;
    cui_confirmPanelNOLabel = lv_label_create(cui_confirmPanelNO);
    lv_obj_set_width(cui_confirmPanelNOLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_confirmPanelNOLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_confirmPanelNOLabel, "NO");
    lv_obj_clear_flag(cui_confirmPanelNOLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelNOLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_confirmPanelNOLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelYES;
    cui_confirmPanelYES = lv_label_create(cui_confirmPanelContainer);
    lv_obj_set_height(cui_confirmPanelYES, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_confirmPanelYES, 1);
    lv_obj_set_flex_flow(cui_confirmPanelYES, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_confirmPanelYES, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_confirmPanelYES, "q");
    lv_obj_add_flag(cui_confirmPanelYES, LV_OBJ_FLAG_CLICKABLE);                                                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_confirmPanelYES, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelYES, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_confirmPanelYES, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_confirmPanelYES, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_confirmPanelYES, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_confirmPanelYES, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_confirmPanelYES, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_confirmPanelYES, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_confirmPanelYES, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_confirmPanelYES, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_confirmPanelYES, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_confirmPanelYESLabel;
    cui_confirmPanelYESLabel = lv_label_create(cui_confirmPanelYES);
    lv_obj_set_width(cui_confirmPanelYESLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_confirmPanelYESLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_confirmPanelYESLabel, "YES");
    lv_obj_clear_flag(cui_confirmPanelYESLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_confirmPanelYESLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_confirmPanelYESLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_CONFIRMPANEL_NUM);
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANEL] = cui_confirmPanel;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER] = cui_confirmPanelContainer;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELCAPTION] = cui_confirmPanelCaption;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELNO] = cui_confirmPanelNO;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELNO1_CONFIRMPANELNOLABEL] = cui_confirmPanelNOLabel;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELYES] = cui_confirmPanelYES;
    children[UI_COMP_CONFIRMPANEL_CONFIRMPANELCONTAINER_CONFIRMPANELYES_CONFIRMPANELYESLABEL] = cui_confirmPanelYESLabel;
    lv_obj_add_event_cb(cui_confirmPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_confirmPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_confirmPanelNO, ui_event_comp_confirmPanel_confirmPanelNO, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_confirmPanelYES, ui_event_comp_confirmPanel_confirmPanelYES, LV_EVENT_ALL, children);
    ui_comp_confirmPanel_create_hook(cui_confirmPanel);
    return cui_confirmPanel;
}

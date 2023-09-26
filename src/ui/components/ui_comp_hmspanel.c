#include "../ui.h"
#include <stdio.h>
#include "xtouch/hms.h"
#include "xtouch/hms-errors.h"

// COMPONENT hmsPanel

void ui_hmsPanel_show(const char *title)
{
    lv_obj_clear_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
    lv_obj_t *titleLabel = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION);
    lv_label_set_text(titleLabel, title);
}

void ui_hmsPanel_hide()
{
    lv_obj_add_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN); /// Flags
}

const char *ui_hmsPanel_getAMSError(unsigned long long prefix)
{

    int num_error_codes = sizeof(hms_error_codes) / sizeof(hms_error_codes[0]);

    // Convert the prefix to a hexadecimal string for comparison with error codes
    char prefix_str[17];
    sprintf(prefix_str, "%016llX", (unsigned long long)prefix);

    return getHMSError(prefix_str);
}

void ui_hmsPanelComponent_onXTouchHMSError(lv_event_t *e)
{
    if (!hms_isQueueEmpty())
    {
        unsigned long long item = hms_dequeue();
        unsigned int reversed_msg_level = (item >> 16) & 0x1F;

        switch (reversed_msg_level)
        {
        case HMS_FATAL:
        case HMS_SERIOUS:
            if (ui_hmsPanel_getAMSError(item) != "")
            {
                ui_hmsPanel_show(ui_hmsPanel_getAMSError(item));
            }
            else
            {
                ui_hmsPanelComponent_onXTouchHMSError(NULL);
            }
            break;
        default:
            ui_hmsPanelComponent_onXTouchHMSError(NULL);
            break;
        }
    }
}

void ui_event_comp_hmsPanel_hmsPanelOKClose(lv_timer_t *timer)
{
    LV_LOG_USER("ui_event_comp_hmsPanel_hmsPanelOKClose");
    ui_hmsPanelComponent_onXTouchHMSError(NULL);
}

void ui_event_comp_hmsPanel_hmsPanelOK(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hmsPanel_hide();
        if (!hms_isQueueEmpty())
        {
            lv_timer_t *ui_event_comp_hmsPanel_hmsPanelOKTimer = lv_timer_create(ui_event_comp_hmsPanel_hmsPanelOKClose, 500, NULL);
            lv_timer_set_repeat_count(ui_event_comp_hmsPanel_hmsPanelOKTimer, 1);
        }
    }
}

lv_obj_t *ui_hmsPanel_create(lv_obj_t *comp_parent)
{

    lv_obj_t *cui_hmsPanel;
    cui_hmsPanel = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_hmsPanel, lv_pct(100));
    lv_obj_set_height(cui_hmsPanel, lv_pct(100));
    lv_obj_set_flex_flow(cui_hmsPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(cui_hmsPanel, LV_OBJ_FLAG_FLOATING);                                                                                                                                                                                                       /// Flags
    lv_obj_clear_flag(cui_hmsPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(cui_hmsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_hmsPanel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_hmsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelContainer;
    cui_hmsPanelContainer = lv_obj_create(cui_hmsPanel);
    lv_obj_set_width(cui_hmsPanelContainer, lv_pct(100));
    lv_obj_set_height(cui_hmsPanelContainer, LV_SIZE_CONTENT); /// 50
    lv_obj_set_flex_flow(cui_hmsPanelContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(cui_hmsPanelContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(cui_hmsPanelContainer, lv_color_hex(0x555555), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_hmsPanelContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_hmsPanelContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelCaption;
    cui_hmsPanelCaption = lv_label_create(cui_hmsPanelContainer);

    lv_obj_set_height(cui_hmsPanelCaption, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelCaption, 1);
    lv_label_set_text(cui_hmsPanelCaption, "Are you sure?");
    lv_label_set_long_mode(cui_hmsPanelCaption, LV_LABEL_LONG_WRAP);
    lv_obj_clear_flag(cui_hmsPanelCaption, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelCaption, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_left(cui_hmsPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelCaption, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelCaption, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelOK;
    cui_hmsPanelOK = lv_label_create(cui_hmsPanelContainer);
    lv_obj_set_height(cui_hmsPanelOK, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelOK, 1);
    lv_obj_set_flex_flow(cui_hmsPanelOK, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelOK, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_hmsPanelOK, "q");
    lv_obj_add_flag(cui_hmsPanelOK, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_hmsPanelOK, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelOK, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelOK, &ui_font_xlcdmin, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_hmsPanelOK, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelOK, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelOK, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_hmsPanelOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelOK, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelOKLabel;
    cui_hmsPanelOKLabel = lv_label_create(cui_hmsPanelOK);
    lv_obj_set_width(cui_hmsPanelOKLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_hmsPanelOKLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_hmsPanelOKLabel, "OK");
    lv_obj_clear_flag(cui_hmsPanelOKLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelOKLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelOKLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_HMSPANEL_NUM);
    children[UI_COMP_HMSPANEL_HMSPANEL] = cui_hmsPanel;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER] = cui_hmsPanelContainer;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION] = cui_hmsPanelCaption;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELNO] = cui_hmsPanelOK;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELNO1_HMSPANELNOLABEL] = cui_hmsPanelOKLabel;
    lv_obj_add_event_cb(cui_hmsPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_hmsPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_hmsPanelOK, ui_event_comp_hmsPanel_hmsPanelOK, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_hmsPanel, ui_hmsPanelComponent_onXTouchHMSError, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_HMS_ERROR, cui_hmsPanel, NULL);

    ui_comp_hmsPanel_create_hook(cui_hmsPanel);
    return cui_hmsPanel;
}

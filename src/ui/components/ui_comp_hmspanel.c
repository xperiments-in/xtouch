#include "../ui.h"
#include <stdio.h>
#include "xtouch/hms.h"

unsigned long long ui_hmsPanel_currentError;

void ui_hmsPanel_show(const char *title, enum XtouchDialogButtonStyle btn_style)
{
    lv_obj_t *titleLabel = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION);
    lv_obj_t *confirmButton = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_CONFIRM_BUTTON);
    lv_obj_t *retryButton = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_RETRY_BUTTON);
    lv_obj_t *doneButton = ui_comp_get_child(ui_hmsComponent, UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_DONE_BUTTON);

    lv_obj_clear_flag(confirmButton, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(retryButton, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(doneButton, LV_OBJ_FLAG_HIDDEN);

    if (btn_style == CONFIRM_AND_DONE)
    {
        lv_obj_clear_flag(doneButton, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(retryButton, LV_OBJ_FLAG_HIDDEN);
    }
    else if (btn_style == CONFIRM_AND_RETRY)
    {
        lv_obj_add_flag(doneButton, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(retryButton, LV_OBJ_FLAG_HIDDEN);
    }
    else if (btn_style == DONE_AND_RETRY)
    {
        lv_obj_clear_flag(retryButton, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(doneButton, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(retryButton, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(doneButton, LV_OBJ_FLAG_HIDDEN);
    }

    lv_label_set_text(titleLabel, title);

    lv_obj_clear_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN);
}

void ui_hmsPanel_hide()
{
    lv_obj_add_flag(ui_hmsComponent, LV_OBJ_FLAG_HIDDEN);
}

const char *ui_hmsPanel_xtouch_errors_getHMSError(unsigned long long prefix)
{
    char prefix_str[17];
    sprintf(prefix_str, "%016llX", (unsigned long long)prefix);

    return xtouch_errors_getHMSError(prefix_str);
}

const char *ui_hmsPanel_deviceHMSError(unsigned long long prefix)
{
    char prefix_str[9];
    sprintf(prefix_str, "%08X", (unsigned long long)prefix);

    return xtouch_errors_getDeviceError(prefix_str);
}

void ui_hmsPanelComponent_onXTouchHMSError(lv_event_t *e)
{
    if (!hms_isQueueEmpty())
    {
        ui_hmsPanel_currentError = hms_dequeue();

        if (ui_hmsPanel_currentError != 0xFFFFFFFFFFFFFFFF)
        {
            if (ui_hmsPanel_currentError <= 0xFFFFFFFF)
            // DEVICE ERROR
            {
                char ui_hmsPanel_currentErrorString[9];
                sprintf(ui_hmsPanel_currentErrorString, "%08X", bambuStatus.print_error);
                bool hasRetry = xtouch_errors_deviceErrorHasRetry(ui_hmsPanel_currentErrorString);
                bool hasDone = xtouch_errors_deviceErrorHasDone(ui_hmsPanel_currentErrorString);
                const char *error = ui_hmsPanel_deviceHMSError(ui_hmsPanel_currentError);
                if (error != "")
                {
                    ui_hmsPanel_show(error,
                                     hasRetry ? (hasDone ? DONE_AND_RETRY : CONFIRM_AND_RETRY) : (hasDone ? CONFIRM_AND_DONE : ONLY_CONFIRM));
                }
                else
                {
                    ui_hmsPanelComponent_onXTouchHMSError(NULL);
                }
            }
            else
            // HMSERROR
            {
                unsigned int reversed_msg_level = (ui_hmsPanel_currentError >> 16) & 0x1F;
                const char *error = ui_hmsPanel_xtouch_errors_getHMSError(ui_hmsPanel_currentError);
                switch (reversed_msg_level)
                {
                case HMS_INFO:
                    if (error != "")
                    {
                        ui_hmsPanel_show(error, ONLY_CONFIRM);
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
    }
}

void ui_event_comp_hmsPanel_onButtonDequeueOnTimer(lv_timer_t *timer)
{
    ui_hmsPanelComponent_onXTouchHMSError(NULL);
}

void ui_event_comp_hmsPanel_onButtonDequeue()
{
    lv_timer_t *ui_event_comp_hmsPanel_buttonDequeueTimer = lv_timer_create(ui_event_comp_hmsPanel_onButtonDequeueOnTimer, 500, NULL);
    lv_timer_set_repeat_count(ui_event_comp_hmsPanel_buttonDequeueTimer, 1);
}

void ui_event_comp_hmsPanel_onDoneClick(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hmsPanel_hide();
        lv_msg_send(XTOUCH_COMMAND_AMS_CONTROL, "done");
        if (!hms_isQueueEmpty())
        {
            ui_event_comp_hmsPanel_onButtonDequeue();
        }
    }
}

void ui_event_comp_hmsPanel_onConfirmClick(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hmsPanel_hide();

        ClearErrorMessage clearErrorMessage;
        clearErrorMessage.print_error = ui_hmsPanel_currentError;
        strcpy(clearErrorMessage.subtask_id, bambuStatus.subtask_id_);

        lv_msg_send(XTOUCH_COMMAND_CLEAN_PRINT_ERROR, &clearErrorMessage);

        if (!hms_isQueueEmpty())
        {
            ui_event_comp_hmsPanel_onButtonDequeue();
        }
    }
}

void ui_event_comp_hmsPanel_onRetryClick(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        ui_hmsPanel_hide();
        lv_msg_send(XTOUCH_COMMAND_AMS_CONTROL, "resume");
        if (!hms_isQueueEmpty())
        {
            ui_event_comp_hmsPanel_onButtonDequeue();
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

    lv_obj_t *cui_hmsPanelRetryButton;
    cui_hmsPanelRetryButton = lv_label_create(cui_hmsPanelContainer);
    lv_obj_set_height(cui_hmsPanelRetryButton, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelRetryButton, 1);
    lv_obj_set_flex_flow(cui_hmsPanelRetryButton, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelRetryButton, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_hmsPanelRetryButton, "q");
    lv_obj_add_flag(cui_hmsPanelRetryButton, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_hmsPanelRetryButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelRetryButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelRetryButton, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_hmsPanelRetryButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelRetryButton, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelRetryButton, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_hmsPanelRetryButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_hmsPanelRetryButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelRetryButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelRetryButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelRetryButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelRetryButtonLabel;
    cui_hmsPanelRetryButtonLabel = lv_label_create(cui_hmsPanelRetryButton);
    lv_obj_set_width(cui_hmsPanelRetryButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_hmsPanelRetryButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_hmsPanelRetryButtonLabel, "Retry");
    lv_obj_clear_flag(cui_hmsPanelRetryButtonLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelRetryButtonLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelRetryButtonLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelDoneButton;
    cui_hmsPanelDoneButton = lv_label_create(cui_hmsPanelContainer);
    lv_obj_set_height(cui_hmsPanelDoneButton, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelDoneButton, 1);
    lv_obj_set_flex_flow(cui_hmsPanelDoneButton, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelDoneButton, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_hmsPanelDoneButton, "q");
    lv_obj_add_flag(cui_hmsPanelDoneButton, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_hmsPanelDoneButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelDoneButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelDoneButton, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_hmsPanelDoneButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelDoneButton, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelDoneButton, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_hmsPanelDoneButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_hmsPanelDoneButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelDoneButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelDoneButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelDoneButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelDoneButtonLabel;
    cui_hmsPanelDoneButtonLabel = lv_label_create(cui_hmsPanelDoneButton);
    lv_obj_set_width(cui_hmsPanelDoneButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_hmsPanelDoneButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_hmsPanelDoneButtonLabel, "Done");
    lv_obj_clear_flag(cui_hmsPanelDoneButtonLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelDoneButtonLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelDoneButtonLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelConfirmButton;
    cui_hmsPanelConfirmButton = lv_label_create(cui_hmsPanelContainer);
    lv_obj_set_height(cui_hmsPanelConfirmButton, LV_SIZE_CONTENT); /// 1
    lv_obj_set_flex_grow(cui_hmsPanelConfirmButton, 1);
    lv_obj_set_flex_flow(cui_hmsPanelConfirmButton, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_hmsPanelConfirmButton, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_label_set_text(cui_hmsPanelConfirmButton, "q");
    lv_obj_add_flag(cui_hmsPanelConfirmButton, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);                                                                                                                                                                      /// Flags
    lv_obj_clear_flag(cui_hmsPanelConfirmButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelConfirmButton, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelConfirmButton, lv_icon_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_hmsPanelConfirmButton, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelConfirmButton, lv_color_hex(0x2AAA00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_hmsPanelConfirmButton, lv_color_hex(0x2A5500), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(cui_hmsPanelConfirmButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_hmsPanelConfirmButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_hmsPanelConfirmButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_hmsPanelConfirmButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_hmsPanelConfirmButton, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *cui_hmsPanelConfirmButtonLabel;
    cui_hmsPanelConfirmButtonLabel = lv_label_create(cui_hmsPanelConfirmButton);
    lv_obj_set_width(cui_hmsPanelConfirmButtonLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(cui_hmsPanelConfirmButtonLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_text(cui_hmsPanelConfirmButtonLabel, "Confirm");
    lv_obj_clear_flag(cui_hmsPanelConfirmButtonLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    lv_obj_set_scrollbar_mode(cui_hmsPanelConfirmButtonLabel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(cui_hmsPanelConfirmButtonLabel, lv_font_small, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t **children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_HMSPANEL_NUM);
    children[UI_COMP_HMSPANEL_HMSPANEL] = cui_hmsPanel;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER] = cui_hmsPanelContainer;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANELCAPTION] = cui_hmsPanelCaption;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_RETRY_BUTTON] = cui_hmsPanelRetryButton;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_RETRY_BUTTON_LABEL] = cui_hmsPanelRetryButtonLabel;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_DONE_BUTTON] = cui_hmsPanelDoneButton;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_DONE_BUTTON_LABEL] = cui_hmsPanelDoneButtonLabel;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_CONFIRM_BUTTON] = cui_hmsPanelConfirmButton;
    children[UI_COMP_HMSPANEL_HMSPANELCONTAINER_HMSPANEL_CONFIRM_BUTTON_LABEL] = cui_hmsPanelConfirmButtonLabel;

    lv_obj_add_event_cb(cui_hmsPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_hmsPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);

    lv_obj_add_event_cb(cui_hmsPanelConfirmButton, ui_event_comp_hmsPanel_onConfirmClick, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_hmsPanelRetryButton, ui_event_comp_hmsPanel_onRetryClick, LV_EVENT_ALL, children);
    lv_obj_add_event_cb(cui_hmsPanelDoneButton, ui_event_comp_hmsPanel_onDoneClick, LV_EVENT_ALL, children);

    lv_obj_add_event_cb(cui_hmsPanel, ui_hmsPanelComponent_onXTouchHMSError, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(XTOUCH_ON_ERROR, cui_hmsPanel, NULL);

    ui_comp_hmsPanel_create_hook(cui_hmsPanel);
    return cui_hmsPanel;
}

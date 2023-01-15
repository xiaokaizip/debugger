//
// Created by 86136 on 2022/12/11.
//

#include "canid_forms.h"
#include "main.h"

button_struct_t button_Turnbuck_CanId;
button_struct_t button_refresh_CanId;
extern unsigned char lcd_buffer[128 * 160 * 2];

extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

extern uint16_t can_id[6];


void Button_TurnBuck_CallBack_CanId(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void CanId_Form_Init() {

    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Turnbuck_CanId, 72, 138, 48, 18, "TurnBuck");
    gui_button_init(&button_refresh_CanId, 12, 138, 48, 18, "refresh");
    button_Turnbuck_CanId.callback = Button_TurnBuck_CallBack_CanId;
    gui_printf(12 * 4, 0, C_BLACK, C_WHITE, " id");
    for (int i = 0; i < 6; i++) {
        gui_draw_hline(0, 16 * (i + 1), 128, C_BLUE);
        gui_printf(12 * 4, 16 * (i + 1) + 4, C_BLACK, C_WHITE, "0X%x", can_id[i]);
    }
    gui_draw_hline(0, 16 * 7, 128, C_BLUE);

    gui_button_update(&button_Turnbuck_CanId, button_normal_status);
    gui_button_update(&button_refresh_CanId, button_click_status);
}

void CanId_Form_Load() {
    if (key_Select_flag >= 2) {
        key_Select_flag = 0;
    }
    switch (key_Select_flag) {
        case 0:
            gui_button_update(&button_refresh_CanId, button_click_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_button_update(&button_refresh_CanId, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_click_status);
            key_Select_flag = 1;
            break;
        default:
            key_Select_flag = 0;
            break;
    }

    if (key_Select_flag == 0) {
        for (int i = 0; i < 6; i++) {
            gui_draw_hline(0, 16 * (i + 1), 128, C_BLUE);
            gui_printf(12 * 4, 16 * (i + 1) + 4, C_BLACK, C_WHITE, "0X%x", can_id[i]);
        }
    }

    if (key_Verify_flag == 1) {
        if (key_Select_flag == 1) {
            button_Turnbuck_CanId.callback(&button_Turnbuck_CanId);
        }
        key_Verify_flag = 0;
    }
}
//
// Created by 86136 on 2022/12/30.
//

#include "main.h"

button_struct_t button_start;
button_struct_t button_stop;
button_struct_t button_up;
button_struct_t button_down;
button_struct_t button_turnbuck_dail;

int16_t speed = 0;
int16_t set_speed = 1;
extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

void Button_TurnBuck_CallBack_Dail(void *object) {

    main_Form_Init();
    speed = 0;
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void Dail_Form_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);

    gui_printf(64, 32, C_BLACK, C_WHITE, "%d", set_speed);
    gui_button_init(&button_up, 12, 64, 48, 24, "up");
    gui_button_init(&button_down, 72, 64, 48, 24, "down");

    gui_button_init(&button_start, 12, 96, 48, 24, "start");
    gui_button_init(&button_stop, 72, 96, 48, 24, "stop");
    gui_button_init(&button_turnbuck_dail, 72, 128, 48, 24, "TurnBuck");
    button_turnbuck_dail.callback = Button_TurnBuck_CallBack_Dail;

    gui_button_update(&button_up, button_click_status);
    gui_button_update(&button_down, button_normal_status);
    gui_button_update(&button_start, button_normal_status);
    gui_button_update(&button_stop, button_normal_status);
    gui_button_update(&button_turnbuck_dail, button_normal_status);


}

void Dail_Form_Load() {

    switch (key_Select_flag) {
        case 0:
            gui_button_update(&button_up, button_click_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_click_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            key_Select_flag = 1;
            break;
        case 2:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_click_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            key_Select_flag = 2;
            break;
        case 3:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_click_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            key_Select_flag = 3;
            break;
        case 4:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_click_status);
            key_Select_flag = 4;
            break;
        default:
            key_Select_flag = 0;
            break;
    }

    if (key_Verify_flag == 1) {
        if (key_Select_flag == 0) {
            set_speed++;
        } else if (key_Select_flag == 1) {
            set_speed--;
        } else if (key_Select_flag == 2) {
            speed = 0;
        } else if (key_Select_flag == 3) {
            speed = 0;
        } else if (key_Select_flag == 4) {
            button_turnbuck_dail.callback(&button_turnbuck_dail);
        }
        key_Verify_flag = 0;
    }

    if (speed != 0) {
        gui_draw_rectangle(12, 12, 12, 12, C_GREEN, Filled);
    } else if (speed == 0) {
        gui_draw_rectangle(12, 12, 12, 12, C_GREEN, UnFilled);
    }
    gui_printf(64, 32, C_BLACK, C_WHITE, "%d", set_speed);

}
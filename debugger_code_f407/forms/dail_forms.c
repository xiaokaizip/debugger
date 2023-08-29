//
// Created by 86136 on 2022/12/30.
//

#include "main.h"
#include"key.h"

button_struct_t button_start;
button_struct_t button_stop;
button_struct_t button_up;
button_struct_t button_down;
button_struct_t button_turnbuck_dail;

int16_t speed = 0;
int16_t set_speed = 0;
press_key_t dail_key;
extern Forms_struct_t forms;

void Button_TurnBuck_CallBack_Dail(void *object) {

    main_Form_Init();
    speed = 0;
    forms.id = Main_Form;
    dail_key.key_select_num = 0;

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
    press_key(&dail_key, 5);
    switch (dail_key.key_select_num) {
        case 0:
            gui_button_update(&button_up, button_click_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            dail_key.key_select_num = 0;
            break;
        case 1:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_click_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            dail_key.key_select_num = 1;
            break;
        case 2:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_click_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            dail_key.key_select_num = 2;
            break;
        case 3:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_click_status);
            gui_button_update(&button_turnbuck_dail, button_normal_status);
            dail_key.key_select_num = 3;
            break;
        case 4:
            gui_button_update(&button_up, button_normal_status);
            gui_button_update(&button_down, button_normal_status);
            gui_button_update(&button_start, button_normal_status);
            gui_button_update(&button_stop, button_normal_status);
            gui_button_update(&button_turnbuck_dail, button_click_status);
            dail_key.key_select_num = 4;
            break;
        default:
            dail_key.key_select_num = 0;
            break;
    }

    if (dail_key.key_verify == 1) {
        if (dail_key.key_select_num == 0) {
            set_speed++;
        } else if (dail_key.key_select_num == 1) {
            set_speed--;
        } else if (dail_key.key_select_num == 2) {
            speed = 0;
        } else if (dail_key.key_select_num == 3) {
            speed = 0;
        } else if (dail_key.key_select_num == 4) {
            button_turnbuck_dail.callback(&button_turnbuck_dail);
        }
        dail_key.key_verify = 0;
    }

    if (speed != 0) {
        gui_draw_rectangle(12, 12, 12, 12, C_GREEN, Filled);
    } else if (speed == 0) {
        gui_draw_rectangle(12, 12, 12, 12, C_GREEN, UnFilled);
    }
    gui_printf(64, 32, C_BLACK, C_WHITE, "%d", set_speed);

}
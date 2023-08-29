//
// Created by 86136 on 2023/3/27.
//

#include "motor_forms.h"
#include "main.h"
#include "key.h"
#include "motor.h"
#include "string.h"

button_struct_t button_Turnbuck_Motor;
button_struct_t button_refresh_Motor;

press_key_t motor_key;
extern Forms_struct_t forms;

extern moto_measure_t motor_measure[8];

void refresh_can_RM_motor_data(moto_measure_t moto[8]);

void Button_TurnBuck_CallBack_Motor(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    motor_key.key_select_num = 0;

}

void Motor_Form_Init() {

    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Turnbuck_Motor, 72, 138, 48, 18, "TurnBuck");
    gui_button_init(&button_refresh_Motor, 12, 138, 48, 18, "refresh");
    button_Turnbuck_Motor.callback = Button_TurnBuck_CallBack_Motor;
    gui_printf(0, 0, C_BLACK, C_WHITE, "id   ang   rpm   hall");

    for (int i = 0; i < 7; i++) {
        gui_printf(0, 16 * (i + 1), C_BLACK, C_WHITE, " %d ", i + 1);
        gui_draw_hline(0, 16 * (i + 1), 128, C_BLUE);
    }
    gui_draw_hline(0, 16 * 7, 128, C_BLUE);

    gui_button_update(&button_Turnbuck_Motor, button_normal_status);
    gui_button_update(&button_refresh_Motor, button_click_status);
}

void Motor_Form_Load() {
    press_key(&motor_key, 2);
    switch (motor_key.key_select_num) {
        case 0:
            gui_button_update(&button_refresh_Motor, button_click_status);
            gui_button_update(&button_Turnbuck_Motor, button_normal_status);
            motor_key.key_select_num = 0;
            break;
        case 1:
            gui_button_update(&button_refresh_Motor, button_normal_status);
            gui_button_update(&button_Turnbuck_Motor, button_click_status);
            motor_key.key_select_num = 1;
            break;
        default:
            motor_key.key_select_num = 0;
            break;
    }
    for (int i = 0; i < 7; i++) {
        gui_printf(6 * 5, 16 * (i + 1) + 4, C_BLACK, C_WHITE, "    ");
        gui_printf(6 * 5, 16 * (i + 1) + 4, C_BLACK, C_WHITE, " %d", motor_measure[i].angle);
        gui_printf(6 * 10, 16 * (i + 1) + 4, C_BLACK, C_WHITE, "     ");
        gui_printf(6 * 10, 16 * (i + 1) + 4, C_BLACK, C_WHITE, " %d", motor_measure[i].speed_rpm);
        gui_printf(6 * 15, 16 * (i + 1) + 4, C_BLACK, C_WHITE, "     ");
        gui_printf(6 * 15, 16 * (i + 1) + 4, C_BLACK, C_WHITE, " %d", motor_measure[i].hall);

    }

    if (motor_key.key_verify == 1) {
        if (motor_key.key_select_num == 0) {
            refresh_can_RM_motor_data(motor_measure);
        }
        if (motor_key.key_select_num == 1) {
            button_Turnbuck_Motor.callback(&button_Turnbuck_Motor);
        }
        motor_key.key_verify = 0;
    }
}

void refresh_can_RM_motor_data(moto_measure_t moto[8]) {
    memset(moto, 0, sizeof(moto_measure_t) * 8);
}
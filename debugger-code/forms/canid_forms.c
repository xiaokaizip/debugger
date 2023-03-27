//
// Created by 86136 on 2022/12/11.
//

#include "canid_forms.h"
#include "main.h"

button_struct_t button_Imu_CanId;
button_struct_t button_Motor_CanId;
button_struct_t button_Turnbuck_CanId;
extern unsigned char lcd_buffer[128 * 160 * 2];

extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

extern uint16_t can_id[6];
extern uint16_t can_times;


void Button_TurnBuck_CallBack_CanId(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void Button_Imu_CallBack_CanId(void *object) {

    Imu_Form_Init();
    forms.id = Imu;
    key_Select_flag = 0;

}

void Button_Motor_CallBack_CanId(void *object) {

    Motor_Form_Init();
    forms.id = Motor;
    key_Select_flag = 0;

}

void CanId_Form_Init() {

    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Imu_CanId, 32, 33, 72, 24, "IMU");
    gui_button_init(&button_Motor_CanId, 32, 63, 72, 24, "motor");
    gui_button_init(&button_Turnbuck_CanId, 32, 93, 72, 24, "TurnBuck");

    button_Turnbuck_CanId.callback = Button_TurnBuck_CallBack_CanId;
    button_Imu_CanId.callback = Button_Imu_CallBack_CanId;
    button_Motor_CanId.callback = Button_Motor_CallBack_CanId;


    gui_button_update(&button_Turnbuck_CanId, button_normal_status);
    gui_button_update(&button_Imu_CanId, button_normal_status);
    gui_button_update(&button_Motor_CanId, button_normal_status);

}

void CanId_Form_Load() {
    if (key_Select_flag >= 3) {
        key_Select_flag = 0;
    }
    switch (key_Select_flag) {
        case 0:
            gui_button_update(&button_Imu_CanId, button_click_status);
            gui_button_update(&button_Motor_CanId, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_button_update(&button_Imu_CanId, button_normal_status);
            gui_button_update(&button_Motor_CanId, button_click_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            key_Select_flag = 1;
            break;
        case 2:
            gui_button_update(&button_Imu_CanId, button_normal_status);
            gui_button_update(&button_Motor_CanId, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_click_status);
            key_Select_flag = 2;
            break;
        default:
            key_Select_flag = 0;
            break;
    }

    if (key_Verify_flag == 1) {
        if (key_Select_flag == 0) {
            button_Imu_CanId.callback(&button_Imu_CanId);
        } else if (key_Select_flag == 1) {
            button_Motor_CanId.callback(&button_Motor_CanId);
        } else if (key_Select_flag == 2) {
            button_Turnbuck_CanId.callback(&button_Turnbuck_CanId);
        }
        key_Verify_flag = 0;
    }
}
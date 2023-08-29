//
// Created by 86136 on 2022/12/11.
//

#include "canid_forms.h"
#include "main.h"
#include "key.h"
#include "can_data.h"

button_struct_t button_Imu_CanId;
button_struct_t button_Motor_CanId;
button_struct_t button_all_canid;
button_struct_t button_Turnbuck_CanId;
extern unsigned char lcd_buffer[128 * 160 * 2];

press_key_t canid_key;

extern Forms_struct_t forms;


void Button_TurnBuck_CallBack_CanId(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    canid_key.key_select_num = 0;
}

void Button_Imu_CallBack_CanId(void *object) {

    Imu_Form_Init();
    forms.id = Imu;
    canid_key.key_select_num = 0;

}

void Button_Motor_CallBack_CanId(void *object) {

    Motor_Form_Init();
    forms.id = Motor;
    canid_key.key_select_num = 0;

}

void button_all_callback_canid(void *object) {

    all_canid_Form_Init();
    forms.id = AllCAN;
    canid_key.key_select_num = 0;

}

void CanId_Form_Init() {

    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Imu_CanId, 32, 33, 72, 24, "IMU");
    gui_button_init(&button_Motor_CanId, 32, 63, 72, 24, "motor");
    gui_button_init(&button_all_canid, 32, 93, 72, 24, "all");
    gui_button_init(&button_Turnbuck_CanId, 32, 123, 72, 24, "TurnBuck");

    button_Turnbuck_CanId.callback = Button_TurnBuck_CallBack_CanId;
    button_Imu_CanId.callback = Button_Imu_CallBack_CanId;
    button_Motor_CanId.callback = Button_Motor_CallBack_CanId;
    button_all_canid.callback = button_all_callback_canid;

    gui_button_update(&button_Turnbuck_CanId, button_normal_status);
    gui_button_update(&button_Imu_CanId, button_normal_status);
    gui_button_update(&button_Motor_CanId, button_normal_status);
    gui_button_update(&button_all_canid, button_normal_status);

}

void CanId_Form_Load() {
    press_key(&canid_key, 4);
    switch (canid_key.key_select_num) {
        case 0:
            gui_button_update(&button_Imu_CanId, button_click_status);
            gui_button_update(&button_Motor_CanId, button_normal_status);
            gui_button_update(&button_all_canid, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            break;
        case 1:
            gui_button_update(&button_Imu_CanId, button_normal_status);
            gui_button_update(&button_Motor_CanId, button_click_status);
            gui_button_update(&button_all_canid, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            break;
        case 2:
            gui_button_update(&button_Imu_CanId, button_normal_status);
            gui_button_update(&button_Motor_CanId, button_normal_status);
            gui_button_update(&button_all_canid, button_click_status);
            gui_button_update(&button_Turnbuck_CanId, button_normal_status);
            break;
        case 3:
            gui_button_update(&button_Imu_CanId, button_normal_status);
            gui_button_update(&button_Motor_CanId, button_normal_status);
            gui_button_update(&button_all_canid, button_normal_status);
            gui_button_update(&button_Turnbuck_CanId, button_click_status);
            break;
        default:
            break;
    }

    if (canid_key.key_verify == 1) {
        if (canid_key.key_select_num == 0) {
            button_Imu_CanId.callback(&button_Imu_CanId);
        } else if (canid_key.key_select_num == 1) {
            button_Motor_CanId.callback(&button_Motor_CanId);
        } else if (canid_key.key_select_num == 2) {
            button_all_canid.callback(&button_all_canid);
        } else if (canid_key.key_select_num == 3) {
            button_Turnbuck_CanId.callback(&button_Turnbuck_CanId);
        }
        canid_key.key_verify = 0;
    }
}
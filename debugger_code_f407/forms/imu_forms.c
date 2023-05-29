//
// Created by 86136 on 2023/3/27.
//

#include "imu_forms.h"

#include "string.h"
#include "main.h"
#include <stdio.h>
#include "BMI1088.h"

button_struct_t button_Turnbuck_Imu;
extern unsigned char lcd_buffer[128 * 160 * 2];

extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

extern uint16_t can_id[6];
extern uint16_t can_times;


float accel[3];
float gyro[3];
float mag[3];

float INS_quat[4] = {0.0f, 0.0f, 0.0f, 0.0f};
float INS_angle[3] = {0.0f, 0.0f, 0.0f};
float yaw;
float pitch;
float roll;

extern double imu_data[6];

extern uint8_t IMU_updata;


void Button_TurnBuck_CallBack_Imu(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void Imu_Form_Init() {
    // get_BIM1088_data(gyro, accel);
    AHRS_init(INS_quat, accel, mag);
    for (int i = 0; i < 3; i++) {
        mag[i] = 0;
    }
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Turnbuck_Imu, 72, 138, 48, 18, "TurnBuck");
    button_Turnbuck_Imu.callback = Button_TurnBuck_CallBack_Imu;

    gui_printf(12, 16 * 1 + 4, C_BLACK, C_WHITE, "  yaw:");
    gui_printf(12, 16 * 2 + 4, C_BLACK, C_WHITE, "pitch:");
    gui_printf(12, 16 * 3 + 4, C_BLACK, C_WHITE, " roll:");

    gui_button_update(&button_Turnbuck_Imu, button_normal_status);
}


double abs_data(double data) {

    return data < 0 ? (-data) : data;
}

void Imu_Form_Load() {

    if (can_times > 1000) {
        for (int i = 0; i < 6; i++) {
            imu_data[i] = 0;
        }
        can_times = 0;
    }
    if (IMU_updata == 0x03) {
        get_BIM1088_data(gyro, accel);
    }


    if (key_Select_flag == 0) {
        for (int i = 0; i < 3; i++) {
            gui_printf(12 * 4 + 12, 16 * (1 + i) + 4, C_BLACK, C_WHITE, "          ");
            gui_printf(12 * 4 + 12, 16 * (1 + i) + 4, C_BLACK, C_WHITE, "%.2d.%.2d",
                       (int) (INS_angle[i] * 57.3f),
                       (int) ((abs_data(INS_angle[i]) * 57.3f * 100) - (int) (abs_data(INS_angle[i]) * 57.3f) * 100));
        }


    }
    gui_button_update(&button_Turnbuck_Imu, button_click_status);

    if (key_Verify_flag == 1) {
        button_Turnbuck_Imu.callback(&button_Turnbuck_Imu);
        key_Verify_flag = 0;
    }
}
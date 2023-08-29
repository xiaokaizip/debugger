//
// Created by 86136 on 2023/3/27.
//

#include "imu_forms.h"

#include "main.h"
#include "key.h"
#include "usart.h"
#include "BMI1088.h"

struct Frame {
    float fdata[4];
    unsigned char tail[4];
};

button_struct_t button_Turnbuck_Imu;
extern unsigned char lcd_buffer[128 * 160 * 2];

press_key_t IMU_key;
extern Forms_struct_t forms;
extern float INS_angle[3];
extern bmi088_real_data_t bmi088_real_data;


void Button_TurnBuck_CallBack_Imu(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    IMU_key.key_select_num = 0;

}

struct Frame frame = {0.0f, 0.0f, 0.0f, 0.0f, 0x00, 0x00, 0x80, 0x7f};

void Imu_Form_Init() {


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
    press_key(&IMU_key, 1);

    frame.fdata[0] = bmi088_real_data.gyro[0];
    frame.fdata[1] = bmi088_real_data.gyro[1];
    frame.fdata[2] = bmi088_real_data.gyro[2];
    frame.fdata[3] = bmi088_real_data.temp;

    for (int i = 0; i < 3; i++) {
        gui_printf(12 * 4 + 12, 16 * (1 + i) + 4, C_BLACK, C_WHITE, "          ");
        gui_printf(12 * 4 + 12, 16 * (1 + i) + 4, C_BLACK, C_WHITE, "%.2d.%.2d",
                   (int) (INS_angle[i] * 57.3f),
                   (int) ((abs_data(INS_angle[i]) * 57.3f * 100) - (int) (abs_data(INS_angle[i]) * 57.3f) * 100));
    }
    gui_button_update(&button_Turnbuck_Imu, button_click_status);

    if (IMU_key.key_verify == 1) {
        button_Turnbuck_Imu.callback(&button_Turnbuck_Imu);
        IMU_key.key_verify = 0;
    }
}
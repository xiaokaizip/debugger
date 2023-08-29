//
// Created by 86136 on 2023/1/13.
//

#include "usart_forms.h"
#include "main.h"
#include "usart.h"
#include "string.h"

button_struct_t button_turnbuck_usart;
button_struct_t button_usart;
label_struct_t label_usart;
char usart_name[20] = {0};
extern uint16_t usart_times;


extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

extern uint8_t usart_data[8];

void Button_TurnBuck_CallBack_Usart(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void Button_Usart_CallBack(void *object) {
    key_Select_flag = 0;
}

void Usart_Form_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_printf(12, 16, C_BLACK, C_WHITE, "yaw:      ");
    gui_printf(12, 40, C_BLACK, C_WHITE, "pitch:      ");

}

float servo_yaw = 0;
float servo_pitch = 0;
uint8_t servo_data[4];

void Usart_Form_Load() {

    gui_printf(12, 16, C_BLACK, C_WHITE, "yaw:%2d.%2d", (int) servo_yaw,
               (int) (servo_yaw * 100) - ((int) servo_yaw * 100));
    gui_printf(12, 40, C_BLACK, C_WHITE, "pitch:%2d.%2d", (int) servo_pitch,
               (int) (servo_pitch * 100) - ((int) servo_pitch * 100));

}

void updata() {
    servo_yaw = (float) ((int16_t) servo_data[0] | (int16_t) servo_data[1] << 8) / 100.0f;
    servo_pitch = (float) ((int16_t) servo_data[2] | (int16_t) servo_data[3] << 8) / 100.0f;
    HAL_UART_Transmit(&huart4, servo_data, 4, HAL_MAX_DELAY);

}

//串口中断的回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    // HAL_UART_Transmit(&huart1,(uint8_t*)"h\n",2,HAL_MAX_DELAY);
    static uint8_t flag = 0;
    static uint8_t index = 0;
    if (usart_data[0] == 0xAA) {
        index = 0;
        flag = 1;
    } else if (flag == 1) {
        servo_data[index] = usart_data[0];
        index++;
    }
    if (index == 4) {
        updata();
        index = 0;
        flag = 0;
    }


    // servo_yaw++;
    //HAL_UART_Receive_IT(&huart1, usart_data, 1);
    HAL_UART_Receive_IT(&huart4, &usart_data[0], 1);
}














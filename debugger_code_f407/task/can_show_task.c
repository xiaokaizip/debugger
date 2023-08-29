//
// Created by 86136 on 2023/6/11.
//

#include "can_show_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "fifo.h"
#include "can_communication.h"
#include "can_data.h"
#include "usart.h"

extern fifo_s_t can_fifo;

extern can_data_t can_data_buff;
uint8_t can_data_temp[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
can_data_t can_data_show[CANID_SHOW_SIZE];

void can_show_task() {
    while (1) {
        get_can_data(&can_fifo, can_data_show);
        osDelay(100);
    }
}

void can_receive_task() {
    uint16_t Id = 0x201;
    uint8_t data = 12;
    while (1) {
        can_data_buff.id = (uint16_t) Id;
        Id++;
        if (Id > 0x208) {
            Id = 0x201;
        }
        if (can_data_buff.id == 0x201) {
            can_data_temp[0] = (uint8_t) data++;

        } else {
            can_data_temp[0] = 0x11;
        }
        memcpy(&can_data_buff.data, &can_data_temp, sizeof(can_data_buff.data));
        //HAL_UART_Transmit(&huart3, (char *) &can_data_buff, sizeof(can_data_buff), HAL_MAX_DELAY);
        fifo_s_puts(&can_fifo, (char *) &can_data_buff.id, sizeof(can_data_t));
        osDelay(200);
    }
}
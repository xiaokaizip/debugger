//
// Created by 86136 on 2023/5/21.
//

#include "can_data.h"
#include "usart.h"

extern fifo_s_t can_fifo;

void printf_fifo(can_data_t can_show_sort[CANID_SHOW_SIZE]);

uint8_t get_can_motor(fifo_s_t *can_fifo, moto_measure_t motor_measure[8]) {
    can_data_t can_data;
    if (fifo_s_used(can_fifo)) {
        fifo_s_gets(can_fifo, (char *) &can_data, sizeof(can_data_t));
        if (can_data.id >= 0x201 && can_data.id <= 0x208) {
            int i = can_data.id - 0x201;
            get_moto_measure(&motor_measure[i], can_data.data);
        }
        return 1;
    }
    return 0;

}


void canid_sort(can_data_t can_show_sort[CANID_SHOW_SIZE]) {
    for (int i = 0; i < CANID_SHOW_SIZE; i++) {
        for (int j = 0; j < CANID_SHOW_SIZE - i - 1; j++) {
            if (can_show_sort[j].id > can_show_sort[j + 1].id) {
                can_data_t can_data_temp;
                memcpy(&can_data_temp, &can_show_sort[j], sizeof(can_data_t));
                memcpy(&can_show_sort[j], &can_show_sort[j + 1], sizeof(can_data_t));
                memcpy(&can_show_sort[j + 1], &can_data_temp, sizeof(can_data_t));
            }
        }
    }
}

/**
 * 判断该id是否已经存在与数组中，若存在则直接刷新数据，如果不存在则返回1
 * @param can_show_sort
 * @param can_data_buff
 * @return
 */
unsigned char is_exits_can_array(can_data_t can_show_sort[CANID_SHOW_SIZE], can_data_t can_data_buff) {
    for (int i = 0; i < CANID_SHOW_SIZE; i++) {
        if (can_show_sort[i].id == can_data_buff.id) {
            memcpy(&can_show_sort[i], &can_data_buff, sizeof(can_data_t));
            return 0;
        }
    }
    return 1;
}

void get_can_data(fifo_s_t *can_fifo, can_data_t can_show_sort[CANID_SHOW_SIZE]) {
    can_data_t can_data_buff;
    if (fifo_s_used(can_fifo)) {
        fifo_s_gets(can_fifo, (char *) &can_data_buff, sizeof(can_data_t));
        if (is_exits_can_array(can_show_sort, can_data_buff))
            /*将没有的数据直接加入到数组的第一位*/
            memcpy(&can_show_sort[0], &can_data_buff, sizeof(can_data_t));
        canid_sort(can_show_sort);
        //printf_fifo(can_show_sort);
    }
}

void refresh_can_data(can_data_t can_show_sort[CANID_SHOW_SIZE]) {
    memset(can_show_sort, 0, CANID_SHOW_SIZE * sizeof(can_data_t));
}

void printf_fifo(can_data_t can_show_sort[CANID_SHOW_SIZE]) {
    for (int i = 0; i < CANID_SHOW_SIZE; i++) {
        HAL_UART_Transmit(&huart3, &can_show_sort[i], sizeof(can_data_t), HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart3, "\n", 1, HAL_MAX_DELAY);
    }
    HAL_UART_Transmit(&huart3, "\n", 1, HAL_MAX_DELAY);

}

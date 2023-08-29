//
// Created by 86136 on 2023/5/21.
//

#ifndef DEBUGGER_CODE_F407_CAN_DATA_H
#define DEBUGGER_CODE_F407_CAN_DATA_H

#include "fifo.h"
#include "can_communication.h"
#include "motor.h"

#define CANID_SHOW_SIZE 8

uint8_t get_can_motor(fifo_s_t *can_fifo, moto_measure_t motor_measure[8]);

void get_can_data(fifo_s_t *can_fifo, can_data_t can_show_sort[8]);

void refresh_can_data(can_data_t can_show_sort[CANID_SHOW_SIZE]);

#endif //DEBUGGER_CODE_F407_CAN_DATA_H

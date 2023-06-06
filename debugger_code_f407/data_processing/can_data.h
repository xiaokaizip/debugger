//
// Created by 86136 on 2023/5/21.
//

#ifndef DEBUGGER_CODE_F407_CAN_DATA_H
#define DEBUGGER_CODE_F407_CAN_DATA_H

#include "fifo.h"
#include "motor.h"
#include "can_communication.h"
#include "BMI1088.h"

void fifo_can_motor(fifo_s_t *can_fifo_motor, moto_measure_t motor_measure[8]);

void fifo_can_IMU(fifo_s_t *can_fifo_motor, IMU_measure_t *IMU_measure);

#endif //DEBUGGER_CODE_F407_CAN_DATA_H

//
// Created by 86136 on 2023/5/21.
//

#include "can_data.h"
#include "fifo.h"
#include "motor.h"
#include "can_communication.h"
#include "BMI1088.h"

void fifo_can_motor_IMU(fifo_s_t *can_fifo, moto_measure_t motor_measure[8], IMU_measure_t *IMU_measure) {
    can_data_t can_data;

    if (fifo_s_used(can_fifo)) {
        fifo_s_gets(can_fifo, (char *) &can_data, sizeof(can_data_t));
        if (can_data.id >= 0x201 && can_data.id <= 0x208) {
            int i = can_data.id - 0x201;
            get_moto_measure(&motor_measure[i], can_data.data);
        }
        if (can_data.id == 0x100 || can_data.id == 0x101) {
            get_BIM1088_data(IMU_measure, can_data.data, can_data.id);
        }
    }
}


//
// Created by 86136 on 2023/5/21.
//

#include "can_data.h"
#include "fifo.h"
#include "motor.h"
#include "can_communication.h"

extern fifo_s_t can_fifo;
can_data_t can_data;
moto_measure_t motor_measure[8];

void can_motor() {

    if (fifo_s_used(&can_fifo)) {
        fifo_s_gets(&can_fifo, (char *) &can_data, sizeof(can_data_t));
        if (can_data.id >= 0x201 && can_data.id <= 0x208) {
            int i = can_data.id - 0x201;
            get_moto_measure(&motor_measure[i], can_data.data);
        }
    }
}

void can_imu() {

}

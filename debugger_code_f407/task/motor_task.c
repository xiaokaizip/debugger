//
// Created by 86136 on 2023/6/13.
//

#include "motor_task.h"
#include "motor.h"
#include "can_data.h"
#include "fifo.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "pid.h"

extern fifo_s_t can_fifo_RM_motor;
moto_measure_t motor_measure[8];
//ÔöÁ¿Ê½pid
//PID_struct_init(&pid_struct, DELTA_PID, 20000, 20000, 10.0f, 0.1f, 10.0f);
pid_t_ pid_struct;


float pid[3] = {4.0f, 0.0f, 0.0f};

void motor_task() {
    PID_struct_init(&pid_struct, POSITION_PID, 20000, 20000, 4.0f, 0.0f, 0.0f);
    pid_struct.max_err = 20000.0f;

    const float set_speed = 500;
    while (1) {
        set_moto_current(0xFF, 2);
        set_gpio_state(1, 1);
        //set_moto_current();
        //get_can_motor(&can_fifo_RM_motor, motor_measure);
//        if (get_can_motor(&can_fifo_RM_motor, motor_measure)) {
//            pid_calc(&pid_struct, (float) motor_measure[1].speed_rpm, 800);
//            set_moto_current((int16_t) pid_struct.pos_out, 2);
//
//
//            //}
//            osDelay(1);
//        }
    }
}

//
// Created by 86136 on 2023/3/27.
//

#include "BMI1088.h"
#include "usart.h"
#include <math.h>
#include "fifo.h"
#include "can_communication.h"


float accel_sen = BMI088_ACCEL_6G_SEN;
float gyro_sen = BMI088_GYRO_2000_SEN;

extern fifo_s_t can_fifo_IMU;
can_data_t can_data_imu;

void get_BIM1088_data(float gyro[3], float accel[3], float *temp) {
    int16_t data_temp = 0;
    if (fifo_s_used(&can_fifo_IMU)) {
        fifo_s_gets(&can_fifo_IMU, (char *) &can_data_imu, sizeof(can_data_t));

        if (can_data_imu.id == 0x100) {
            data_temp = (int16_t) ((can_data_imu.data[1]) << 8) | can_data_imu.data[0];
            gyro[0] = (float) data_temp * gyro_sen;
            data_temp = (int16_t) ((can_data_imu.data[3]) << 8) | can_data_imu.data[2];
            gyro[1] = (float) data_temp * gyro_sen;
            data_temp = (int16_t) ((can_data_imu.data[5]) << 8) | can_data_imu.data[4];
            gyro[2] = (float) data_temp * gyro_sen;
            data_temp = (int16_t) ((can_data_imu.data[6] << 3) | (can_data_imu.data[7] >> 5));
            if (data_temp > 1023) {
                data_temp -= 2048;
            }
            *temp = (float) data_temp * BMI088_TEMP_FACTOR + BMI088_TEMP_OFFSET;
        } else if (can_data_imu.id == 0x101) {
            data_temp = (int16_t) ((can_data_imu.data[1]) << 8) | can_data_imu.data[0];
            accel[0] = data_temp * accel_sen;
            data_temp = (int16_t) ((can_data_imu.data[3]) << 8) | can_data_imu.data[2];
            accel[1] = data_temp * accel_sen;
            data_temp = (int16_t) ((can_data_imu.data[5]) << 8) | can_data_imu.data[4];
            accel[2] = data_temp * accel_sen;
        }
    }
}







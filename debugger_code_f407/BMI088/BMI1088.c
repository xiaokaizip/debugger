//
// Created by 86136 on 2023/3/27.
//
#include "motor.h"

#include "BMI1088.h"
#include "usart.h"
#include "MahonyAHRS.h"
#include <math.h>
#include "can_data.h"

extern uint8_t can_rx_data[8];

float accel_sen = BMI088_ACCEL_6G_SEN;
float gyro_sen = BMI088_GYRO_2000_SEN;

IMU_measure_t IMU_measure;
extern float mag[3];

extern float INS_quat[4];
extern float INS_angle[3];
extern fifo_s_t can_fifo_IMU;

void get_BIM1088_data(IMU_measure_t *IMU_measure, uint8_t can_data[8], uint16_t can_id) {
    int16_t data_temp = 0;
    if (can_id == 0x100) {
        data_temp = (int16_t) ((can_data[1]) << 8) | can_data[0];
        IMU_measure->accel[0] = data_temp * accel_sen;
        data_temp = (int16_t) ((can_data[3]) << 8) | can_data[2];
        IMU_measure->accel[1] = data_temp * accel_sen;
        data_temp = (int16_t) ((can_data[5]) << 8) | can_data[4];
        IMU_measure->accel[2] = data_temp * accel_sen;
    } else if (can_id == 0x100) {
        data_temp = (int16_t) ((can_data[1]) << 8) | can_data[0];
        IMU_measure->gyro[0] = (float) data_temp * gyro_sen;
        data_temp = (int16_t) ((can_data[3]) << 8) | can_data[2];
        IMU_measure->gyro[1] = (float) data_temp * gyro_sen;
        data_temp = (int16_t) ((can_data[5]) << 8) | can_data[4];
        IMU_measure->gyro[2] = (float) data_temp * gyro_sen;
    }
}


void AHRS_init(float quat[4], float accel[3], float mag[3]) {
    quat[0] = 1.0f;
    quat[1] = 0.0f;
    quat[2] = 0.0f;
    quat[3] = 0.0f;

}


void Init_IMU_attitude_algorithm() {
    AHRS_init(INS_quat, IMU_measure.accel, mag);
    IMU_measure.accel[0] = 0;
    IMU_measure.accel[1] = 0;
    IMU_measure.accel[2] = 0;
    IMU_measure.gyro[0] = 0;
    IMU_measure.gyro[1] = 0;
    IMU_measure.gyro[2] = 0;
    mag[0] = 0;
    mag[1] = 1;
    mag[2] = 0;
}


void AHRS_update(float quat[4], float time, float gyro[3], float accel[3], float mag[3]) {
    MahonyAHRSupdateIMU(quat, gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2]);
}

void get_angle(float q[4], float *yaw, float *pitch, float *roll) {
    *yaw = atan2f(2.0f * (q[0] * q[3] + q[1] * q[2]), 2.0f * (q[0] * q[0] + q[1] * q[1]) - 1.0f);
    *pitch = asinf(-2.0f * (q[1] * q[3] - q[0] * q[2]));
    *roll = atan2f(2.0f * (q[0] * q[1] + q[2] * q[3]), 2.0f * (q[0] * q[0] + q[3] * q[3]) - 1.0f);
}

/**
 * 将此函数放在定时器的中断函数中,一次来结算出IMU姿态的数据
 */
void get_IMU_attitude_algorithm_callback() {

    fifo_can_IMU(&can_fifo_IMU, &IMU_measure);
    AHRS_update(INS_quat, 1.0f / 1000.0f, IMU_measure.gyro, IMU_measure.accel, mag);
    get_angle(INS_quat, &INS_angle[0], &INS_angle[1], &INS_angle[2]);
}

/**
 * 调用此函数，以获得IMU的姿态
 * @param roll
 * @param pitch
 * @param yaw
 */
void get_IMU_attitude_algorithm_data(float *roll, float *pitch, float *yaw) {
    *roll = INS_angle[2];
    *pitch = INS_angle[1];
    *roll = INS_angle[0];
}





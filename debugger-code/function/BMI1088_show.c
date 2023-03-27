//
// Created by 86136 on 2023/3/27.
//
#include "motor.h"

#include "BMI1088_show.h"
#include "usart.h"
#include "retarget.h"

#define BMI088_ACCEL_3G_SEN 0.0009f
#define BMI088_GYRO_2000_SEN 0.0011f

extern uint8_t can_rx_data[8];
extern uint8_t can_BMI_accel_data[8];
extern uint8_t can_BMI_gyro_data[8];

double accel_x, accel_y, accel_z;
double gyro_x, gyro_y, gyro_z;


double imu_data[6];

void show_BIM1088_data() {
    int16_t data_temp = 0;


    data_temp = (int16_t) (can_BMI_accel_data[1] << 8 | can_BMI_accel_data[0]);
    accel_x = (double) data_temp * BMI088_ACCEL_3G_SEN;
    data_temp = (int16_t) (can_BMI_accel_data[3] << 8 | can_BMI_accel_data[2]);
    accel_y = (double) data_temp * BMI088_ACCEL_3G_SEN;
    data_temp = (int16_t) (can_BMI_accel_data[5] << 8 | can_BMI_accel_data[4]);
    accel_z = (double) data_temp * BMI088_ACCEL_3G_SEN;

    data_temp = (int16_t) (can_BMI_gyro_data[1] << 8 | can_BMI_gyro_data[0]);
    gyro_x = (double) data_temp * BMI088_GYRO_2000_SEN;
    data_temp = (int16_t) (can_BMI_gyro_data[3] << 8 | can_BMI_gyro_data[2]);
    gyro_y = (double) data_temp * BMI088_GYRO_2000_SEN;
    data_temp = (int16_t) (can_BMI_gyro_data[5] << 8 | can_BMI_gyro_data[4]);
    gyro_z = (double) data_temp * BMI088_GYRO_2000_SEN;


    imu_data[0] = accel_x;
    imu_data[1] = accel_y;
    imu_data[2] = accel_z;
    imu_data[3] = gyro_x;
    imu_data[4] = gyro_y;
    imu_data[5] = gyro_z;
    // printf("%lf,%lf,%lf", accel_x, accel_y, accel_z);
    printf("\n");
}
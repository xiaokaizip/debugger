//
// Created by 86136 on 2023/3/27.
//

#ifndef DEBUGGER_CODE_BMI1088_SHOW_H
#define DEBUGGER_CODE_BMI1088_SHOW_H

void set_BIM1088();

void get_BIM1088_data(float gyro[3], float accel[3]);

void AHRS_init(float quat[4], float accel[3], float mag[3]);

void AHRS_update(float quat[4], float time, float gyro[3], float accel[3], float mag[3]);

void get_angle(float q[4], float *yaw, float *pitch, float *roll);

void Show_BMI088_Attitude(float *yaw, float *pitch, float *roll);


#endif //DEBUGGER_CODE_BMI1088_SHOW_H

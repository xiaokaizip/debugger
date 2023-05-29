//
// Created by 86136 on 2023/3/27.
//

#ifndef DEBUGGER_CODE_BMI1088_H
#define DEBUGGER_CODE_BMI1088_H


#define BMI088_ACCEL_3G_SEN     0.0008974358974f
#define BMI088_ACCEL_6G_SEN     0.00179443359375f
#define BMI088_ACCEL_12G_SEN    0.0035888671875f
#define BMI088_ACCEL_24G_SEN    0.007177734375f


#define BMI088_GYRO_2000_SEN    0.00106526443603169529841533860381f
#define BMI088_GYRO_1000_SEN    0.00053263221801584764920766930190693f
#define BMI088_GYRO_500_SEN     0.00026631610900792382460383465095346f
#define BMI088_GYRO_250_SEN     0.00013315805450396191230191732547673f
#define BMI088_GYRO_125_SEN     0.000066579027251980956150958662738366f


typedef struct {
    float gyro[3];
    float accel[3];
} IMU_measure_t;

void set_BIM1088();

void get_BIM1088_data(IMU_measure_t *IMU_measure, uint8_t can_data[8], uint16_t can_id);

void AHRS_init(float quat[4], float accel[3], float mag[3]);

void AHRS_update(float quat[4], float time, float gyro[3], float accel[3], float mag[3]);

void get_angle(float q[4], float *yaw, float *pitch, float *roll);

void Show_BMI088_Attitude(float *yaw, float *pitch, float *roll);


#endif //DEBUGGER_CODE_BMI1088_H

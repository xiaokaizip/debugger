//
// Created by 58286 on 2022/7/19.
//

#ifndef MOTOR_TEST_CORE_INC_MOTOR_H_
#define MOTOR_TEST_CORE_INC_MOTOR_H_

#include "main.h"

#define CAN_ID 0x201
#define RC (1/(2*3.1415926f*10))
#define SAMPLE_FREQ 1000

#define C1 (1/(1+RC*SAMPLE_FREQ))
#define C2 (1-C1)

#define FILTER_BUF_LEN 2
typedef enum {

    CAN_3508Moto_ALL_ID = 0x200,
    CAN_3508Moto1_ID = 0x201,
    CAN_3508Moto2_ID = 0x202,
    CAN_3508Moto3_ID = 0x203,
    CAN_3508Moto4_ID = 0x204,

} CAN_3508_Moto_Message_ID;
typedef enum {

    CAN_2006Moto_ALL_ID = 0x200,
    CAN_2006Moto1_ID = 0x201,
    CAN_2006Moto2_ID = 0x202,
    CAN_2006Moto3_ID = 0x203,
    CAN_2006Moto4_ID = 0x204,

} CAN_2006_Moto_Message_ID;

typedef struct {
    int16_t speed_rpm;
    int16_t last_speed_rpm;
    int16_t real_current;
    int16_t given_current;
    uint8_t hall;
    uint16_t angle;                //abs angle range:[0,8191]
    uint16_t last_angle;    //abs angle range:[0,8191]
    uint16_t offset_angle;
    int32_t round_cnt;
    int32_t total_angle;
    uint8_t buf_idx;
    uint16_t angle_buf[FILTER_BUF_LEN];
    uint16_t fited_angle;
    uint32_t msg_cnt;
} moto_measure_t;

//电机状态的结构体
typedef struct {
    int motorType;              //结构体
    uint16_t idFlag;            //判断电机是否开启
    uint16_t id;                //电机的id
    int16_t motorSspeed;        //电机的转速
    float motorDecelration;     //电机的减速比
    float setSpeed;           //设置的转子的速度
    moto_measure_t motorMeasure;//电机信息的结构体
} motor_state_t;

extern uint8_t can_rx_data[8];
extern moto_measure_t moto_measure[5];
extern motor_state_t motor_state[5];


int16_t get_moto_measure(moto_measure_t *ptr);

void set_moto_current(int16_t current, uint16_t id);

void CAN_Id_Sort();


#endif // MOTOR_TEST_CORE_INC_MOTOR_H_

//
// Created by 58286 on 2022/7/19.
//
#include "motor.h"
#include "usart.h"


static CAN_TxHeaderTypeDef can_header;
static uint8_t can_tx_data[8];
extern CAN_HandleTypeDef hcan1;


int16_t get_moto_measure(moto_measure_t *ptr, uint8_t can_data[8]) {
    ptr->last_angle = ptr->angle;
    ptr->angle = (uint16_t) (can_data[0] << 8 | can_data[1]);
    ptr->real_current = (int16_t) (can_data[2] << 8 | can_data[3]);
    ptr->speed_rpm = C1 * ptr->real_current + C2 * ptr->last_speed_rpm;    //这里是因为两种电调对应位不一样的信息
    ptr->last_speed_rpm = ptr->speed_rpm;
    ptr->given_current = (int16_t) (can_data[4] << 8 | can_data[5]) / -5;
    ptr->hall = can_data[6];
    if (ptr->angle - ptr->last_angle > 4096)
        ptr->round_cnt--;
    else if (ptr->angle - ptr->last_angle < -4096)
        ptr->round_cnt++;
    ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;

    return ptr->speed_rpm;
}

/**
 * 将电流传输给指定id的电机
 * @param current 电机的转速
 * @param id 电机的id
 */
void set_moto_current(int16_t current, uint16_t id) {
    can_header.IDE = CAN_ID_STD;      //当该位为0时，为标准帧；当该位为1时，为拓展帧
    can_header.RTR = CAN_RTR_DATA;    //远程帧
    can_header.StdId = 0x200;         //ID
    can_header.DLC = 8;               //数据位

    can_tx_data[(id - 1) * 2] = current >> 8;
    can_tx_data[(id - 1) * 2 + 1] = current & 0xFF;

    uint32_t tx_mailbox;
    HAL_CAN_AddTxMessage(&hcan1, &can_header, can_tx_data, &tx_mailbox);

}

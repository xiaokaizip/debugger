//
// Created by 86136 on 2023/3/24.
//

#include "can_communication.h"
#include "motor.h"
#include "usart.h"
#include "string.h"
#include "fifo.h"

uint8_t can_rx_data[8];

extern CAN_HandleTypeDef hcan1;


/////////////can_fifo///////////

fifo_s_t can_fifo;
fifo_s_t can_fifo_RM_motor;
fifo_s_t can_fifo_IMU;
unsigned char can_fifo_buf[1024];
unsigned char can_fifo_RM_motor_buf[1024];
unsigned char can_fifo_IMU_buf[1024];


can_data_t can_data_buff;

/**
 * can 滤波设置
 */
void can_init(void) {
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 1;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}


void can_fifo_init() {
    fifo_s_init(&can_fifo, &can_fifo_buf, 1000);
    fifo_s_init(&can_fifo_RM_motor, &can_fifo_RM_motor_buf, 1000);
    fifo_s_init(&can_fifo_IMU, &can_fifo_IMU_buf, 1000);
}


/**
 * 获取电机的id，以及相应电机的信息
 * @param hcan
 */

uint16_t count = 0;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    //当接受到电机的id是，led灯闪烁
    count++;
    led_can_rx(&count);
    uint8_t flag = 0;
    if (hcan->Instance == CAN1) {
        CAN_RxHeaderTypeDef rx_header;
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, can_rx_data);
////////can_fifo////////////////////////////
        can_data_buff.id = (uint16_t) rx_header.StdId;
        memcpy(&can_data_buff.data, &can_rx_data, sizeof(can_data_buff.data));
        fifo_s_puts(&can_fifo, (char *) &can_data_buff.id, sizeof(can_data_t));
///////////////////////////////////////////


        if ((uint16_t) rx_header.StdId == 0x100 || (uint16_t) rx_header.StdId == 0x101) {
            can_data_buff.id = (uint16_t) rx_header.StdId;
            memcpy(&can_data_buff.data, &can_rx_data, sizeof(can_data_buff.data));
            fifo_s_puts(&can_fifo_IMU, (char *) &can_data_buff.id, sizeof(can_data_t));

        }

        if ((uint16_t) rx_header.StdId > 0x200 && (uint16_t) rx_header.StdId <= 0x212) {
            can_data_buff.id = (uint16_t) rx_header.StdId;
            memcpy(&can_data_buff.data, &can_rx_data, sizeof(can_data_buff.data));
            fifo_s_puts(&can_fifo_RM_motor, (char *) &can_data_buff.id, sizeof(can_data_t));
        }

    }

}
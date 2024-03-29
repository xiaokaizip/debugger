//
// Created by 86136 on 2023/3/24.
//

#include "can_communication.h"
#include "motor.h"
#include "usart.h"
#include "string.h"
#include "fifo.h"

uint8_t can_rx_data[8];
uint16_t can_BMI_accel_data[8];
uint16_t can_BMI_gyro_data[8];
uint16_t can_id[6];
extern CAN_HandleTypeDef hcan1;

uint8_t IMU_updata;

/////////////can_fifo///////////

fifo_s_t can_fifo_motor;
fifo_s_t can_fifo_IMU;

unsigned char can_fifo_motor_buf[1024];
unsigned char can_fifo_IMU_buf[256];
can_data_t can_data_buf;

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
    fifo_s_init(&can_fifo_motor, can_fifo_motor_buf, 1024);
    fifo_s_init(&can_fifo_IMU, can_fifo_IMU_buf, 256);

}

void CAN_Id_Sort() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (can_id[j] > can_id[j + 1]) {
                uint16_t temp = 0;
                temp = can_id[j];
                can_id[j] = can_id[j + 1];
                can_id[j + 1] = temp;
            }

        }
    }
}


/**
 * 获取电机的id，以及相应电机的信息
 * @param hcan
 */
uint16_t twinkles = 0;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    //当接受到电机的id是，led灯闪烁
    if (twinkles > 200) {
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
        twinkles = 0;
    }

    uint8_t i = 0;
    uint8_t flag = 0;
    if (hcan->Instance == CAN1) {
        CAN_RxHeaderTypeDef rx_header;
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, can_rx_data);
////////can_fifo////////////////////////////
        can_data_buf.id = (uint16_t) rx_header.StdId;
        memcpy(&can_fifo_motor, &can_rx_data, sizeof(can_rx_data));
        if (can_data_buf.id >= 0x201 && can_data_buf.id <= 0x208) {

            fifo_s_puts(&can_fifo_motor, (char *) &can_data_buf.id, sizeof(can_data_t));
        } else if (can_data_buf.id == 0x100 || can_data_buf.id == 0x101) {
            fifo_s_puts(&can_fifo_IMU, (char *) &can_data_buf.id, sizeof(can_data_t));

        }
///////////////////////////////////////////
        twinkles++;

        if ((uint16_t) rx_header.StdId == 0x100) {
            for (int k = 0; k < 8; k++) {
                can_BMI_gyro_data[k] = can_rx_data[k];
            }
            IMU_updata |= 1;
        } else if ((uint16_t) rx_header.StdId == 0x101) {
            for (int k = 0; k < 8; k++) {
                can_BMI_accel_data[k] = can_rx_data[k];
            }
            IMU_updata |= (1 << 1);
        }

        for (int j = 0; j < 6; ++j) {
            for (int k = 0; k < 6; ++k) {
                if (can_id[k] == (uint16_t) rx_header.StdId) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                flag = 0;
                break;
            } else {
                can_id[j] = rx_header.StdId;

                flag = 0;
            }
        }
        CAN_Id_Sort();
    }

}
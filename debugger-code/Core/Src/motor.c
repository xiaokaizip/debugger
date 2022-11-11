//
// Created by 58286 on 2022/7/19.
//
#include "motor.h"
#include "usart.h"


uint8_t can_rx_data[8];
moto_measure_t moto_measure[5];
motor_state_t motor_state[5];


static CAN_TxHeaderTypeDef can_header;
static uint8_t can_tx_data[8];
uint16_t can_id[6];
extern CAN_HandleTypeDef hcan;

extern uint16_t twinkles;
uint16_t twinkles_time = 0;
extern uint16_t times;

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
    HAL_CAN_ConfigFilter(&hcan, &can_filter_st);
    HAL_CAN_Start(&hcan);
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

int16_t speed_now;
int16_t speed_last;


int16_t get_moto_measure(moto_measure_t *ptr) {
    ptr->last_angle = ptr->angle;
    ptr->angle = (uint16_t) (can_rx_data[0] << 8 | can_rx_data[1]);
    ptr->real_current = (int16_t) (can_rx_data[2] << 8 | can_rx_data[3]);
    ptr->speed_rpm = C1 * ptr->real_current + C2 * ptr->last_speed_rpm;    //这里是因为两种电调对应位不一样的信息
    ptr->last_speed_rpm = ptr->speed_rpm;
    ptr->given_current = (int16_t) (can_rx_data[4] << 8 | can_rx_data[5]) / -5;
    ptr->hall = can_rx_data[6];
    if (ptr->angle - ptr->last_angle > 4096)
        ptr->round_cnt--;
    else if (ptr->angle - ptr->last_angle < -4096)
        ptr->round_cnt++;
    ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;

    return ptr->speed_rpm;

}

void CAN_Id_Sort() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5 - i; j++) {
            uint16_t temp = 0;
            temp = can_id[j];
            can_id[j] = can_id[j + 1];
            can_id[j + 1] = temp;
        }
    }
}

/**
 * 将电流传输给指定id的电机
 * @param current 电机的转速
 * @param id 电机的id
 */
void set_moto_current(int16_t current, uint16_t id) {
    can_header.IDE = CAN_ID_STD;
    can_header.RTR = CAN_RTR_DATA;
    can_header.StdId = 0x200;
    can_header.DLC = 8;

    can_tx_data[(id - 1) * 2] = current >> 8;
    can_tx_data[(id - 1) * 2 + 1] = current & 0xFF;


    uint32_t tx_mailbox;
    HAL_CAN_AddTxMessage(&hcan, &can_header, can_tx_data, &tx_mailbox);

}


/**
 * 获取电机的id，以及相应电机的信息
 * @param hcan
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    //当接受到电机的id是，led灯闪烁
    if (twinkles - twinkles_time > 200) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14);
        twinkles = 0;
    }


    uint8_t i = 0;
    uint8_t flag = 0;
    if (hcan->Instance == CAN1) {
        CAN_RxHeaderTypeDef rx_header;
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, can_rx_data);

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
//        switch (rx_header.StdId) {
//            case 0x201: {
//                can_id[0] = 1;
//                break;
//            }
//            case 0x202: {
//                can_id[1] = 2;
//                break;
//            }
//            case 0x203: {
//                can_id[2] = 3;
//                break;
//            }
//            case 0x204: {
//                can_id[3] = 4;
//                break;
//            }
//            case 0x205: {
//                can_id[4] = 5;
//                break;
//            }
//            case 0x206: {
//                can_id[5] = 6;
//                break;
//            }
//            default:
//                break;
//        }
//

    }

}

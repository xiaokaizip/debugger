//
// Created by 86136 on 2022/10/15.
//

#include "key.h"
#include "retarget.h"

uint8_t Enter_Key() {
    uint8_t flag = 0;
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET);
        HAL_Delay(10);

        flag = 1;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET);
        HAL_Delay(10);
        flag = 2;
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) {
        HAL_Delay(10);
        while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET);
        HAL_Delay(10);
        flag = 3;
    }
    return flag;
}
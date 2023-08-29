#include "led.h"
#include "gpio.h"
#include "usart.h"

void led_can_rx(uint16_t *count) {

    if (*count > 200) {
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
        *count = 0;
    }
}

void led_can_tx(uint16_t *count) {
    if (*count > 200) {
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
        *count = 0;
    }
}
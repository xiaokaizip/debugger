//
// Created by 86136 on 2023/6/11.
//

#include "led_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

void led_task() {
    while (1) {
        vTaskDelay(1000);
    }
}

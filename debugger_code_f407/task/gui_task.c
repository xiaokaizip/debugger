//
// Created by 86136 on 2023/6/6.
//

#include "gui_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

extern unsigned char lcd_buffer[130 * 162 * 2];

void gui_task() {
    gui_config();//lcd∆¡ƒª≥ı ºªØ
    main_Form_Init();
    while (1) {
        Form_UpdateEvent();
        gui_updata();
        osDelay(100);
    }
}
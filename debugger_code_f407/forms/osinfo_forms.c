//
// Created by 86136 on 2023/6/12.
//

#include "osinfo_forms.h"
#include "main.h"
#include "key.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

static button_struct_t button_turnbuck_osinfo;
static unsigned char osinfo_update_counter = 0;

extern Forms_struct_t forms;

press_key_t osinfo_key;


static unsigned char OSInfo_Printf(unsigned char row, unsigned char column, char *fmt) {
    unsigned char n = 0;
    while (fmt[n] != '\n') {
        if (fmt[n] == '\t')
            fmt[n] = ' ';
        if (fmt[n] >= 32 && fmt[n] <= 127) {
            gui_putchar(row, column, fmt[n], 0x0000, 0xFFFF);
            row += 6;
        }
        n++;
    }
    return n;
}

static void RefreshTaskInfo(void) {
    char *buf_source = pvPortMalloc(1024), *buf = buf_source;
//    vTaskList(buf);
    OSInfo_Printf(2, 6, "Name State Prio Stack\n");
    buf += OSInfo_Printf(2, 22, buf) + 1;
    buf += OSInfo_Printf(2, 36, buf) + 1;
    buf += OSInfo_Printf(2, 50, buf) + 1;
    OSInfo_Printf(2, 64, buf);
    vPortFree(buf_source);
}

void button_turnBack_callback_osinfo(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    osinfo_key.key_select_num = 0;
}

void OSInfo_Form_Load(void) {
    press_key(&osinfo_key, 1);
    RefreshTaskInfo();
    if (osinfo_key.key_verify == 1) {
        button_turnbuck_osinfo.callback(&button_turnbuck_osinfo);
        osinfo_key.key_verify = 0;
    }
}

void OSInfo_Form_Init(void) {

    gui_clear_screan(C_WHITE);
    gui_button_init(&button_turnbuck_osinfo, 24, 136, 80, 20, "TurnBack");
    button_turnbuck_osinfo.callback = button_turnBack_callback_osinfo;
    gui_button_update(&button_turnbuck_osinfo, button_click_status);

    RefreshTaskInfo();
}

//
// Created by 86136 on 2023/1/13.
//

#include "usart_forms.h"
#include "main.h"
#include "usart.h"
#include "string.h"

button_struct_t button_turnbuck_usart;
button_struct_t button_usart;
label_struct_t label_usart;
char usart_name[20] = {0};
extern uint16_t usart_times;


extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

extern uint8_t usart_data[8];

void Button_TurnBuck_CallBack_Usart(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

void Button_Usart_CallBack(void *object) {
    key_Select_flag = 0;
}

void Usart_Form_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_printf(12, 16, C_BLACK, C_WHITE, "data1:%d", usart_data[0]);
    gui_printf(72, 16, C_BLACK, C_WHITE, "data2:%d", usart_data[1]);
    gui_printf(12, 40, C_BLACK, C_WHITE, "data3:%d", usart_data[2]);
    gui_printf(72, 40, C_BLACK, C_WHITE, "data4:%d", usart_data[3]);
    gui_printf(12, 64, C_BLACK, C_WHITE, "data5:%d", usart_data[4]);
    gui_printf(72, 64, C_BLACK, C_WHITE, "data6:%d", usart_data[5]);
    gui_printf(12, 88, C_BLACK, C_WHITE, "data7:%d", usart_data[6]);
    gui_printf(72, 88, C_BLACK, C_WHITE, "data8:%d", usart_data[7]);

    strcpy(usart_name, "wating...");
    gui_label_init(&label_usart, 8, C_BLACK, label_align_middle, usart_name);
    gui_button_init(&button_usart, 12, 128, 48, 24, "usart");
    gui_button_init(&button_turnbuck_usart, 72, 128, 48, 24, "TurnBuck");
    button_turnbuck_usart.callback = Button_TurnBuck_CallBack_Usart;
    button_usart.callback = Button_Usart_CallBack;

    gui_label_update(&label_usart);
    gui_button_update(&button_usart, button_click_status);
    gui_button_update(&button_turnbuck_usart, button_normal_status);

}

void Usart_Form_Load() {
    if (key_Select_flag >= 2) {
        key_Select_flag = 0;
    }

    gui_label_settext(&label_usart, usart_name);
    gui_label_update(&label_usart);
    gui_printf(12, 16, C_BLACK, C_WHITE, "data1:%d", usart_data[0]);
    gui_printf(72, 16, C_BLACK, C_WHITE, "data2:%d", usart_data[1]);
    gui_printf(12, 40, C_BLACK, C_WHITE, "data3:%d", usart_data[2]);
    gui_printf(72, 40, C_BLACK, C_WHITE, "data4:%d", usart_data[3]);
    gui_printf(12, 64, C_BLACK, C_WHITE, "data5:%d", usart_data[4]);
    gui_printf(72, 64, C_BLACK, C_WHITE, "data6:%d", usart_data[5]);
    gui_printf(12, 88, C_BLACK, C_WHITE, "data7:%d", usart_data[6]);
    gui_printf(72, 88, C_BLACK, C_WHITE, "data8:%d", usart_data[7]);

    if (usart_times > 5000) {
        strcpy(usart_name, "wating...");
        gui_label_settext(&label_usart, usart_name);
    }


    switch (key_Select_flag) {
        case 0:
            gui_label_update(&label_usart);
            gui_button_update(&button_usart, button_click_status);
            gui_button_update(&button_turnbuck_usart, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_label_update(&label_usart);
            gui_button_update(&button_usart, button_normal_status);
            gui_button_update(&button_turnbuck_usart, button_click_status);
            key_Select_flag = 1;
            break;
        default:
            key_Select_flag = 0;
            break;
    }

    if (key_Verify_flag == 1) {
        if (key_Select_flag == 0) {
            button_usart.callback(&button_usart);
        }
        if (key_Select_flag == 1) {
            button_turnbuck_usart.callback(&button_turnbuck_usart);
        }
        key_Verify_flag = 0;
    }

}



















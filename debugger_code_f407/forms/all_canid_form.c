//
// Created by 86136 on 2023/6/13.
//

#include "all_canid_form.h"

#include "main.h"
#include "key.h"
#include "can_data.h"
#include "usart.h"
#include "stdio.h"

button_struct_t button_Turnbuck_all_canid;
button_struct_t button_refresh_all_canid;
extern unsigned char lcd_buffer[128 * 160 * 2];

press_key_t all_canid_key;
extern Forms_struct_t forms;

extern can_data_t can_data_show[CANID_SHOW_SIZE];


void Button_TurnBuck_CallBack_all_canid(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    all_canid_key.key_select_num = 0;

}

void button_refresh_callback_all_canid(void *object) {
    refresh_can_data(can_data_show);
}

void all_canid_Form_Init() {

    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Turnbuck_all_canid, 72, 138, 48, 18, "TurnBuck");
    gui_button_init(&button_refresh_all_canid, 12, 138, 48, 18, "refresh");
    button_Turnbuck_all_canid.callback = Button_TurnBuck_CallBack_all_canid;
    button_refresh_all_canid.callback = button_refresh_callback_all_canid;
    for (int i = 0; i < CANID_SHOW_SIZE; i++) {
        gui_draw_hline(0, 16 * (i + 1), 128, C_BLUE);
    }

    gui_button_update(&button_Turnbuck_all_canid, button_normal_status);
    gui_button_update(&button_refresh_all_canid, button_click_status);
}

void all_canid_Form_Load() {
    press_key(&all_canid_key, 2);
    switch (all_canid_key.key_select_num) {
        case 0:
            gui_button_update(&button_refresh_all_canid, button_click_status);
            gui_button_update(&button_Turnbuck_all_canid, button_normal_status);
            all_canid_key.key_select_num = 0;
            break;
        case 1:
            gui_button_update(&button_refresh_all_canid, button_normal_status);
            gui_button_update(&button_Turnbuck_all_canid, button_click_status);
            all_canid_key.key_select_num = 1;
            break;
        default:
            all_canid_key.key_select_num = 0;
            break;
    }

    for (int i = 0; i < CANID_SHOW_SIZE; i++) {

        gui_printf(0, 16 * i + 4, C_BLACK, C_WHITE, "     ");
        gui_printf(0, 16 * i + 4, C_BLACK, C_WHITE, "%x", can_data_show[i].id);
        for (int j = 0; j < 7; j++) {
            gui_printf(6 * 3 + 6 * 2 * j + 3 * (j + 1), 16 * i + 4, C_BLACK, C_WHITE, "%x",
                       can_data_show[i].data[j]);
            //HAL_UART_Transmit(&huart2, (uint8_t *) &can_data_show[i], 10, HAL_MAX_DELAY);
            
        }

    }


    if (all_canid_key.key_verify == 1) {
        if (all_canid_key.key_select_num == 0) {
            button_refresh_all_canid.callback(&button_refresh_all_canid);
            gui_clear_screan(C_WHITE);
        } else if (all_canid_key.key_select_num == 1) {
            button_Turnbuck_all_canid.callback(&button_Turnbuck_all_canid);
        }
        all_canid_key.key_verify = 0;
    }
}
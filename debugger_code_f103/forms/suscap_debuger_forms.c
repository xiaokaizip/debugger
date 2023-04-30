//
// Created by 86136 on 2022/12/2.
//

#include "suscap_debuger_forms.h"
#include "main.h"


button_struct_t button_Normal;
button_struct_t button_ChargeFirst;
button_struct_t button_UseFirst;
button_struct_t button_SuscapTest;
button_struct_t button_Turnbuck_Sus;
button_struct_t button_Show;

extern unsigned char lcd_buffer[128 * 160 * 2];

extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;

void Button_TurnBuck_CallBack_Sus(void *object) {

    main_Form_Init();
    forms.id = Main_Form;
    key_Select_flag = 0;

}

/**
 * 超级店容界面的初始化函数
 */
void Suscap_Debuger_Show_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_button_init(&button_Normal, 32, 3, 72, 24, "Normal");
    gui_button_init(&button_ChargeFirst, 32, 33, 72, 24, "ChargeFirst");
    gui_button_init(&button_UseFirst, 32, 63, 72, 24, "UseFirst");
    gui_button_init(&button_SuscapTest, 32, 93, 72, 24, "SuscapTest");
    gui_button_init(&button_Turnbuck_Sus, 72, 138, 48, 18, "TurnBuck");
    button_Turnbuck_Sus.callback = Button_TurnBuck_CallBack_Sus;
    gui_button_init(&button_Show, 6, 138, 48, 18, "0");

    gui_button_update(&button_Normal, button_click_status);
    gui_button_update(&button_ChargeFirst, button_normal_status);
    gui_button_update(&button_UseFirst, button_normal_status);
    gui_button_update(&button_SuscapTest, button_normal_status);
    gui_button_update(&button_Turnbuck_Sus, button_normal_status);
    gui_button_update(&button_Show, button_normal_status);
}

/**
 * 超级电容调试界面的加载函数
 */
void Suscap_Debuger_Show_Load() {

    switch (key_Select_flag) {
        case 0:
            gui_button_update(&button_Normal, button_click_status);
            gui_button_update(&button_ChargeFirst, button_normal_status);
            gui_button_update(&button_UseFirst, button_normal_status);
            gui_button_update(&button_SuscapTest, button_normal_status);
            gui_button_update(&button_Turnbuck_Sus, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_button_update(&button_Normal, button_normal_status);
            gui_button_update(&button_ChargeFirst, button_click_status);
            gui_button_update(&button_UseFirst, button_normal_status);
            gui_button_update(&button_SuscapTest, button_normal_status);
            gui_button_update(&button_Turnbuck_Sus, button_normal_status);
            key_Select_flag = 1;
            break;
        case 2:
            gui_button_update(&button_Normal, button_normal_status);
            gui_button_update(&button_ChargeFirst, button_normal_status);
            gui_button_update(&button_UseFirst, button_click_status);
            gui_button_update(&button_SuscapTest, button_normal_status);
            gui_button_update(&button_Turnbuck_Sus, button_normal_status);
            key_Select_flag = 2;
            break;
        case 3:
            gui_button_update(&button_Normal, button_normal_status);
            gui_button_update(&button_ChargeFirst, button_normal_status);
            gui_button_update(&button_UseFirst, button_normal_status);
            gui_button_update(&button_SuscapTest, button_click_status);
            gui_button_update(&button_Turnbuck_Sus, button_normal_status);
            key_Select_flag = 3;
            break;
        case 4:
            gui_button_update(&button_Normal, button_normal_status);
            gui_button_update(&button_ChargeFirst, button_normal_status);
            gui_button_update(&button_UseFirst, button_normal_status);
            gui_button_update(&button_SuscapTest, button_normal_status);
            gui_button_update(&button_Turnbuck_Sus, button_click_status);
            key_Select_flag = 4;
            break;
        default:
            key_Select_flag = 0;
            break;
    }

    if (key_Verify_flag == 1) {
        if (key_Select_flag == 4) {
            button_Turnbuck_Sus.callback(&button_Turnbuck_Sus);
        }
        key_Verify_flag = 0;
    }

}

//
// Created by 86136 on 2022/12/2.
//

#include "main.h"
#include "main_forms.h"
#include "retarget.h"
#include "key.h"

label_struct_t label_mainForms;

button_struct_t button_SuscapDebuger;
button_struct_t button_Dail;
button_struct_t button_CanId;
button_struct_t button_Usart;

press_key_t main_key;

extern Forms_struct_t forms;


void Button_SusCap_CallBack(void *object) {

    Suscap_Debuger_Show_Init();
    forms.id = SusCapDebuger;
    main_key.key_select_num = 0;
}

void Button_Dial_CallBack(void *object) {

    Dail_Form_Init();
    forms.id = Dail;
    main_key.key_select_num = 0;

}

void Button_CanId_CallBuck(void *object) {
    CanId_Form_Init();
    forms.id = CanId;
    main_key.key_select_num = 0;
}

void Button_Usart_CallBuck(void *object) {
    Usart_Form_Init();
    forms.id = Usart;
    main_key.key_select_num = 0;
}

void main_Form_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_label_init(&label_mainForms, 0, C_BLACK, label_align_middle, "Main_Forms");
    gui_button_init(&button_SuscapDebuger, 32, 33, 72, 24, "SusCap");
    button_SuscapDebuger.callback = Button_SusCap_CallBack;
    gui_button_init(&button_Dail, 32, 63, 72, 24, "Dail");
    button_Dail.callback = Button_Dial_CallBack;
    gui_button_init(&button_CanId, 32, 93, 72, 24, "CanId");
    button_CanId.callback = Button_CanId_CallBuck;
    gui_button_init(&button_Usart, 32, 123, 72, 24, "Usart");
    button_Usart.callback = Button_Usart_CallBuck;

    gui_label_update(&label_mainForms);
    gui_button_update(&button_SuscapDebuger, button_click_status);
    gui_button_update(&button_Dail, button_normal_status);
    gui_button_update(&button_CanId, button_normal_status);
    gui_button_update(&button_Usart, button_normal_status);

}

void main_Form_Load() {

    press_key(&main_key, 4);

    switch (main_key.key_select_num) {
        case 0:
            gui_button_update(&button_SuscapDebuger, button_click_status);
            gui_button_update(&button_Dail, button_normal_status);
            gui_button_update(&button_CanId, button_normal_status);
            gui_button_update(&button_Usart, button_normal_status);
            break;
        case 1:
            gui_button_update(&button_SuscapDebuger, button_normal_status);
            gui_button_update(&button_Dail, button_click_status);
            gui_button_update(&button_CanId, button_normal_status);
            gui_button_update(&button_Usart, button_normal_status);
            break;
        case 2:
            gui_button_update(&button_SuscapDebuger, button_normal_status);
            gui_button_update(&button_Dail, button_normal_status);
            gui_button_update(&button_CanId, button_click_status);
            gui_button_update(&button_Usart, button_normal_status);
            break;
        case 3:
            gui_button_update(&button_SuscapDebuger, button_normal_status);
            gui_button_update(&button_Dail, button_normal_status);
            gui_button_update(&button_CanId, button_normal_status);
            gui_button_update(&button_Usart, button_click_status);
            break;
        default:
            break;
    }


    if (main_key.key_verify == 1) {
        if (main_key.key_select_num == 0) {
            button_SuscapDebuger.callback(&button_SuscapDebuger);
        } else if (main_key.key_select_num == 1) {
            button_Dail.callback(&button_Dail);
        } else if (main_key.key_select_num == 2) {
            button_CanId.callback(&button_CanId);
        } else if (main_key.key_select_num == 3) {
            button_Usart.callback(&button_Usart);
        }
        main_key.key_verify = 0;
    }

}
//
// Created by 86136 on 2022/12/2.
//

#include "main.h"
#include "main_forms.h"
#include "retarget.h"

label_struct_t label_mainForms;

button_struct_t button_SuscapDebuger;
button_struct_t button_Dail;
button_struct_t button_CanId;

extern unsigned short x;
extern unsigned short y;
extern uint8_t key_Select_flag;
extern uint8_t key_Enter_flag;
extern uint8_t key_Verify_flag;
extern Forms_struct_t forms;


void ButtonSusCapCallBack(void *object) {

    Suscap_Debuger_Show_Init();
    forms.id = SusCapDebuger;
    key_Select_flag = 0;
}


void main_Form_Init() {
    gui_clear_screan(C_WHITE);
    HAL_Delay(10);
    gui_label_init(&label_mainForms, 0, C_BLACK, label_align_middle, "Main_Forms");
    gui_button_init(&button_SuscapDebuger, 32, 33, 72, 24, "SusCap");
    button_SuscapDebuger.callback = ButtonSusCapCallBack;
    gui_button_init(&button_Dail, 32, 63, 72, 24, "Dail");
    gui_button_init(&button_CanId, 32, 93, 72, 24, "CanId");

    gui_label_update(&label_mainForms);
    gui_button_update(&button_SuscapDebuger, button_click_status);
    gui_button_update(&button_Dail, button_normal_status);
    gui_button_update(&button_CanId, button_normal_status);
}

void main_Form_Load() {

    if (key_Select_flag >= 3) {
        key_Select_flag = 0;
    }

    printf("%d", key_Select_flag);
    switch (key_Select_flag) {
        case 0:
            gui_button_update(&button_SuscapDebuger, button_click_status);
            gui_button_update(&button_Dail, button_normal_status);
            gui_button_update(&button_CanId, button_normal_status);
            key_Select_flag = 0;
            break;
        case 1:
            gui_button_update(&button_SuscapDebuger, button_normal_status);
            gui_button_update(&button_Dail, button_click_status);
            gui_button_update(&button_CanId, button_normal_status);
            key_Select_flag = 1;
            break;
        case 2:
            gui_button_update(&button_SuscapDebuger, button_normal_status);
            gui_button_update(&button_Dail, button_normal_status);
            gui_button_update(&button_CanId, button_click_status);
            key_Select_flag = 2;
            break;
        default:
            key_Select_flag = 0;
            break;
    }


    if (key_Verify_flag == 1) {
        if (key_Select_flag == 0) {
            button_SuscapDebuger.callback(&button_SuscapDebuger);
            forms.id = SusCapDebuger;
        }
        key_Verify_flag = 0;
    }

}
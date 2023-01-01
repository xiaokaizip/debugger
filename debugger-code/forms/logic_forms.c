//
// Created by 86136 on 2022/12/9.
//

#include "main.h"

extern Forms_struct_t forms;

void Form_UpdateEvent(void) {

    switch (forms.id) {
        case Main_Form:
            main_Form_Init();
            main_Form_Load();
            break;
        case SusCapDebuger:
            Suscap_Debuger_Show_Init();
            Suscap_Debuger_Show_Load();
            break;
        case Dail:
            Dail_Form_Init();
            Dail_Form_Load();
            break;
        case CanId:
            CanId_Form_Init();
            CanId_Form_Load();
    }
}


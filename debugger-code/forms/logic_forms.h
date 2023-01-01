//
// Created by 86136 on 2022/12/9.
//

#ifndef DEBUGGER_CODE_LOGIC_FORMS_H
#define DEBUGGER_CODE_LOGIC_FORMS_H

#include "main.h"

typedef struct Forms {
    uint8_t id;
} Forms_struct_t;


enum formsId {
    Main_Form = 0,
    SusCapDebuger = 1,
    Dail = 2,
    CanId = 3
};


void Form_UpdateEvent(void);

#endif //DEBUGGER_CODE_LOGIC_FORMS_H

//
// Created by 86136 on 2022/12/2.
//

#ifndef DEBUGGER_CODE_MAIN_FORMS_H
#define DEBUGGER_CODE_MAIN_FORMS_H

typedef struct Forms {
    uint8_t id;
} Forms_struct_t;

enum formsId {
    Main_Form = 0,
    SusCapDebuger = 1
};


void main_Form_Init();

void main_Form_Load();

#endif //DEBUGGER_CODE_MAIN_FORMS_H

//
// Created by 86136 on 2023/3/24.
//

#ifndef DEBUGGER_CODE_CAN_COMMUNICATION_H
#define DEBUGGER_CODE_CAN_COMMUNICATION_H

typedef struct {
    unsigned short id;
    unsigned char data[8];
} can_data_t;

void can_init(void);

void can_fifo_init();

#endif //DEBUGGER_CODE_CAN_COMMUNICATION_H

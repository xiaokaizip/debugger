

#ifndef C6T6_LM5116_KEY_H
#define C6T6_LM5116_KEY_H

#include "main.h"


uint8_t Enter_Key();

typedef struct {
    uint8_t key_select_num;
    uint8_t key_verify;
} press_key_t;

void press_key(press_key_t *press_key, uint8_t max_select_num);

#endif

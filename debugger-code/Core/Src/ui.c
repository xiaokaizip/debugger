//
// Created by 86136 on 2022/10/21.
//

#include "ui.h"

extern uint16_t can_id[6];

void LCD_UI() {

//    LCD_ShowString(8, 4, 8 * 12, 8, 12, (uint8_t *) "id");
//    LCD_DrawLine(0, 20, 8 * 16, 20);
    for (int i = 0; i < 6; i++) {
        LCD_ShowHEX(8, 20 * (i + 1) + 4, can_id[i], 12);
        // LCD_DrawLine(0, 20 * (i + 1), 8 * 16, 20 * (i + 1));
    }
}

/**
 * 将0-15转化为16进制数
 * @param num
 * @return
 */
char numTohex(uint8_t num) {
    char hex = '0';
    if (num <= 9) {
        hex = '0' + num;
    } else {
        switch (num) {
            case 10:
                hex = 'A';
                break;
            case 11:
                hex = 'B';
                break;
            case 12:
                hex = 'C';
                break;
            case 13:
                hex = 'D';
                break;
            case 14:
                hex = 'E';
                break;
            case 15:
                hex = 'F';
                break;
            default:
                break;
        }
    }

    return hex;
}

/**
 * 将任意数转化16进制数（3位）
 * @param x 横轴坐标
 * @param y 纵轴坐标
 * @param num 要显示的数
 * @param len 长度
 * @param size
 */
void LCD_ShowHEX(uint16_t x, uint16_t y, uint32_t num, uint8_t size) {
    char hex[6];
    char hex_temp[3];
    for (int i = 0; i < 3; i++) {
        hex_temp[i] = numTohex(num % 16);
        num /= 16;
    }
    for (int i = 0; i < 3; i++) {
        hex[5 - i - 1] = hex_temp[i];
    }
    hex[0] = '0';
    hex[1] = 'X';
    hex[5] = 0;
    //LCD_ShowString(x, y, 8 * 12, 8, size, (uint8_t *) hex);
}

//
// Created by 86136 on 2022/12/1.
//

#ifndef DEBUGGER_CODE_LCD_INIT_H
#define DEBUGGER_CODE_LCD_INIT_H

void lcd_config();

void lcd_set_direction(unsigned char mode);

void lcd_set_address(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

#endif //DEBUGGER_CODE_LCD_INIT_H

/**************************************************************************/ /**
    \file       xpt2046.c
    \brief      Touch Screen Related Codes
    \author     Lao·Zhu
    \version    V1.6.1
    \date       24. July 2022
******************************************************************************/

#include "xpt2046.h"
#include "spi.h"
#include "../function/delay.h"
#include "gui_base.h"


short touch_x_offset = 0, touch_y_offset = 0;
float touch_x_factor = 0, touch_y_factor = 0;

unsigned short xpt2046_read(unsigned short cmd) {
    unsigned char i, j;
    unsigned short tmp, value[TOUCH_READ_TIMES] = {0};
    unsigned long total_value = 0;
    unsigned short temp_value1 = 0;
    unsigned short temp_value2 = 0;

    unsigned char Data = TOUCH_Continue_Read;
    for (i = 0; i < TOUCH_READ_TIMES; i++) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

        HAL_SPI_Transmit(&hspi1, (uint8_t *) &cmd, 1, HAL_MAX_DELAY);

        HAL_SPI_Receive(&hspi1, (uint8_t *) &temp_value1, 1, HAL_MAX_DELAY);
        HAL_SPI_Receive(&hspi1, (uint8_t *) &temp_value2, 1, HAL_MAX_DELAY);
        value[i] = ((temp_value1 << 8) | temp_value2) >> 3;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    }

    for (i = 0; i < TOUCH_READ_TIMES; i++) {
        for (j = i + 1; j < TOUCH_READ_TIMES; j++) {
            if (value[i] < value[j]) {
                tmp = value[i];
                value[i] = value[j];
                value[j] = tmp;
            }
        }
    }

    for (i = 1; i < TOUCH_READ_TIMES - 1; i++)
        total_value += value[i];
    total_value /= (TOUCH_READ_TIMES - 2);

    return total_value;
}

unsigned char xpt2046_readxy(unsigned short *x, unsigned short *y) {
    unsigned short valueX1, valueY1, valueX2, valueY2;
    valueX1 = xpt2046_read(TOUCH_X_CMD);
    valueY1 = xpt2046_read(TOUCH_Y_CMD);
    valueX2 = xpt2046_read(TOUCH_X_CMD);
    valueY2 = xpt2046_read(TOUCH_Y_CMD);

    *x = valueX1 > valueX2 ? (valueX1 - valueX2) : (valueX2 - valueX1);
    *y = valueY1 > valueY2 ? (valueY1 - valueY2) : (valueY2 - valueY1);
    if ((*x > TOUCH_ERR_RANGE) || (*y > TOUCH_ERR_RANGE))
        return 0xFF;

    *x = (valueX1 + valueX2) / 2;
    *y = (valueY1 + valueY2) / 2;

    if ((*x < TOUCH_X_MIN || *x > TOUCH_X_MAX) ||
        (*y < TOUCH_Y_MIN || *y > TOUCH_Y_MAX))
        return 0xFF;
    return 0;
}

void gui_draw_sign_for_calibrate(unsigned char x, unsigned char y) {
    gui_draw_hline(x - 5, y - 1, 11, C_RED);
    gui_draw_hline(x - 5, y, 11, C_RED);
    gui_draw_hline(x - 5, y + 1, 11, C_RED);
    gui_draw_vline(x - 1, y - 5, 11, C_RED);
    gui_draw_vline(x, y - 5, 11, C_RED);
    gui_draw_vline(x + 1, y - 5, 11, C_RED);
}

void xpt2046_calibrate_single_point(unsigned short x,
                                    unsigned short y,
                                    unsigned short *valueX,
                                    unsigned short *valueY) {
    unsigned char i = 0;
    gui_clear_screan(C_BLACK);
    gui_draw_sign_for_calibrate(x, y);
    HAL_Delay(500);
    while (1) {
        if (xpt2046_readxy(valueX, valueY) != 0xFF) {
            i++;
            if (i > 10)
                break;
        }
    }
}

void xpt2046_calibrate(void) {
    unsigned short px[2], py[2], valueX[4], valueY[4];

    xpt2046_calibrate_single_point(LCD_CALx_MIN, LCD_CALy_MIN, &valueX[0], &valueY[0]);
    HAL_Delay(500);
    xpt2046_calibrate_single_point(LCD_CALx_MIN, LCD_CALy_MAX, &valueX[1], &valueY[1]);
    HAL_Delay(500);
    xpt2046_calibrate_single_point(LCD_CALx_MAX, LCD_CALy_MIN, &valueX[2], &valueY[2]);
    HAL_Delay(500);
    xpt2046_calibrate_single_point(LCD_CALx_MAX, LCD_CALy_MAX, &valueX[3], &valueY[3]);
    HAL_Delay(500);

    px[0] = (valueX[0] + valueX[1]) / 2;
    py[0] = (valueY[0] + valueY[2]) / 2;
    px[1] = (valueX[3] + valueX[2]) / 2;
    py[1] = (valueY[3] + valueY[1]) / 2;

    touch_x_factor = (float) LCD_CAL_X / ((float) px[1] - (float) px[0]);
    touch_y_factor = (float) LCD_CAL_Y / ((float) py[1] - (float) py[0]);
    touch_x_offset = (short) ((float) LCD_CALx_MAX - ((float) px[1] * touch_x_factor));
    touch_y_offset = (short) ((float) LCD_CALy_MAX - ((float) py[1] * touch_y_factor));
}

unsigned char xpt2046_scan(unsigned char *x_pos, unsigned char *y_pos) {
    unsigned short valueX, valueY;
    if (xpt2046_readxy(&valueX, &valueY) == 0xFF)
        return 0xFF;
    *x_pos = (unsigned char) ((float) valueX * touch_x_factor + (float) touch_x_offset);
    *y_pos = (unsigned char) ((float) valueY * touch_y_factor + (float) touch_y_offset);
    if ((*x_pos > 128) || (*y_pos > 160))
        return 0xFE;
    return 0;
}


//
// Created by 86136 on 2022/12/1.
//

#include "lcd_init.h"

#include "delay.h"
#include "spi.h"
#include "gpio.h"

void lcd_write_command(unsigned int com) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_Transmit_DMA(&hspi3, &com, 1);
}

void lcd_write_data(unsigned int dat) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_SPI_Transmit_DMA(&hspi3, &dat, 1);
}

void lcd_set_address(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
    x1 = x1 + 2;
    x2 = x2 + 2;
    y1 = y1 + 1;
    y2 = y2 + 1;
    lcd_write_command(0X2A);
    lcd_write_data(x1 >> 8UL);
    lcd_write_data(x1 & 0XFFUL);
    lcd_write_data(x2 >> 8UL);
    lcd_write_data(x2 & 0XFFUL);
    lcd_write_command(0X2BUL);
    lcd_write_data(y1 >> 8UL);
    lcd_write_data(y1 & 0XFFUL);
    lcd_write_data(y2 >> 8UL);
    lcd_write_data(y2 & 0XFFUL);
    lcd_write_command(0X2CUL);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
}

void lcd_set_direction(unsigned char mode) {
    switch (mode) {
        case 1:
            lcd_write_command(0x36);
            lcd_write_data(0x08);      // BGR Order. 0x00 for RGB Order
            lcd_write_command(0x2C);
            break;
        case 2:
            lcd_write_command(0x36);
            lcd_write_data(0x80);
            lcd_write_command(0x2C);
            break;
        case 3:
            lcd_write_command(0x36);
            lcd_write_data(0x40);
            lcd_write_command(0X2C);
            break;
        case 4:
            lcd_write_command(0x36);
            lcd_write_data(0xC8);   // BGR Order. 0xC0 for RGB Order
            lcd_write_command(0x2C);
            break;
        case 5:
            lcd_write_command(0x36);
            lcd_write_data(0x20);
            lcd_write_command(0x2C);
            break;
        case 6:
            lcd_write_command(0x36);
            lcd_write_data(0x60);
            lcd_write_command(0x2C);
            break;
        case 7:
            lcd_write_command(0x36);
            lcd_write_data(0xA0);
            lcd_write_command(0x2C);
            break;
        case 8:
            lcd_write_command(0x36);
            lcd_write_data(0xE0);
            lcd_write_command(0x2C);
            break;
        default:
            break;
    }
}

void lcd_config() {

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    delayus(1000);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    delayus(1000);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    delayus(120 * 1000);
    lcd_write_command(0x11);
    delayus(120 * 1000);

    lcd_write_command(0xB1);
    lcd_write_data(0x05);
    lcd_write_data(0x3C);
    lcd_write_data(0x3C);
    lcd_write_command(0xB2);
    lcd_write_data(0x05);
    lcd_write_data(0x3C);
    lcd_write_data(0x3C);
    lcd_write_command(0xB3);
    lcd_write_data(0x05);
    lcd_write_data(0x3C);
    lcd_write_data(0x3C);
    lcd_write_data(0x05);
    lcd_write_data(0x3C);
    lcd_write_data(0x3C);
    lcd_write_command(0xB4);
    lcd_write_data(0x03);
    lcd_write_command(0xC0);
    lcd_write_data(0x28);
    lcd_write_data(0x08);
    lcd_write_data(0x04);
    lcd_write_command(0xC1);
    lcd_write_data(0XC0);
    lcd_write_command(0xC2);
    lcd_write_data(0x0D);
    lcd_write_data(0x00);
    lcd_write_command(0xC3);
    lcd_write_data(0x8D);
    lcd_write_data(0x2A);
    lcd_write_command(0xC4);
    lcd_write_data(0x8D);
    lcd_write_data(0xEE);
    lcd_write_command(0xC5);
    lcd_write_data(0x1A);
    lcd_write_command(0x36);
    lcd_write_data(0xC8);       // BGR Order. 0xC0 for RGB Order
    lcd_write_command(0xE0);
    lcd_write_data(0x04);
    lcd_write_data(0x22);
    lcd_write_data(0x07);
    lcd_write_data(0x0A);
    lcd_write_data(0x2E);
    lcd_write_data(0x30);
    lcd_write_data(0x25);
    lcd_write_data(0x2A);
    lcd_write_data(0x28);
    lcd_write_data(0x26);
    lcd_write_data(0x2E);
    lcd_write_data(0x3A);
    lcd_write_data(0x00);
    lcd_write_data(0x01);
    lcd_write_data(0x03);
    lcd_write_data(0x13);
    lcd_write_command(0xE1);
    lcd_write_data(0x04);
    lcd_write_data(0x16);
    lcd_write_data(0x06);
    lcd_write_data(0x0D);
    lcd_write_data(0x2D);
    lcd_write_data(0x26);
    lcd_write_data(0x23);
    lcd_write_data(0x27);
    lcd_write_data(0x27);
    lcd_write_data(0x25);
    lcd_write_data(0x2D);
    lcd_write_data(0x3B);
    lcd_write_data(0x00);
    lcd_write_data(0x01);
    lcd_write_data(0x04);
    lcd_write_data(0x13);
    lcd_write_command(0x3A);
    lcd_write_data(0x05);
    lcd_write_command(0x29);
}
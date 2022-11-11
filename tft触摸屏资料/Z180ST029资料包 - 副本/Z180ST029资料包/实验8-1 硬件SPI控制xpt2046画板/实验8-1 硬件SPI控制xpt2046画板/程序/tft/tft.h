#ifndef TFT_H
#define TFT_H
#include "def.h"



sbit RES = P2^2;
sbit  A0 = P2^0;
sbit SDA = P4^4;
sbit SCL = P2^1;
sbit CSB = P4^2;

sbit LCD_BK1 = P4^1;//--背光
sbit LCD_REST	 = P1^6; 
sbit LED = P1^2;

void Lcd_Init(void);   //初始化
void Lcd_WR_Reg(u16 c);   //发送命令
void Lcd_Write_Data(u16 dat16); //发送数据
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标范围

void LCD_scan(u8 mode);

#endif

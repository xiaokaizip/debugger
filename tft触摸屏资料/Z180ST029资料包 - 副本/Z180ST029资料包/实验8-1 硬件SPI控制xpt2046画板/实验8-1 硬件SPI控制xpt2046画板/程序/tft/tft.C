#include "stc15f2k60s2.h"
#include "tft.h"
#include "delay.h"
#include "def.h"


//发送命令
void  Lcd_WR_Reg(u16 c)
{
     int i;
     A0=0;
     CSB=0;
     for(i=0;i<8;i++)
     {
     if(c &0x80)
     {
     SDA=1;
     }
     else SDA=0;
     SCL=0;
     SCL=1;
     c <<=1;
     }
	 
     CSB=1;	
}

void LCD_WriteData(u16 dat)
{
      int i;
      A0=1;
      CSB=0;
      for(i=0;i<8;i++)
      {
      if(dat&0x80)
      {
      SDA=1;
      }
      else SDA=0;
      SCL=0;
      SCL=1;
      dat<<=1;
      }	 
      CSB=1;
}
//发送数据
void Lcd_Write_Data(u16 dat16)
{
  LCD_WriteData(dat16>>8);
  LCD_WriteData(dat16);
}

//设置坐标范围		
//x1 y1  初始位置
//x2 y2  结束位置
void Address_set(u16 x1,u16 y1,u16 x2,u16 y2)
{	     
      //  xq=0;yq=0;
	
	  
	  x1 = x1 + 2;
	  y1 = y1 + 1;
	  x2 = x2 + 2;
	  y2 = y2 + 1;
	
		Lcd_WR_Reg(0X2A); 
		LCD_WriteData(x1>>8); 
		LCD_WriteData(x1&0XFF);
		LCD_WriteData(x2>>8); 
		LCD_WriteData(x2&0XFF);

		Lcd_WR_Reg(0X2B); 
		LCD_WriteData(y1>>8); 
		LCD_WriteData(y1&0XFF);
		LCD_WriteData(y2>>8); 
		LCD_WriteData(y2&0XFF);
	  Lcd_WR_Reg(0X2C);      //开始写入GRAM
 
}

/*
9341扫描特点 如果扫描方向改变后 会直接改变x y起始原点
所以在横屏显示的时候 就不用考虑 x y的变化后的结果 因为原点也发生改变
就是可以一种代码通用

*/

//tft屏设置扫描方式函数
//mode 1 -8  一共8种扫描方式
//     1   左>右  上>下 
//     2   左>右  下>上
//     3   右>左  上>下
//     4   右>左  下>上 
//     5   上>下  左>右  
//     6   上>下  右>左 
//     7   下>上  左>右 
//     8   下>上  右>左 
void LCD_scan(u8 mode)
{
 switch(mode)
 {
   case 1:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0x08); 	
    Lcd_WR_Reg(0X2C);      //开始写入GRAM			 
	break;
   case 2:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0x88); 
	Lcd_WR_Reg(0X2C);      //开始写入GRAM					 
	break;
   case 3:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0x48); 	
	Lcd_WR_Reg(0X2C);      //开始写入GRAM				
	break;
   case 4:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0xc8); 	
	Lcd_WR_Reg(0X2C);      //开始写入GRAM				 
	break;
   case 5:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0x28); 
	Lcd_WR_Reg(0X2C);      //开始写入GRAM					 
	break;
   case 6:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0x68); 	
	Lcd_WR_Reg(0X2C);      //开始写入GRAM				 
	break;
   case 7:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0xa8); 	
	Lcd_WR_Reg(0X2C);      //开始写入GRAM				 
	break;
   case 8:
	Lcd_WR_Reg(0x36);    // Memory Access Control 	   saomiao
	LCD_WriteData(0xe8); 
	Lcd_WR_Reg(0X2C);      //开始写入GRAM					 
	break;
 }
}




//液晶初始化
void Lcd_Init(void)
{

			
			//------------------------------------ST7735R Reset Sequence-----------------------------------------// 
RES =1; 
delay1ms (1);                                                              //Delay 1ms 
RES =0; 
delay1ms (1);                                                              //Delay 1ms 
RES =1; 
delay1ms (120);                                                              //Delay 120ms 
//--------------------------------End ST7735R Reset Sequence --------------------------------------// 
 
//--------------------------------End ST7735S Reset Sequence --------------------------------------// 
Lcd_WR_Reg(0x11); //Sleep out 
delay1ms(120);              //Delay 120ms 
//------------------------------------ST7735S Frame Rate-----------------------------------------// 
Lcd_WR_Reg(0xB1); 
LCD_WriteData(0x05); 
LCD_WriteData(0x3C); 
LCD_WriteData(0x3C); 
Lcd_WR_Reg(0xB2); 
LCD_WriteData(0x05); 
LCD_WriteData(0x3C); 
LCD_WriteData(0x3C); 
Lcd_WR_Reg(0xB3); 
LCD_WriteData(0x05); 
LCD_WriteData(0x3C); 
LCD_WriteData(0x3C); 
LCD_WriteData(0x05); 
LCD_WriteData(0x3C); 
LCD_WriteData(0x3C); 
//------------------------------------End ST7735S Frame Rate---------------------------------// 
Lcd_WR_Reg(0xB4); //Dot inversion 
LCD_WriteData(0x03); 
//------------------------------------ST7735S Power Sequence---------------------------------// 
Lcd_WR_Reg(0xC0); 
LCD_WriteData(0x28); 
LCD_WriteData(0x08); 
LCD_WriteData(0x04); 
Lcd_WR_Reg(0xC1); 
LCD_WriteData(0XC0); 
Lcd_WR_Reg(0xC2); 
LCD_WriteData(0x0D); 
LCD_WriteData(0x00); 
Lcd_WR_Reg(0xC3); 
LCD_WriteData(0x8D); 
LCD_WriteData(0x2A); 
Lcd_WR_Reg(0xC4); 
LCD_WriteData(0x8D); 
LCD_WriteData(0xEE); 
//---------------------------------End ST7735S Power Sequence-------------------------------------// 
Lcd_WR_Reg(0xC5); //VCOM 
LCD_WriteData(0x1A); 
Lcd_WR_Reg(0x36); //MX, MY, RGB mode 
LCD_WriteData(0xC0); 
//------------------------------------ST7735S Gamma Sequence---------------------------------// 
Lcd_WR_Reg(0xE0); 
LCD_WriteData(0x04); 
LCD_WriteData(0x22); 
LCD_WriteData(0x07); 
LCD_WriteData(0x0A); 
LCD_WriteData(0x2E); 
LCD_WriteData(0x30); 
LCD_WriteData(0x25); 
LCD_WriteData(0x2A); 
LCD_WriteData(0x28); 
LCD_WriteData(0x26); 
LCD_WriteData(0x2E); 
LCD_WriteData(0x3A); 
LCD_WriteData(0x00); 
LCD_WriteData(0x01); 
LCD_WriteData(0x03); 
LCD_WriteData(0x13); 
Lcd_WR_Reg(0xE1); 
LCD_WriteData(0x04); 
LCD_WriteData(0x16); 
LCD_WriteData(0x06); 
LCD_WriteData(0x0D); 
LCD_WriteData(0x2D); 
LCD_WriteData(0x26); 
LCD_WriteData(0x23); 
LCD_WriteData(0x27); 
LCD_WriteData(0x27); 
LCD_WriteData(0x25); 
LCD_WriteData(0x2D); 
LCD_WriteData(0x3B); 
LCD_WriteData(0x00); 
LCD_WriteData(0x01); 
LCD_WriteData(0x04); 
LCD_WriteData(0x13); 
//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
Lcd_WR_Reg(0x3A); //65k mode 
LCD_WriteData(0x05); 
Lcd_WR_Reg(0x29); //Display on 


}	   















































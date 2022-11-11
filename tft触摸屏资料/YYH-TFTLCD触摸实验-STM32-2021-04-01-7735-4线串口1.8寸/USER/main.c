#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "image.h"
#include "function.h"
#include "timer.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"

 
/************************************************
 深圳耀元鸿科技STM32开发板 适用9341驱动4线串口接口LCD液晶屏
 TFTLCD显示实验  
 开机显示：深圳市耀元鸿科技欢迎您（中，英文显示，白底红字）-0-9   A-Z a-z(白底绿字）-名言/诗/词（白底蓝字）
 刷屏程序：依次显示： 黑底白字显示公司名字，显示屏信息-黑-白-红-绿-蓝-  画方框-填色-画圆-填色-图片（一帧完整图片）
 WK_UP:暂停，KEY0:上翻，KEY1:下翻 
 日期：2020-11-04
 
 打开宏定义 #define tpTest行，此程序是触摸演示程序
 注释宏定义 #define tpTest行，此程序是显示演示程序
 日期：2021-01-04
 
************************************************/

//#define tpTest 

//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear_S(WHITE);	//清屏   
 	POINT_COLOR=BLUE;	//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  POINT_COLOR=RED;	//设置画笔蓝色 
}

//电阻触摸屏测试函数
void rtp_test(void)
{
	u8 i=0;	  
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	    
		if(key==KEY0_PRES)	//KEY0按下,则执行校准程序
		{			
			key = 0;
			LED1=!LED1;
			LCD_Clear(WHITE);//清屏
		  TP_Adjust();  	//屏幕校准  
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)LED0=!LED0;
	}
}



 int main(void)
 {	 
	
 	u8 x=0;
	u8 Color_Read[20];//存放读取到的颜色值	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	Lcd_Init();
	KEY_Init();	
 	tp_dev.init();
	TIM3_Int_Init(10,7199);//10Khz的计数频率，计数到10为1ms 
	POINT_COLOR=RED;
	 
	 #ifdef tpTest
					Load_Drow_Dialog();	 			
					rtp_test(); 						//电阻屏测试
	 #else
					 while(1) 
					{		 
							Lcd_Test();
					} 	 
	 #endif
	 
  

}
 

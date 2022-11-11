
/*TFT驱动IC为  ILI9341



触摸xpt2046
SPI总线  MOSI-P4^0  MISO-P4^1  SCLK-P4^3
CS-P4^4   PENIRQ-P3^7


      SPI触摸画板实验
      说明  STC15  有它自己的硬体SPI功能  它的具体讲解在 STC15F2K60S2.pdf 手册第852页开始
	        默认的SPI口是在P1口上 但是P1口我们以后会用到测试AD功能 所以从此程序开始就将SPI
			调整到 P4.1 P4.2 P4.3 （这是STC15特有功能）
			如果用到STC15单片机的硬体SPI 那么在main开始的时候就要配置好SPI功能   
			这里我们用	Init_SPI();  来初始化SPI  注意如果不初始化 SPI将不会工作！！！！

			xpt2046  是触摸芯片  以往的触摸芯片的控制 大多数都是调的模拟SPI口 来使其工作的  
		  用了 STC15硬体的SPI来控制 xpt2046工作  
			这样做的主要目的是为了节省 IO口 也是另一种功能的扩展 
			如果大家想进一步了解 SPI硬体控制xpt2046  就请参考  xpt2046 SPI通讯.doc  并结合 XPT2046中文资料.pdf 
			资料里都写的很详细，这里我们就不做多说明了。


			程序流程 启动程序 初始化SPI  死循环 判断是否有触摸现象 如果有判断触摸对应TFT屏坐标  然后画点  达到触摸画板的效果

			对于触摸校准 我们将在后面的程序讲解

*/


#include  "stc15f2k60s2.h"		  //STC15头文件
#include  "def.h"	    		  //宏定义 常用函数
#include  "delay.h"				  //延时函数
#include  "tft.h"			      //TFT IC底层驱动
#include  "gui.h"
#include  "spi.h"
#include  "xpt2046.h"
#include "tft.h"



void IO_init(void)
{
  P0M0 = 0X00;
  P0M1 = 0X00;

  P1M0 = 0X00;
  P1M1 = 0X00;

  P2M0 = 0X00;
  P2M1 = 0X00;

  P3M0 = 0X00;
  P3M1 = 0X00;

  P4M0 = 0X02;
  P4M1 = 0X00; 
	
  P5M0 = 0X08;
  P5M1 = 0X00;  
	
  P6M0 = 0X00;
  P6M1 = 0X00; 
	
  P7M0 = 0X00;
  P7M1 = 0X00;   
}



void main()
{ 
  struct TFT_Pointer Tp_pix;	        //定义触摸变量结构体
  u8 t; 
  IO_init();				   //真对 IAP15W4K61S4  IO口初始化
  Lcd_Init();                //tft初始化
  Init_SPI(); 			     //SPI初始化
  GUI_Clear(Cyan);			 //白色清屏  
  GUI_sprintf_hzstr16x(0,0,"spi touch test",Blue,White);
  while(1)
  {
    Tp_pix=TFT_Cm();	                            // 扫描触摸屏
    if(Tp_pix.flag==1)                              //是否有触摸事件 发送 
    { 
			LED = !LED;
	 Address_set(Tp_pix.x,Tp_pix.y,Tp_pix.x+2,Tp_pix.y+2);			//3*3个点为一个单元点	
	 for(t=0;t<9;t++)				
	  Lcd_Write_Data(Red);
	}
//	    LED = !LED;
  
  }
    	
}







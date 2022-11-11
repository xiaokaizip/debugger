#include "function.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "image.h"
#include "logo.h"
#include  "hz16x16.h"		  //汉字16X16
#include  "hz32x32.h"


u8 key = 0;

//--画填充圆形
void LCD_DrawFullCircle(uint16_t Xpos,uint16_t Ypos,uint16_t Radius,uint16_t Color)
{
	uint16_t x,y,r=Radius;
	for(y=Ypos - r;y<Ypos +r;y++)
	{
		for(x=Xpos - r;x<Xpos+r;x++)
		{
			if(((x-Xpos)*(x-Xpos)+(y-Ypos)*(y-Ypos)) <= r*r)
			{
				LCD_DrawPoint(x,y,Color);
			}
		}
	}
}

//--显示圆形
void Dis_Circle(void)
{
		static u16 i = 0;
	  LCD_Clear(WHITE);
		while(1)
		{
				switch(i)
				{
					case 0:
								POINT_COLOR=RED;
								LCD_Draw_Circle(100, 150, 50);
								break;
					case 1:
								POINT_COLOR=GREEN;
								LCD_Draw_Circle(100+i*25, 150-i*25, 50);
								break;
					case 2:
								POINT_COLOR=BLUE;
								LCD_Draw_Circle(100+i*25, 150-i*25, 50);
								break;
					case 3:
								POINT_COLOR=YELLOW;
								LCD_Draw_Circle(100+i*25, 150-i*25, 50);
								break;
					case 4:
								POINT_COLOR=MAGENTA;
								LCD_Draw_Circle(100+i*25, 150-i*25, 50);
								break;
				}
				delay_ms(1000);	
				i++;
				if(i>=5)
				{
						i=0;
						return;
				}
			
		}

}
//--显示填充圆形
void Dis_FullCircle(void)
{
		static u16 i = 0;
	  LCD_Clear(WHITE);
		while(1)
		{
				switch(i)
				{
					case 0:
								LCD_DrawFullCircle(100, 150, 50,RED);
								break;
					case 1:
								LCD_DrawFullCircle(100+i*25, 150-i*25, 50,GREEN);
								break;
					case 2:
								LCD_DrawFullCircle(100+i*25, 150-i*25, 50,BLUE);
								break;
					case 3:
								LCD_DrawFullCircle(100+i*25, 150-i*25, 50,YELLOW);
								break;
					case 4:
								LCD_DrawFullCircle(100+i*25, 150-i*25, 50,MAGENTA);
								break;
				}
				delay_ms(1000);	
				i++;
				if(i>=5)
				{
						i=0;
						return;
				}
			
		}

}



//--显示方形
void Dis_Rectangle(void)
{
		static u16 i = 0;
	  LCD_Clear(WHITE);
		while(1)
		{
				switch(i)
				{
					case 0:
								POINT_COLOR=RED;
								LCD_DrawRectangle(50, 250, 150, 150);
								break;
					case 1:
								POINT_COLOR=GREEN;
								LCD_DrawRectangle(50+i*20, 250-i*20, 150+i*20, 150-i*20);
								break;
					case 2:
								POINT_COLOR=BLUE;
								LCD_DrawRectangle(50+i*20, 250-i*20, 150+i*20, 150-i*20);
								break;
					case 3:
								POINT_COLOR=YELLOW;
								LCD_DrawRectangle(50+i*20, 250-i*20, 150+i*20, 150-i*20);
								break;
					case 4:
								POINT_COLOR=MAGENTA;
								LCD_DrawRectangle(50+i*20, 250-i*20, 150+i*20, 150-i*20);
								break;
				}			   		 
				delay_ms(1000);	
				i++;
				if(i>=5)
				{
						i=0;
						return;
				}
		}
		
}
//--显示填充方形图形
void Dis_Fill(void)
{
	  static u16 i = 0;
	  LCD_Clear(WHITE);
		while(1)
		{
				switch(i)
				{
					case 0:
								LCD_Fill(50, 150, 150, 250,RED);
								break;
					case 1:
								LCD_Fill(50+i*20, 150-i*20, 150+i*20, 250-i*20,GREEN);
								break;
					case 2:
								LCD_Fill(50+i*20, 150-i*20, 150+i*20, 250-i*20,BLUE);
								break;
					case 3:
								LCD_Fill(50+i*20, 150-i*20, 150+i*20, 250-i*20,YELLOW);
								break;
					case 4:
								LCD_Fill(50+i*20, 150-i*20, 150+i*20, 250-i*20,MAGENTA);
								break;
				}			   		 
				delay_ms(1000);	
				i++;
				if(i>=5)
				{
						i=0;
						return;
				}
		}
}




//--显示logo
void Dis_Logo(void)
{
		u16 x =0,y=0;
		u32 index=0;      
    Address_set(0,0,99,96);//设置光标位置 
	
		for(y=0;y<97;y++)
		{
			for(x=0;x<100;x++)
			{
				  index++;
					Lcd_Write_Data((u16)(((u16)gImage_logo[index*2+1]<<8)+gImage_logo[index*2]));
			}
		}
//		


}

//--显示一张图片
void Dis_Image(void)
{
		
	u16 x =0,y=0;
	u32 index=0; 
	  Address_set(0,0,127,159);
		for(y=0;y<160;y++)
		{
			for(x=0;x<128;x++)
			{
				  index++;
				  Lcd_Write_Data((u16)(((u16)gImage_9[index*2+1]<<8)+gImage_9[index*2]));	
			}
		}
}


void Dis_Fill_Full(void)
{
		LCD_Fill(0, 0, 53, 160,BLUE);
		LCD_Fill(0, 120, 53, 240,MAGENTA);
	
		LCD_Fill(53, 0, 160, 160,RED);
		LCD_Fill(53, 120, 160, 240,YELLOW);
	
		LCD_Fill(160, 0, 266, 160,GREEN);
		LCD_Fill(160, 120, 266, 240,GBLUE);
	
		LCD_Fill(266, 0, 320, 160,BRED);
		LCD_Fill(266, 120, 320, 240,BRRED);
}


void Lcd_Test(void)
{
	static u8 i = 0;
	static u8 Dis_Cnt = 0;
	static u8 Wakeup_Cnt = 0;
	u8 lcd_id[12];			//存放LCD ID字符串
//	i=11;
	switch(i)
	{
		case 0:
						LCD_Clear(BLACK);
						Dis_Logo();
						POINT_COLOR = WHITE;
						BACK_COLOR = 	BLACK;
						GUI_sprintf_hz16x(4,100,"耀元鸿科技",WHITE,BLACK);	//
//						LCD_ShowString(0,100,320,16,16,"Product specification:2.8/3.2 inch"); 
//						LCD_ShowString(0,120,320,16,16,"LCD Action Area:48.6mm x 64.84mm"); 
//						LCD_ShowString(0,140,320,16,16,"Resoluting:320 RGB x 240");  
//						LCD_ShowString(0,160,320,16,16,"Display Mode: Transmissive"); 
//						LCD_ShowString(0,180,320,16,16,"Input Data:MCU 16-bit Parallel interface"); 
////						LCD_ShowString(0,200,320,16,16,"Viewing:12 o'clock"); 
						LCD_ShowString(4,120,320,16,16,"Drive:"); 
						LCD_ShowString(4+6*8,120,320,16,16,"7735");		//显示LCD ID
						LCD_ShowString(4,140,320,16,16,"15889732276"); 						
						break;
		case 1:	LCD_Clear(BLACK);break;
		case 2: LCD_Clear(WHITE);break;
		case 3: LCD_Clear(RED);break;
		case 4: LCD_Clear(GREEN);break;
		case 5: LCD_Clear(BLUE);break;
		case 6: Dis_Rectangle();break;
		case 7: Dis_Fill();break;		
		case 8: Dis_Circle();break;
		case 9: Dis_FullCircle();break;
		case 10: Dis_Fill_Full();break;
		case 11: Dis_Image();break;
		
			
	}	
	
	delay_ms(1000);	   		 
	delay_ms(500);
	if(Wakeup_Cnt == 0)
	{
			i++;
//			if(i>=12)
			if(i>=12)
			{
				i=0;
			}			
	    LED0=!LED0;			
	}
	else
	{
			i= 0xff;
	}
	
	if(key)
	{						   
		switch(key)
		{				 
			case WKUP_PRES:	//控制LED1翻转 暂停
										LED0=!LED0;		
										Wakeup_Cnt++;
										if(Wakeup_Cnt == 1)//--第一次按下 暂停
										{
												Dis_Cnt = i;
												i = 0xff;
												LED0 = 1;
										}
										else if(Wakeup_Cnt >= 2)//--第二次按下恢复
										{
											  Wakeup_Cnt = 0;
												i = Dis_Cnt+1;
												LED0 = 0;
										}
										key = 0;		
										break; 
			case KEY1_PRES:	//控制LED1翻转	 下一张
										LED0=!LED0;		
										i++;
										Dis_Cnt++;
										if(Dis_Cnt >= 12)
										{
												Dis_Cnt = 0;
										}
										i = Dis_Cnt;
										key = 0;
										break;
			case KEY0_PRES:	//同时控制LED0,LED1翻转 上一张	
										LED0=!LED0;	
										if(Dis_Cnt == 0)
										{
												Dis_Cnt = 12;
										}
										i = Dis_Cnt;
										i--;	
										Dis_Cnt--;
										key = 0;
										break;
		}
	}	
		   		 
	
	
	
}


//--字符显示
void Test_String(void)
{		
		GUI_sprintf_hz32x(32,0,"深圳市耀元鸿科技",RED,WHITE);	//
		GUI_sprintf_hz16x(90,32,"深圳市耀元鸿科技",RED,WHITE);	//		
	  LCD_ShowString(0,48,480,16,16,"Welcome to Shenzhen yaoyuanhong Technology");  
	  POINT_COLOR = GREEN;
	  LCD_ShowString(48,64,320,16,16,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");  
	  LCD_ShowString(48,80,320,16,16,"abcdefghijklmnopqrstuvwxyz");  
	
		GUI_sprintf_hz32x(48,100,"莫道谗言如浪深，",BLUE,WHITE);	//
		GUI_sprintf_hz32x(48,136,"莫言过客似沙沉。",BLUE,WHITE);	//
		GUI_sprintf_hz32x(48,172,"千淘万漉虽辛苦，",BLUE,WHITE);	//
		GUI_sprintf_hz32x(48,208,"吹尽狂沙始到金。",BLUE,WHITE);	//
	
}





//程序汉字显示
//说明：汉字是用取模软件制作好的 指定的汉字 汉字大小是16x16	 即32个字节存储一个汉字
// 		这部分汉字是存在程序空间 所以汉字的多少直接影响程序空间的剩余量
//      主要方便于就显示几个指定的汉字来说就不用调用字库了 
//x  y  要显示汉字的坐标
//c[2]  汉字的数据 一个汉字两个字节表示
//dcolor 汉字的颜色   bgcolor 背景颜色
void GUI_sprintf_hz1616(u16 x, u16  y, u8 c[2], u16 dcolor,u16 bgcolor)
{
	u8 i,j,k,m;									//定义临时变量
	u16 x0,y0;
	x0 = x;
  y0=y;	
	Address_set(x,y,x+16-1,y+16-1);      //选择坐标位置	

	for (k=0;k<64;k++) 		  //64表示自建汉字库中的个数，循环查询内码	这个数并不确定 取决于存如的汉字个数	  
	{                        
	  if ((codeHZ_16[k].Index[0]==c[0])&&(codeHZ_16[k].Index[1]==c[1]))	    //寻找对应汉字	 一个汉字需要两个字节
	  { 
    	for(i=0;i<32;i++) {								    //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
		   m=codeHZ_16[k].Msk[i];							//读取对应字节数据
		  for(j=0;j<8;j++) 									//显示一个字节  一个字节8位 也就是8个点
		   {
			 if((m&0x80)==0x80) 							//判断是否是要写入点 	 如果是 给字体颜色
			   LCD_Fast_DrawPoint(x,y,dcolor);				
			 else 											//如果不是 为背景色  给颜色
			   LCD_Fast_DrawPoint(x,y,bgcolor);
			  m<<=1;										    //左移一位  判断下一点
			 
			 
				  x++;
					if((x-x0)==16)
					{
						x=x0;
						y++;
						if((y-y0)>=16)
						{
							return;
						}
					}
			 
		   } 
		  }
		}  
	  }	
	}



//显示字符串 
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示字符的颜色
//bgcolor 显示字符的背景颜色  
void GUI_sprintf_hz16x(u16 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str>=0x80)		  //小于128   ascii 都在数组内
	  {	  		  
	    GUI_sprintf_hz1616(x1+l*8,y1,(u8*)str,dcolor, bgcolor);
			str+=2;l+=2;
	  }
	}	
}



//显示32x32单个汉字
//(x，y) 是显示内容的左上角坐标，c[2]表示汉字的两个字节
//dcolor 汉字的颜色   bgcolor 背景颜色
//说明：在指定位置上显示一个32x32的汉字
void GUI_sprintf_hz3232(u16 x, u16  y, u8 c[2], u16 dcolor,u16 bgcolor)
{
	u8 i,j,k;

	u16 x0,y0;
	x0 = x;
  y0=y;	

	Address_set(x,y,x+32-1,y+32-1);      //选择坐标位置	
	for (k=0;k<100;k++) 	  //自建汉字库（k最大值和汉字库中汉字个数有关），循环查询内码
	{ 
	  if ((codeHZ_32[k].Index[0]==c[0])&&(codeHZ_32[k].Index[1]==c[1]))		//寻找要显示的汉字
	  { 
    	for(i=0;i<128;i++)													//1个汉字要128个字节点来显示
		{
		  u8 m=codeHZ_32[k].Msk[i];											//一个字节一个字节的显示
		  for(j=0;j<8;j++) 
		  {
			if((m&0x80)==0x80) //判断是否是要写入点 	 如果是 给字体颜色
			   LCD_Fast_DrawPoint(x,y,dcolor);				
			else 
			   LCD_Fast_DrawPoint(x,y,bgcolor);	//如果不是 为背景色  给颜色
			m<<=1;
			 x++;
					if((x-x0)==32)
					{
						x=x0;
						y++;
						if((y-y0)>=32)
						{
							return;
						}
					}
		  }    
		}
	  }  
	}	
}





//显示32x32汉字 和32x16 字母串
//x1，y1是显示内容的左上角坐标，
//dcolor 汉字的颜色   bgcolor 背景颜色
//*str 要显示的数据
void GUI_sprintf_hz32x(u16 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	 
{  
   u8 l=0;	  
   while(*str)
   {
	 if(*str>=0x80)		 	        
	 {
	   GUI_sprintf_hz3232(x1+l*8,y1,(u8*)str,dcolor,bgcolor);
	   l+=4;
	   str+=2;
	 }
   }
}




 

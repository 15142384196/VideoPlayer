#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h" 
#include "malloc.h" 
#include "sdio_sdcard.h" 
#include "flash.h"
#include "ff.h" 
#include "fatfs_app.h"
#include "key.h"
#include "font_show.h"
#include "wm8978.h"	
#include "videoplayer.h" 
#include "time.h"


int main()
{	
	
	SysTick_Init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	KEY_Init();
	USART1_Init(115200);
	TFTLCD_Init();			//LCD初始化
	EN25QXX_Init();				//初始化EN25Q128	  
	WM8978_Init();				//初始化WM8978
	WM8978_ADDA_Cfg(1,0);		//开启DAC
	WM8978_Input_Cfg(0,0,0);	//关闭输入通道
	WM8978_Output_Cfg(1,0);		//开启DAC输出  
	WM8978_HPvol_Set(40,40);
	WM8978_SPKvol_Set(60);
	TIM3_Init(10000-1,8400-1);//10Khz计数,1秒钟中断一次
	
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池 
	FATFS_Init();				//为fatfs相关变量申请内存  
  	f_mount(fs[0],"0:",1); 		//挂载SD卡  
	FRONT_COLOR=RED;      
	while(font_init()) 			//检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
		delay_ms(200);	
		LED1=!LED1;
	}  	 
	FRONT_COLOR=RED;      
 	LCD_ShowFontString(60,50,200,16,"PRECHIN-STM32F407",16,0);				    	 
	LCD_ShowFontString(60,70,200,16,"视频播放器实验",16,0);				    	 
	LCD_ShowFontString(60,90,200,16,"www.prechin.net",16,0);				    	 
	LCD_ShowFontString(60,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0); 
	LCD_ShowFontString(60,150,200,16,"KEY_UP:FF   KEY1：REW",16,0);
	delay_ms(1500);
	while(1)
	{ 
		video_play();
	} 
}

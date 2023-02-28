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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_Init();
	KEY_Init();
	USART1_Init(115200);
	TFTLCD_Init();			//LCD��ʼ��
	EN25QXX_Init();				//��ʼ��EN25Q128	  
	WM8978_Init();				//��ʼ��WM8978
	WM8978_ADDA_Cfg(1,0);		//����DAC
	WM8978_Input_Cfg(0,0,0);	//�ر�����ͨ��
	WM8978_Output_Cfg(1,0);		//����DAC���  
	WM8978_HPvol_Set(40,40);
	WM8978_SPKvol_Set(60);
	TIM3_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	FATFS_Init();				//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 		//����SD��  
	FRONT_COLOR=RED;      
	while(font_init()) 			//����ֿ�
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);	
		LED1=!LED1;
	}  	 
	FRONT_COLOR=RED;      
 	LCD_ShowFontString(60,50,200,16,"PRECHIN-STM32F407",16,0);				    	 
	LCD_ShowFontString(60,70,200,16,"��Ƶ������ʵ��",16,0);				    	 
	LCD_ShowFontString(60,90,200,16,"www.prechin.net",16,0);				    	 
	LCD_ShowFontString(60,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0); 
	LCD_ShowFontString(60,150,200,16,"KEY_UP:FF   KEY1��REW",16,0);
	delay_ms(1500);
	while(1)
	{ 
		video_play();
	} 
}

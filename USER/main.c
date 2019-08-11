#include "stm32f4xx.h" 

#include "led.h"

#include "delay.h"

#include "dog.h"

#include "time_text.h"

#include "LCD.h"

#include "printf.h"

#include "key.h"

#include "mune.h"

#include "EEPROM.h"

#include "PID.h"

#include "Timer.h"

#include "TIMIRQ.h"

#include "usart.h"

#include "PWM.h"

#include "stdlib.h"

/***********************************************  
P存储地址0x00
I存储地址0x08     
D上限地址0x30
V存储地址0x38
***********************************************/

float PID_set_P; 
float PID_set_I;
float PID_set_D;


unsigned char ZXT_flag=0;  //0为不画折线图 1为画折线图

char E2str[8];

int main()  //主函数
{
	int i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(115200);
	
	IIC_Init();	
	
	KEY_Init();
	
	LED_Init();
	
	TIM10_PWM_init(500-1,84-1);
	TIM11_PWM_init(500-1,84-1);
	
	TIM_SetCompare1(TIM10,500);  //改变占空比
	TIM_SetCompare1(TIM11,500);  //改变占空比
	
	TIM4_Init_encoder();
	TIM3_Int_Init(1000-1,8400-1);
	
  lcd_initial();      //显示屏初始化
	dsp_single_colour(BLACK);//背景调为黑色
	
	mune_init();       //菜单初始化

	
}


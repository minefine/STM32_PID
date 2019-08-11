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
P�洢��ַ0x00
I�洢��ַ0x08     
D���޵�ַ0x30
V�洢��ַ0x38
***********************************************/

float PID_set_P; 
float PID_set_I;
float PID_set_D;


unsigned char ZXT_flag=0;  //0Ϊ��������ͼ 1Ϊ������ͼ

char E2str[8];

int main()  //������
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
	
	TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�
	TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�
	
	TIM4_Init_encoder();
	TIM3_Int_Init(1000-1,8400-1);
	
  lcd_initial();      //��ʾ����ʼ��
	dsp_single_colour(BLACK);//������Ϊ��ɫ
	
	mune_init();       //�˵���ʼ��

	
}


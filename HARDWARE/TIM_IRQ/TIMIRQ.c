#include "TIMIRQ.h"

#include "led.h"

#include "Timer.h"

#include "delay.h"

#include "usart.h"

#include "PID.h"

#include "LCD.h"


extern char ZXT_flag;
extern float TIM5_Speed_i;
extern float set_speed;
extern int set_AG;

static int pwm;

void TIM3_Int_Init(u32 arr,u32 psc)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;  //�ޱ�Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
	
		
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x03;
	NVIC_Init(&NVIC_InitStruct);
	
  TIM_Cmd(TIM3,ENABLE);
}


void TIM3_IRQHandler(void)  //TIM4�ж�
{
	static float a;
	static char i=0;
   LED1=!LED1;    //ʹ���̵ƹ۲�����ִ�����
	
  i++;
  i=i%4;	
	
	
	if(ZXT_flag==1&&i==1)     //0Ϊ��������ͼ 1Ϊ������ͼ
	 { 
		 a=TIM4->CNT;
	   a=a-30000;
		 
		 printf("%d\n", TIM4->CNT);  
	
		 a=(a/(26*40))*10;  //10Ϊ10������Ϊһ��,
		
		 pwm=-figure_PID(a,set_speed); //����pwmֵ
	      
		 //printf("%f\n",a);
	    if(pwm<=0)
			{
		    pwm=0;
			}
			else if(pwm>300)
			{
			  pwm=300;
			}
		
	  // USRAT_printf("��ǰת�٣�%f    PWM��%d  set_speed:%f   TIM4->CNT=%d  ZXT_flag=%d\r\n",a,pwm,set_speed,TIM4->CNT,ZXT_flag);  //ͨ�����ڴ�ӡת��	
	
	   ZXT(a);
		 TIM_SetCompare1(TIM10,pwm);  //�ı�ռ�ձ�
		 TIM4->CNT=30000;//��ʼ���м�ֵ����ֹ���
	 }
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //�����жϱ�־λ
}	






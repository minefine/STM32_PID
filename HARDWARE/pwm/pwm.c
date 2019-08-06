#include "PWM.h"

//TIM10-TIM14ֻ��һ��PWMͨ�� ����ֻ��һ���̶�������ӳ�临��
void  TIM10_PWM_init(u32 arr,u32 psc)  
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource6,GPIO_AF_TIM10);//���Ÿ��ã���PF6ӳ��ΪTIM10
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;    //�Զ�����ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStruct);//��ʼ��TIM10
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC1Init(TIM10,&TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM10,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM10,ENABLE);
	TIM_Cmd(TIM10,ENABLE);
	
	
}


//TIM10-TIM14ֻ��һ��PWMͨ�� ����ֻ��һ���̶�������ӳ�临��
void  TIM11_PWM_init(u32 arr,u32 psc) 
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_TIM10);//���Ÿ��ã���PF7ӳ��ΪTIM11
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;    //�Զ�����ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStruct);//��ʼ��TIM11
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC1Init(TIM11,&TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM11,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM11,ENABLE);
	TIM_Cmd(TIM11,ENABLE);
	
	
}


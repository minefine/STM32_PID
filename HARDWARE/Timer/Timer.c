#include "Timer.h"

#include "led.h"

void TIM4_Init_encoder(void)
{
	TIM_ICInitTypeDef TIM4_ICInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);
  
	TIM_TimeBaseInitStruct.TIM_Prescaler=0X0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=60000;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM4_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM4_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM4_ICInitStruct.TIM_ICFilter=0X3;  //采样八次 滤波
	TIM4_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM4_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;  //不分频 还有 2,4,8 分频可选。
	TIM_ICInit(TIM4,&TIM4_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;       //中断 红灯亮  观察程序的执行效果
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	TIM4->CNT=30000;
	
	TIM_Cmd(TIM4,ENABLE); 
	
}

float TIM5_Speed_i=0;

void TIM4_IRQHandler(void)
{	
  TIM5_Speed_i++;
	LED0=~LED0;
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}









#include "my_usart.h"

#include "delay.h"

void Myusart1_init(void)
{
	 NVIC_InitTypeDef NVIC_InitStruct;
	 USART_InitTypeDef USART_InitStruct;
   GPIO_InitTypeDef  GPIO_InitStructure;  //����һ����ʼ��GPIO�ṹ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ�ܴ���1ʱ��
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��PA��ʱ��
	 
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);//���Ÿ���ӳ��
	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);//���Ÿ���ӳ��
	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;  //ͬʱ��ʼ��PA9,PA10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHZ
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
   GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	 
	 USART_InitStruct.USART_BaudRate=115200;
	 USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
	 USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; 
	 USART_InitStruct.USART_Parity=USART_Parity_No;
	 USART_InitStruct.USART_StopBits= USART_StopBits_1;
	 USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	 
	 USART_Init(USART1,&USART_InitStruct);
	 USART_Cmd(USART1,ENABLE);
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	 NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn ;
	 NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	 NVIC_Init(&NVIC_InitStruct);
}


void usart_send_str(char *str)
{
  while(*str++!='\0')
	{
	  USART_SendData(USART1,*str);
		delay_ms(10);
	}
}


void USART1_IRQHandler(void)
{
	char res;
	
    if(USART_GetITStatus(USART1, USART_IT_RXNE))
		{
		  res=USART_ReceiveData(USART1);
			USART_SendData(USART1,res);
			
		}
}



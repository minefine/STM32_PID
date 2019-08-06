#include "led.h"
#include "stm32f4xx.h"

void LED_Init(void)
{
   RCC->AHB1ENR|= 1<<5;  //时钟使能
	
	//PF0
	GPIOF->MODER &= ~(3<<2*0); //清零
	GPIOF->MODER |= 1<<(2*0);
	
	GPIOF->OSPEEDR &= ~(3<<2*0);
	GPIOF->OSPEEDR |= 2<<(2*0);
	
	GPIOF->PUPDR &= ~(3<<2*0);
	GPIOF->PUPDR |= 1<<(2*0);
	
	GPIOF->OTYPER &= ~(1<<0);
	GPIOF->OTYPER |=0<<0;
	
	GPIOF->ODR |= 1<<0;  //1
	
		//PF1
	GPIOF->MODER &= ~(3<<2*1); //清零
	GPIOF->MODER |= 1<<(2*1);
	
	GPIOF->OSPEEDR &= ~(3<<2*1);
	GPIOF->OSPEEDR |= 2<<(2*1);
	
	GPIOF->PUPDR &= ~(3<<2*1);
	GPIOF->PUPDR |= 1<<(2*1);
	
	GPIOF->OTYPER &= ~(1<<1);
	GPIOF->OTYPER |=0<<1;
	
	GPIOF->ODR |= 1<<1;  //1
	
	//PF2
	GPIOF->MODER &= ~(3<<2*2); //清零
	GPIOF->MODER |= 1<<(2*2);
	
	GPIOF->OSPEEDR &= ~(3<<2*2);
	GPIOF->OSPEEDR |= 2<<(2*2);
	
	GPIOF->PUPDR &= ~(3<<2*2);
	GPIOF->PUPDR |= 1<<(2*2);
	
	GPIOF->OTYPER &= ~(1<<2);
	GPIOF->OTYPER |=0<<2;
	
	GPIOF->ODR |= 1<<2;  //1
	
	//PF3
	GPIOF->MODER &= ~(3<<2*3); //清零
	GPIOF->MODER |= 1<<(2*3);
	
	GPIOF->OSPEEDR &= ~(3<<2*3);
	GPIOF->OSPEEDR |= 2<<(2*3);
	
	GPIOF->PUPDR &= ~(3<<2*3);
	GPIOF->PUPDR |= 1<<(2*3);
	
	GPIOF->OTYPER &= ~(1<<3);
	GPIOF->OTYPER |=0<<3;
	
	GPIOF->ODR |= 1<<3;  //1
	
	//PF4
	GPIOF->MODER &= ~(3<<2*4); //清零
	GPIOF->MODER |= 1<<(2*4);
	
	GPIOF->OSPEEDR &= ~(3<<2*4);
	GPIOF->OSPEEDR |= 2<<(2*4);
	
	GPIOF->PUPDR &= ~(3<<2*4);
	GPIOF->PUPDR |= 1<<(2*4);
	
	GPIOF->OTYPER &= ~(1<<4);
	GPIOF->OTYPER |=0<<4;
	
	GPIOF->ODR |= 1<<4;  //1
	
	//PF5
	GPIOF->MODER &= ~(3<<2*5); //清零
	GPIOF->MODER |= 1<<(2*5);
	
	GPIOF->OSPEEDR &= ~(3<<2*5);
	GPIOF->OSPEEDR |= 2<<(2*5);
	
	GPIOF->PUPDR &= ~(3<<2*5);
	GPIOF->PUPDR |= 1<<(2*5);
	
	GPIOF->OTYPER &= ~(1<<5);
	GPIOF->OTYPER |=0<<5;
	
	GPIOF->ODR |= 1<<5;  //1
	
	//PF9
	GPIOF->MODER &= ~(3<<2*9); //清零
	GPIOF->MODER |= 1<<(2*9);
	
	GPIOF->OSPEEDR &= ~(3<<2*9);
	GPIOF->OSPEEDR |= 2<<(2*9);
	
	GPIOF->PUPDR &= ~(3<<2*9);
	GPIOF->PUPDR |= 1<<(2*9);
	
	GPIOF->OTYPER &= ~(1<<9);
	GPIOF->OTYPER |=0<<9;
	
	GPIOF->ODR |= 1<<9;  //1
	//GPIOF->ODR &= ~(1<<9);//0
	
	//PF10
	
	GPIOF->MODER &= ~(3<<2*10); //清零
	GPIOF->MODER |= 1<<(2*10);
	
	GPIOF->OSPEEDR &= ~(3<<2*10);
	GPIOF->OSPEEDR |= 2<<(2*10);
	
	GPIOF->PUPDR &= ~(3<<2*10);
	GPIOF->PUPDR |= 1<<(2*10);
	
	GPIOF->OTYPER &= ~(1<<10);
	GPIOF->OTYPER |=0<<10;
	
	GPIOF->ODR |= 1<<10;  //1
}


#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF11,13,15
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5;//对应引脚PD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD0
}


unsigned char KEY_scan(void)//最好放到中断中使用
{
	static unsigned char  i,last=0,now=0;

	last=now;
	
	  for(i=0;i<=2;i++)
	  {
	   if(i==0)
	   {OUT_KEY1=0;OUT_KEY2=1;OUT_KEY3=1;}
	   else if(i==1)
	   {OUT_KEY1=1;OUT_KEY2=0;OUT_KEY3=1;}
	   else if(i==2)
	   {OUT_KEY1=1;OUT_KEY2=1;OUT_KEY3=0;}
	
     if(IN_KEY1 == 0||IN_KEY2 == 0||IN_KEY3 == 0)
	   {
	    delay_ms(2); //延时消抖
		
      if(IN_KEY1==0)
		  {
		    if(OUT_KEY1==0)
				{now = 1;break;}
			  else if(OUT_KEY2==0)
				{now = 2;break;}
			  else if(OUT_KEY3==0)
				{ now = 3;break;}
		  }  
		  else if(IN_KEY2==0)
		  {
		    if(OUT_KEY1==0)
				{now = 4;break;}
			  else if(OUT_KEY2==0)
				{now = 5;break;}
			  else if(OUT_KEY3==0)
				{now = 6;break;}
		  }  
	    else if(IN_KEY3==0)
		  {
		    if(OUT_KEY1==0)
				{now = 7;break;}
			 else if(OUT_KEY2==0)
			 {now = 8;break;}
			  else if(OUT_KEY3==0)
        {now = 9;break;}
		  }
			else
				now=0;
			
	   }
		 else
		 {
		    now=0;
		 }
  }
		
	
		if(last==now)
		{
		  return 0;
		}
		else
		{
		  return now;
		}
		
	
 	//return 0;
}


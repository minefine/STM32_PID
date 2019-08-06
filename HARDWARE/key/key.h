#ifndef _KEY_H
#define _KEY_H

#include "sys.h" 

#define OUT_KEY1 PDout(2)
#define OUT_KEY2 PDout(4)
#define OUT_KEY3 PDout(5)

//GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define IN_KEY1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_11)
#define IN_KEY2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_13)
#define IN_KEY3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15)

void KEY_Init(void);
unsigned char KEY_scan(void);

#endif

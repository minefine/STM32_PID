#ifndef _TIMIRQ_H
#define _TIMIRQ_H

#include "sys.h" 

void TIM3_Int_Init(u32 arr,u32 psc);
char *my_itoa(int n);
char *reverse(char *s);
#endif


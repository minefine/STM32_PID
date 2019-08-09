#ifndef _PID_H
#define _PID_H

#include "sys.h" 

void PID_Init(float P,float I,float D);
void Change_PID(float P,float I,float D);
int figure_PID(float real_speed,float set_speed);
void Change_P(float P);
void Change_I(float I);
void Change_D(float D);
void Change_add_error(float P);
#endif

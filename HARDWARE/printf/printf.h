#ifndef _PRINTF_H
#define _PRINTF_H

#include "sys.h"
#include "LCD.h"

void my_printf(const char *format,...);
char *same_char(char a);
void down_line(void);
void up_line(void);
void qingling(void);
void show_arrow(void);
void show_v(void);
void left_move(void);
void right_move(void);
void set_P(void);
void set_I(void);
void set_D(void);
void set_V(void);
#endif


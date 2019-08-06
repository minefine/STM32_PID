#include "SET_angle.h"

#include "SET_PID.h"

#include "key.h"

#include "printf.h"

extern unsigned char ZXT_flag;

extern  char SET_i;

void SET_angle(void)
{
	
  	unsigned char key;
	
    show_init();
	
		while(1)	
		{
			ZXT_flag=1;  //打开折线图
			
			key=KEY_scan();
			
       switch(key)  //键值，提供功能
		   { 
		    case 1:break;
			  case 2:SET_down();break;
			  case 3:PID_selete();break;
			  case 4:break;
			  case 5:break;
			  case 6:break;
			  case 7:break;
			  case 8:SET_up();break;
			  case 9:break;
		   }
			 
			 if(SET_i==5&&key==3)  //返回界面
			 {
				 SET_i=1;
			   return;
			 }
			 
			 if(key==3) //从PID_selete();返回的其他值
			 {
				 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
			   qingling();
         show_init();
			 }
		}
}



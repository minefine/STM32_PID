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
			ZXT_flag=1;  //������ͼ
			
			key=KEY_scan();
			
       switch(key)  //��ֵ���ṩ����
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
			 
			 if(SET_i==5&&key==3)  //���ؽ���
			 {
				 SET_i=1;
			   return;
			 }
			 
			 if(key==3) //��PID_selete();���ص�����ֵ
			 {
				 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
			   qingling();
         show_init();
			 }
		}
}



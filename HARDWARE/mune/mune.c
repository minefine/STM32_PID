#include "mune.h"

#include "printf.h"

#include "key.h"

#include "SET_PID.h"

#include "EEPROM.h"

#include "delay.h"

#include "LCD.h"


extern char ZXT_flag;   //0Ϊ��������ͼ 1Ϊ������ͼ

static char mune_i=1;
	
void mune_init(void)
{  
	 unsigned char key;
	
    my_printf("1.SET PID  \n2.SET angle \n3.return  \n");
  

	
	/*	for(i=0;i<8;i++)
	  b[i]=E2ReadByte(0x30+i);
	 my_printf(b);
	my_printf("\n");
			for(i=0;i<8;i++)
	  b[i]=E2ReadByte(0x38+i);
	 my_printf(b);
	 my_printf("\n");*/  //������
	
	  show_arrow();
	
	  while(1)
		{		
			 key=KEY_scan();
			
       switch(key)
		   { 
		    case 1:/*my_printf("1")*/;break;
			  case 2:mune_down();break;
			  case 3:mune_selete();break;
			  case 4:my_printf("4");break;
			  case 5:/*my_printf("5")*/;break;
			  case 6:/*my_printf("6")*/;break;
			  case 7:/*my_printf("7")*/;break;
			  case 8:mune_up();break;
			  case 9:/*my_printf("9")*/;break;
		   }
			 
			 if(key==3)
			 {
				 ZXT_flag=0;  //�ر�����ͼ
				 TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�
	       TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�
				 
				 ZXT_QL();
				 mune_i=1;
			   qingling();
         my_printf("1.SET PID  \n2.SET angle \n3.return  \n");
	       show_arrow();
			 }
			 
		}
}

void mune_selete(void)
{
  switch(mune_i)
	{
	  case 1:SET_PID();break;
		case 2:SET_angle();break;
	}
}




void mune_down(void) //����һ��
{
	mune_i++;
	
  my_printf("\b");
	my_printf("\b");
	my_printf(" ");
	my_printf(" ");
	down_line();
	my_printf("\b");
	my_printf("\b");
	my_printf("<-");
}

void mune_up(void) //����һ��
{
	mune_i--;
	
  my_printf("\b");
	my_printf("\b");
	my_printf(" ");
	my_printf(" ");
	up_line();
	my_printf("\b");
	my_printf("\b");
	my_printf("<-");	
}





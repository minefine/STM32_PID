#include "SET_PID.h"

#include "printf.h"

#include "key.h"

#include "EEPROM.h"

#include "delay.h"

#include "PID.h"

#include "stdlib.h"

#include "LCD.h"

#include "usart.h"

u8 *str=USART_RX_BUF;

float set_speed=0;  //�趨�ٶ�ֵ

int set_AG=0;    //�趨�Ƕ�ֵ

int un_flag=0; //charû������֮��

char AG[4]="000\0";

char JG[8]="000.0000";//����һ���洢���������ַ�������

extern char ZXT_flag;   //0Ϊ��������ͼ 1Ϊ������ͼ


static char SET_i=1;

static int SET_IO=0;

extern float TIM5_Speed_i;




/*�������� �ٶ�PID����*/
void SET_PID(void)
{
	unsigned char key;
	float vv;int i=0;
	Change_add_error(0);  //����  ��ֹ�ۼ�ЧӦ
    show_init();
	
		while(1)	
		{
			delay_ms(10);
		if(USART_RX_STA&0X8000)	
		{
     	str=USART_RX_BUF;
			
		  printf("%s\n",str);
			USART_RX_STA=0;
    }
		else{
			USART_RX_STA=0;
	  while(USART_RX_BUF[i]!='\0')
			{
			   USART_RX_BUF[i++]='\0';
			}
		}
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
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 

			 MY_USART_Change_PID(); 
			 
			 if(str[0]=='V')
			 {
				 Read_USART_str();
			   E2Write_long(0X38,JG);//�̶�ֻд�˸��ַ� 
				 vv=atof(JG);
				 set_speed=vv;
				 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
		}
}



/*�������� �Ƕ�PID����*/
void SET_angle(void)
{
	
	unsigned char key,i=0;
	int angle;
	char k[3];
	TIM4->CNT=30000;
	

	
	  ZXT_flag=0;
		TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�
	  TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�
	  
    AG_show_init();
	
	
		while(1)	
		{
			ZXT_flag=0;  //����ͼ
			
		  delay_ms(10);
		if(USART_RX_STA&0X8000)	
		{
     	str=USART_RX_BUF;
			
		  printf("%s\n",str);
			USART_RX_STA=0;
    }

			key=KEY_scan();
			
       switch(key)  //��ֵ���ṩ����
		   { 
		    case 1:break;
			  case 2:SET_down();break;
			  case 3:my_Angle_selete();break;
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
        AG_show_init();
			 }
			 
			TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�
	    TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�
			
			 MY_USART_Change_PIDtwo();
			 if(str[0]=='a')
			 {
         for(i=0;i<=2;i++)
				 {
				   k[i]=str[i+1];
				 }
				
				  angle=atoi(k);
				 
				  printf("k=%d\r\n",angle);

			    str[0]='\0';
          str[1]='\0';	
          str[2]='\0';
          str[3]='\0';
					AG_ZD(angle);			 
				/* printf("  str:%c",JG[1]);*/

			 }
			 
			 USART_RX_STA=0;
			while(USART_RX_BUF[i]!='\0')
			{
			   USART_RX_BUF[i++]='\0';
			}
			i=0;
			 
		}
}

 /*��λ����PID*/
void MY_USART_Change_PID(void)
{
 	float pp,ii,dd;
	
	
			 if(str[0]=='P')
			 {
         Read_USART_str();
			   E2Write_long(0X00,JG);//�̶�ֻд�˸��ַ�
				 delay_ms(10);
				 pp=atof(JG);
				 Change_P(pp);	

				 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();				 
			 }
			 
			 if(str[0]=='I')
			 {
				 Read_USART_str();
			   E2Write_long(0X08,JG);//�̶�ֻд�˸��ַ�					 
				 ii=atof(JG);
				 Change_I(ii);

				 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
			 if(str[0]=='D')
			 {
				 Read_USART_str();
			    E2Write_long(0X30,JG);//�̶�ֻд�˸��ַ� 
				 dd=atof(JG);
				 Change_D(dd);
				 
				 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
}


 /*��λ����PID*/
void MY_USART_Change_PIDtwo(void)
{
 	float pp,ii,dd;
	
	
		int i=0;
	//printf("kikikikiki");
	 delay_ms(10);
	 if(USART_RX_STA&0X8000)	
		{
     	str=USART_RX_BUF;
		  printf("%s\n",str);
			USART_RX_STA=0;
    }
		else{
	  while(USART_RX_BUF[i]!='\0')
			{
			   USART_RX_BUF[i++]='\0';
			}
		 i=0;
			
		}
	
			 if(str[0]=='P')
			 {
         Read_USART_str();
			   E2Write_long(0X00,JG);//�̶�ֻд�˸��ַ�
				 delay_ms(10);
				 pp=atof(JG);
				 Change_P(pp);				
	
			 	 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
			 if(str[0]=='I')
			 {
				 Read_USART_str();
			   E2Write_long(0X08,JG);//�̶�ֻд�˸��ַ�					 
				 ii=atof(JG);
				 Change_I(ii);
	
			 	 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
			 if(str[0]=='D')
			 {
				 Read_USART_str();
			    E2Write_long(0X30,JG);//�̶�ֻд�˸��ַ� 
				 dd=atof(JG);
				 Change_D(dd);
	
			 	 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
}


/*��ȡ����ֵ�������䴮�ڵ������ʼ��*/
void Read_USART_str(void)
{
	unsigned char i;
  	for(i=0;i<=7;i++)
		{
			JG[i]=str[i+1];
		  str[i]='\0';
		}
				 
		JG[3]='.';
}

/*��ʾ��ʼ��*/
void show_init(void)
{
	unsigned char i;
	char P[9];
	char I[9];
	char D[9];
	char V[9];
	
	P[8]='\0';  //��ֹ����߽��ӡ
	I[8]='\0';  //��ֹ����߽��ӡ
	D[8]='\0';  //��ֹ����߽��ӡ
	V[8]='\0';  //��ֹ����߽��ӡ
	
	ZXT_flag=0;  //�ر�����ͼ
	
	
	 for(i=0;i<=7;i++)
	 {
	    P[i]=E2ReadByte(0X00+i);
	 }
	
	 for(i=0;i<=7;i++)
	 {
	    I[i]=E2ReadByte(0X08+i);
	 }
	 for(i=0;i<=7;i++)
	 {
	    D[i]=E2ReadByte(0X30+i);
	 }
	 for(i=0;i<=7;i++)
	 {
	    V[i]=E2ReadByte(0X38+i);
	 }
	 
 	 qingling();
	 my_printf("1.P:");
	 my_printf(P);
   my_printf("\n");	 
	 my_printf("2.I:");
	 my_printf(I);
   my_printf("\n");	 				 
	 my_printf("3.D:");
	 my_printf(D);
   my_printf("\n");	 				 
	 my_printf("4.V:");
	 my_printf(V);
   my_printf("\n");
	 my_printf("5.return\n");
		
   XY_show();	 
	 show_arrow();
	 
	 ZXT_flag=1;  //������ͼ
	 
}


/*��ʾ�ǶȽ���� ��ʼ��*/
void AG_show_init(void)
{
	unsigned char i;
	char P[9];
	char I[9];
	char D[9];
	
	ZXT_flag=2;
	
	P[8]='\0';  //��ֹ����߽��ӡ
	I[8]='\0';  //��ֹ����߽��ӡ
	D[8]='\0';  //��ֹ����߽��ӡ
	
	 for(i=0;i<=7;i++)
	 {
	    P[i]=E2ReadByte(0X00+i);
	 }
	
	 for(i=0;i<=7;i++)
	 {
	    I[i]=E2ReadByte(0X08+i);
	 }
	 for(i=0;i<=7;i++)
	 {
	    D[i]=E2ReadByte(0X30+i);
	 }

	 
 	 qingling();
	 my_printf("1.P:");
	 my_printf(P);
   my_printf("\n");	 
	 my_printf("2.I:");
	 my_printf(I);
   my_printf("\n");	 				 
	 my_printf("3.D:");
	 my_printf(D);
   my_printf("\n");	 				 
	 my_printf("4.AG:");
	 my_printf(AG);
   my_printf("\n");	 				 
	 my_printf("5.return\n");
		
   XY_show();	 
	 show_arrow();
	 
}



/*ѡ����*/
void PID_selete(void)
{
  switch(SET_i)
	{
		case 1:set_P();break;
		case 2:set_I();break;
		case 3:set_D();break;
		case 4:set_V();break;
	  case 5:break;
	}
}

/*ѡ����*/
void my_Angle_selete(void)
{
  switch(SET_i)
	{
		case 1:set_P();break;
		case 2:set_I();break;
		case 3:set_D();break;
		case 4:myset_AG();break;
	  case 5:break;
	}
}

//����һ��
void SET_down(void) 
{
	if(SET_i<5)  //��ֹԽ�磬Ӱ�����������ͼ
	{
	 SET_i++;
	 
	 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
   my_printf("\b");
	 my_printf("\b");
	 my_printf(" ");
	 my_printf(" ");
	 down_line();
	 my_printf("\b");
	 my_printf("\b");
	 my_printf("<-");
	 ZXT_flag=1;  //������ͼ  
	}
}

//����һ��
void SET_up(void) 
{
	if(SET_i>1)
	{
	 SET_i--;
	 ZXT_flag=0;  //�ر�����ͼ  ����Ӱ������ͼ
   my_printf("\b");
	 my_printf("\b");
	 my_printf(" ");
	 my_printf(" ");
	 up_line();
	 my_printf("\b");
	 my_printf("\b");
	 my_printf("<-");
	 ZXT_flag=1;  //������ͼ 
	}
}

/*����P��ֵ*/
void set_P(void)
{
	float pp;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //�ر�����ͼ
	
	qingling();
	//��ȡP��ֵ����ʾ
	for(i=0;i<=7;i++)
	{
	  show[i]=E2ReadByte(0x00+i);
	}
	
	for(i=0;i<=7;i++)
	{
	  JG[i]=show[i];
	}
	
	my_printf("\n1.P:");

	my_printf(show);
	
	show_v();
	
	 while(1)
		{
		
			
			key=KEY_scan();
       switch(key)
		   { 
		    case 1:break;
			  case 2:flag2();break;
			  case 3:break;
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //ֻ��SET_IO<0ʱ���ż�
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//ֻ��SET_IO<7ʱ���ż�
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //ȷ�ϼ�
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X00,JG);//�̶�ֻд�˸��ַ� 
				 pp=atof(JG);
				 Change_P(pp);
			   break;
			 }
			 
		 }
}

/*����I��ֵ*/
void set_I(void)
{
	float ii;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //�ر�����ͼ
	
	qingling();
	//��ȡI��ֵ����ʾ
	for(i=0;i<=7;i++)
	{
	  show[i]=E2ReadByte(0x08+i);
	}
	
	for(i=0;i<=7;i++)
	{
	  JG[i]=show[i];
	}
	
	my_printf("\n2.I:");

	my_printf(show);
	
	show_v();
	
	 while(1)
		{
			
			
			
			key=KEY_scan();
       switch(key)
		   { 
		    case 1:break;
			  case 2:flag2();break;
			  case 3:break;
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //ֻ��SET_IO<0ʱ���ż�
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//ֻ��SET_IO<7ʱ���ż�
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //ȷ�ϼ�
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X08,JG);//�̶�ֻд�˸��ַ� 
				 ii=atof(JG);
				 Change_I(ii);			 
			   break;
			 }
			 
		 }
}


/*����D��ֵ*/
void set_D(void)
{
	float dd;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0; //�ر�����ͼ
	
	qingling();
	//��ȡD��ֵ����ʾ
	for(i=0;i<=7;i++)
	{
	  show[i]=E2ReadByte(0x30+i);
	}
	
	for(i=0;i<=7;i++)
	{
	  JG[i]=show[i];
	}
	
	my_printf("\n3.D:");

	my_printf(show);
	
	show_v();
	
	 while(1)
		{
			 
			key=KEY_scan();
       switch(key)
		   { 
		    case 1:break;
			  case 2:flag2();break;
			  case 3:break;
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //ֻ��SET_IO<0ʱ���ż�
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//ֻ��SET_IO<7ʱ���ż�
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //ȷ�ϼ�
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X30,JG);//�̶�ֻд�˸��ַ� 
				 dd=atof(JG);
				 Change_D(dd);
			   break;
			 }
			 
		 } 
}


/*����V��ֵ*/
void set_V(void)
{
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //�ر�����ͼ
	
	qingling();
	//��ȡV��ֵ����ʾ
	for(i=0;i<=7;i++)
	{
	  show[i]=E2ReadByte(0x38+i);
	}
	
	for(i=0;i<=7;i++)
	{
	  JG[i]=show[i];
	}
	
	my_printf("\n4.V:");

	my_printf(show);
	
	show_v();
	
	 while(1)
		{
			
			
			key=KEY_scan();
       switch(key)
		   { 
		    case 1:break;
			  case 2:flag2();break;
			  case 3:break;
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //ֻ��SET_IO<0ʱ���ż�
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//ֻ��SET_IO<7ʱ���ż�
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //ȷ�ϼ�
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X38,JG);//�̶�ֻд�˸��ַ� 
				 set_speed=atof(JG);
	       
			   break;
			 }
			 
		 } 
}
 
//���°���2��
void flag2(void)  
{
	char s[1];
	
	un_flag=JG[SET_IO]-'0';
	
  un_flag--; 
	
	if(un_flag<0)
		un_flag=9;  
	
	if(un_flag>9)
		un_flag=0;
	
	if(SET_IO!=3)
	{
	  JG[SET_IO]=un_flag+'0';  //��ֵ��JG�����ڸı�PID��ֵ
		s[0]=JG[SET_IO];         //��ֹ���ӡ
		down_line();             //��һ��
		my_printf("\b");         //����һ��
		my_printf(s);            //��ӡ����S
		up_line();               //��һ��
		my_printf("\bV");        //��ӡ
	}
	
}

//���°���8��
void flag8(void)  
{
	char s[1];
	
	un_flag=JG[SET_IO]-'0';
	
  un_flag++; 
	
	if(un_flag<0)
		un_flag=9;  
	
	if(un_flag>9)
		un_flag=0;
	
	if(SET_IO!=3)
	{
	  JG[SET_IO]=un_flag+'0';  //��ֵ��JG�����ڸı�PID��ֵ
		s[0]=JG[SET_IO];         //��ֹ���ӡ
		down_line();             //��һ��
		my_printf("\b");         //����һ��
		my_printf(s);            //��ӡ����S
		up_line();               //��һ��
		my_printf("\bV");        //��ӡ
	}	
}


void myset_AG(void)
{
  unsigned char key;
	int angle;
	int next_cnt;
	int this_cnt;
	int PWM;
	ZXT_flag=0;  //�ر�����ͼ
	
	qingling();
	
	JG[0]='0';
	JG[1]='0';
	JG[2]='0';
	JG[3]='\0';
	
	my_printf("\n4.A:000");

	
	show_v();
	
	 while(1)
		{
			key=KEY_scan();
       switch(key)
		   { 
		    case 1:break;
			  case 2:flag2();break;
			  case 3:break;
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //ֻ��SET_IO<0ʱ���ż�
			  case 5:break;
			  case 6:if(SET_IO<2) {right_move();SET_IO++;}break;//ֻ��SET_IO<7ʱ���ż�
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //ȷ�ϼ�
			 {
				 SET_IO=0;
				 angle = atoi(JG);
				 
				 TIM5_Speed_i=0;
				 next_cnt=( angle *260/360 );
				 
				 this_cnt= TIM5_Speed_i;
				 
				 while(this_cnt<=next_cnt)
				 {
				   this_cnt= TIM5_Speed_i;
					 PWM=-figure_PID(this_cnt,next_cnt);
					 if(PWM<0)
						 PWM=0;
					 
					 
					 TIM_SetCompare1(TIM10,PWM);  //�ı�ռ�ձ�	
			     TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�	
           //delay_ms(1);
           //printf("%d\n",PWM);					 
				 }
	       	TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�	
			    TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�	
			   break;
			 }
			 
		 } 

}

/*�������ýǶȣ�ֱ��ת��*/
void AG_ZD(int angle)
{
	char a[3];
	int next_cnt;
	int this_cnt;
	int PWM;

	//angle = 360;
	
	ZXT_flag=0;  //�ر�����ͼ
	
	qingling();
	
	my_printf("\n4.A");
	
	 TIM5_Speed_i=0;
	 next_cnt=( angle *260/360 );
	 
	 this_cnt= TIM5_Speed_i;
	 
	 while(this_cnt<=next_cnt)
	 {
		 this_cnt= TIM5_Speed_i;
		 PWM=-figure_PID(this_cnt,next_cnt);
		 if(PWM<0)
			 PWM=0;
		 
		 
		 TIM_SetCompare1(TIM10,PWM);  //�ı�ռ�ձ�	
		 TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�	
		 //delay_ms(1);
		 //printf("%d\n",PWM);					 
	 }
		TIM_SetCompare1(TIM10,500);  //�ı�ռ�ձ�	
		TIM_SetCompare1(TIM11,500);  //�ı�ռ�ձ�	

		SET_i=1;
		qingling();
    AG_show_init();

}
	





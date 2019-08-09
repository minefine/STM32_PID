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

float set_speed=0;  //设定速度值

int set_AG=0;    //设定角度值

int un_flag=0; //char没有正负之分

char AG[4]="000\0";

char JG[8]="000.0000";//定义一个存储浮点数的字符的数组

extern char ZXT_flag;   //0为不画折线图 1为画折线图


static char SET_i=1;

static int SET_IO=0;

extern float TIM5_Speed_i;




/*进入设置 速度PID界面*/
void SET_PID(void)
{
	unsigned char key;
	float vv;int i=0;
	Change_add_error(0);  //清零  防止累计效应
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
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 

			 MY_USART_Change_PID(); 
			 
			 if(str[0]=='V')
			 {
				 Read_USART_str();
			   E2Write_long(0X38,JG);//固定只写八个字符 
				 vv=atof(JG);
				 set_speed=vv;
				 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
		}
}



/*进入设置 角度PID界面*/
void SET_angle(void)
{
	
	unsigned char key,i=0;
	int angle;
	char k[3];
	TIM4->CNT=30000;
	

	
	  ZXT_flag=0;
		TIM_SetCompare1(TIM10,500);  //改变占空比
	  TIM_SetCompare1(TIM11,500);  //改变占空比
	  
    AG_show_init();
	
	
		while(1)	
		{
			ZXT_flag=0;  //折线图
			
		  delay_ms(10);
		if(USART_RX_STA&0X8000)	
		{
     	str=USART_RX_BUF;
			
		  printf("%s\n",str);
			USART_RX_STA=0;
    }

			key=KEY_scan();
			
       switch(key)  //键值，提供功能
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
        AG_show_init();
			 }
			 
			TIM_SetCompare1(TIM10,500);  //改变占空比
	    TIM_SetCompare1(TIM11,500);  //改变占空比
			
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

 /*上位机改PID*/
void MY_USART_Change_PID(void)
{
 	float pp,ii,dd;
	
	
			 if(str[0]=='P')
			 {
         Read_USART_str();
			   E2Write_long(0X00,JG);//固定只写八个字符
				 delay_ms(10);
				 pp=atof(JG);
				 Change_P(pp);	

				 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();				 
			 }
			 
			 if(str[0]=='I')
			 {
				 Read_USART_str();
			   E2Write_long(0X08,JG);//固定只写八个字符					 
				 ii=atof(JG);
				 Change_I(ii);

				 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
			 if(str[0]=='D')
			 {
				 Read_USART_str();
			    E2Write_long(0X30,JG);//固定只写八个字符 
				 dd=atof(JG);
				 Change_D(dd);
				 
				 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         show_init();
			 }
			 
}


 /*上位机改PID*/
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
			   E2Write_long(0X00,JG);//固定只写八个字符
				 delay_ms(10);
				 pp=atof(JG);
				 Change_P(pp);				
	
			 	 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
			 if(str[0]=='I')
			 {
				 Read_USART_str();
			   E2Write_long(0X08,JG);//固定只写八个字符					 
				 ii=atof(JG);
				 Change_I(ii);
	
			 	 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
			 if(str[0]=='D')
			 {
				 Read_USART_str();
			    E2Write_long(0X30,JG);//固定只写八个字符 
				 dd=atof(JG);
				 Change_D(dd);
	
			 	 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
				 SET_i=1;
				 ZXT_QL(); 
			   qingling();
         AG_show_init();
			 }
			 
}


/*读取串口值，并将其串口的数组初始化*/
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

/*显示初始化*/
void show_init(void)
{
	unsigned char i;
	char P[9];
	char I[9];
	char D[9];
	char V[9];
	
	P[8]='\0';  //防止数组边界打印
	I[8]='\0';  //防止数组边界打印
	D[8]='\0';  //防止数组边界打印
	V[8]='\0';  //防止数组边界打印
	
	ZXT_flag=0;  //关闭折线图
	
	
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
	 
	 ZXT_flag=1;  //打开折线图
	 
}


/*显示角度界面的 初始化*/
void AG_show_init(void)
{
	unsigned char i;
	char P[9];
	char I[9];
	char D[9];
	
	ZXT_flag=2;
	
	P[8]='\0';  //防止数组边界打印
	I[8]='\0';  //防止数组边界打印
	D[8]='\0';  //防止数组边界打印
	
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



/*选择功能*/
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

/*选择功能*/
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

//向下一行
void SET_down(void) 
{
	if(SET_i<5)  //防止越界，影响下面的折线图
	{
	 SET_i++;
	 
	 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
   my_printf("\b");
	 my_printf("\b");
	 my_printf(" ");
	 my_printf(" ");
	 down_line();
	 my_printf("\b");
	 my_printf("\b");
	 my_printf("<-");
	 ZXT_flag=1;  //打开折线图  
	}
}

//向上一行
void SET_up(void) 
{
	if(SET_i>1)
	{
	 SET_i--;
	 ZXT_flag=0;  //关闭折线图  避免影响后面绘图
   my_printf("\b");
	 my_printf("\b");
	 my_printf(" ");
	 my_printf(" ");
	 up_line();
	 my_printf("\b");
	 my_printf("\b");
	 my_printf("<-");
	 ZXT_flag=1;  //打开折线图 
	}
}

/*设置P的值*/
void set_P(void)
{
	float pp;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //关闭折线图
	
	qingling();
	//读取P的值，显示
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
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //只有SET_IO<0时，才加
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//只有SET_IO<7时，才加
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //确认键
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X00,JG);//固定只写八个字符 
				 pp=atof(JG);
				 Change_P(pp);
			   break;
			 }
			 
		 }
}

/*设置I的值*/
void set_I(void)
{
	float ii;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //关闭折线图
	
	qingling();
	//读取I的值，显示
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
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //只有SET_IO<0时，才加
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//只有SET_IO<7时，才加
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //确认键
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X08,JG);//固定只写八个字符 
				 ii=atof(JG);
				 Change_I(ii);			 
			   break;
			 }
			 
		 }
}


/*设置D的值*/
void set_D(void)
{
	float dd;
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0; //关闭折线图
	
	qingling();
	//读取D的值，显示
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
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //只有SET_IO<0时，才加
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//只有SET_IO<7时，才加
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //确认键
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X30,JG);//固定只写八个字符 
				 dd=atof(JG);
				 Change_D(dd);
			   break;
			 }
			 
		 } 
}


/*设置V的值*/
void set_V(void)
{
  unsigned char key,i;
	char show[9];
	show[8]='\0';
	
	ZXT_flag=0;  //关闭折线图
	
	qingling();
	//读取V的值，显示
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
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //只有SET_IO<0时，才加
			  case 5:break;
			  case 6:if(SET_IO<7) {right_move();SET_IO++;}break;//只有SET_IO<7时，才加
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //确认键
			 {
				 SET_IO=0;
				 JG[3]='.';
				 E2Write_long(0X38,JG);//固定只写八个字符 
				 set_speed=atof(JG);
	       
			   break;
			 }
			 
		 } 
}
 
//摁下按键2后
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
	  JG[SET_IO]=un_flag+'0';  //赋值给JG，用于改变PID的值
		s[0]=JG[SET_IO];         //防止多打印
		down_line();             //下一行
		my_printf("\b");         //后退一格
		my_printf(s);            //打印数组S
		up_line();               //上一行
		my_printf("\bV");        //打印
	}
	
}

//摁下按键8后
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
	  JG[SET_IO]=un_flag+'0';  //赋值给JG，用于改变PID的值
		s[0]=JG[SET_IO];         //防止多打印
		down_line();             //下一行
		my_printf("\b");         //后退一格
		my_printf(s);            //打印数组S
		up_line();               //上一行
		my_printf("\bV");        //打印
	}	
}


void myset_AG(void)
{
  unsigned char key;
	int angle;
	int next_cnt;
	int this_cnt;
	int PWM;
	ZXT_flag=0;  //关闭折线图
	
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
			  case 4:if(SET_IO>0) {left_move();SET_IO--;} break;  //只有SET_IO<0时，才加
			  case 5:break;
			  case 6:if(SET_IO<2) {right_move();SET_IO++;}break;//只有SET_IO<7时，才加
			  case 7:break;
			  case 8:flag8();break;
			  case 9:break;
		   }
			 
			 if(key==3) //确认键
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
					 
					 
					 TIM_SetCompare1(TIM10,PWM);  //改变占空比	
			     TIM_SetCompare1(TIM11,500);  //改变占空比	
           //delay_ms(1);
           //printf("%d\n",PWM);					 
				 }
	       	TIM_SetCompare1(TIM10,500);  //改变占空比	
			    TIM_SetCompare1(TIM11,500);  //改变占空比	
			   break;
			 }
			 
		 } 

}

/*串口设置角度，直接转动*/
void AG_ZD(int angle)
{
	char a[3];
	int next_cnt;
	int this_cnt;
	int PWM;

	//angle = 360;
	
	ZXT_flag=0;  //关闭折线图
	
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
		 
		 
		 TIM_SetCompare1(TIM10,PWM);  //改变占空比	
		 TIM_SetCompare1(TIM11,500);  //改变占空比	
		 //delay_ms(1);
		 //printf("%d\n",PWM);					 
	 }
		TIM_SetCompare1(TIM10,500);  //改变占空比	
		TIM_SetCompare1(TIM11,500);  //改变占空比	

		SET_i=1;
		qingling();
    AG_show_init();

}
	





#include "PID.h"
#include "usart.h"	
//定义一个PID的结构体
static struct {
	
	 float Kp;
	 float Ki;
	 float Kd;
   float error;
	 float last_error;
	 float last_last_error;
	 float P_out;
   float I_out;    
	 float D_out;
	 float PID_out;
	 float add_error;          //累计误差
}PID;

void PID_Init()  //数值的初始化
{
  PID.Kp=0;
  PID.Ki=0;
  PID.Kd=0;
  PID.last_error=0;
  PID.error=0;
  PID.last_last_error=0;
}

void Change_P(float P)  //改变P的数值
{
   PID.Kp=P;
}

void Change_add_error(float P)  //改变add_error的数值
{
   PID.add_error=P;
}

void Change_I(float I)  //改变I的数值
{
   PID.Ki=I;
}

void Change_D(float D)  //改变D的数值
{
   PID.Kd=D;	
}

/*位置式PID的公式 PID = Kp*error + Ki*累计误差+Kd*(  d(error(t) )/d(t)  ) */

/*int figure_PID(float real_speed,float set_speed)  //real_speed为实际数度，set_speed为设定的速度
{
	
  PID.error=set_speed-real_speed;  //计算误差值
	
	PID.P_out=PID.Kp*PID.error;      //计算Kp的输出
	
	PID.add_error+=PID.error;            //计算累计误差
	PID.I_out=PID.Ki*PID.add_error;      //计算Ki的输出
		
	PID.add_error+=PID.error;            //计算累计误差
	PID.I_out=PID.Ki*PID.add_error;      //计算Ki的输出
	
	PID.D_out=PID.Kd*(PID.error-PID.last_error);//计算Kd的输出
	
	
	PID.PID_out=PID.P_out+PID.D_out+PID.I_out;//计算PWM输出
	
	PID.last_error=PID.error;  //赋值为下一次计算做准备
	
	return PID.PID_out;        //返回PWM值
}*/

/*注意PID三个值计算出来的值，有可能为负数*/

int figure_PID(float real_speed,float set_speed)  //real_speed为实际数度，set_speed为设定的速度  //增量式PID
{
	 float increment_speed;//增量
	
	 PID.error=set_speed-real_speed;  //计算误差值
	
	 //printf("%f\n", PID.error);  
	
   increment_speed =  (PID.Kp*PID.error) + (PID.Ki*PID.last_error) +(PID.last_last_error*PID.Kd);
	
	 PID.PID_out += increment_speed;
	
	 PID.last_last_error = PID.last_error;
	
	 PID.last_error = PID.error;
	
	 //printf("%f\n",PID.PID_out);
	
	 return PID.PID_out;        //返回PWM值
}

#include "PID.h"

//定义一个PID的结构体
static struct {
	
	 float Kp;
	 float Ki;
	 float Kd;
   float error;
	 float last_error;
	 float P_out;
   float I_out;    
	 float D_out;
	 float PID_out;
	
}PID;

void PID_Init(float P,float I,float D)  //数值的初始化
{
  PID.Kd=P;
  PID.Ki=I;
  PID.Kp=D;
  PID.last_error=0;
  PID.error=0;
  	
}

void Change_P(float P)  //改变P的数值
{
   PID.Kp=P;
}

void Change_I(float I)  //改变I的数值
{
   PID.Ki=I;
}

void Change_D(float D)  //改变D的数值
{
   PID.Kd=D;	
}

/*PID的公式 PID = Kp*error + Ki*累计误差+Kd*(  d(error(t) )/d(t)  ) */

int figure_PID(float real_speed,float set_speed)  //real_speed为实际数度，set_speed为设定的速度
{
	static float add_error;          //累计误差
	
  PID.error=set_speed-real_speed;  //计算误差值
	
	PID.P_out=PID.Kp*PID.error;      //计算Kp的输出
	
	add_error+=PID.error;            //计算累计误差
	PID.I_out=PID.Ki*add_error;      //计算Ki的输出
		
	add_error+=PID.error;            //计算累计误差
	PID.I_out=PID.Ki*add_error;      //计算Ki的输出
	
	PID.D_out=PID.Kd*(PID.error-PID.last_error);//计算Kd的输出
	
	PID.PID_out=PID.P_out+PID.D_out+PID.I_out;//计算PWM输出
	
	PID.last_error=PID.error;  //赋值为下一次计算做准备
	
	return PID.PID_out;        //返回PWM值
}

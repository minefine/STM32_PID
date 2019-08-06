#include "PID.h"

//����һ��PID�Ľṹ��
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

void PID_Init(float P,float I,float D)  //��ֵ�ĳ�ʼ��
{
  PID.Kd=P;
  PID.Ki=I;
  PID.Kp=D;
  PID.last_error=0;
  PID.error=0;
  	
}

void Change_P(float P)  //�ı�P����ֵ
{
   PID.Kp=P;
}

void Change_I(float I)  //�ı�I����ֵ
{
   PID.Ki=I;
}

void Change_D(float D)  //�ı�D����ֵ
{
   PID.Kd=D;	
}

/*PID�Ĺ�ʽ PID = Kp*error + Ki*�ۼ����+Kd*(  d(error(t) )/d(t)  ) */

int figure_PID(float real_speed,float set_speed)  //real_speedΪʵ�����ȣ�set_speedΪ�趨���ٶ�
{
	static float add_error;          //�ۼ����
	
  PID.error=set_speed-real_speed;  //�������ֵ
	
	PID.P_out=PID.Kp*PID.error;      //����Kp�����
	
	add_error+=PID.error;            //�����ۼ����
	PID.I_out=PID.Ki*add_error;      //����Ki�����
		
	add_error+=PID.error;            //�����ۼ����
	PID.I_out=PID.Ki*add_error;      //����Ki�����
	
	PID.D_out=PID.Kd*(PID.error-PID.last_error);//����Kd�����
	
	PID.PID_out=PID.P_out+PID.D_out+PID.I_out;//����PWM���
	
	PID.last_error=PID.error;  //��ֵΪ��һ�μ�����׼��
	
	return PID.PID_out;        //����PWMֵ
}
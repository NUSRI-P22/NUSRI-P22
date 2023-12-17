//Motor_Speed_pid.c
//2023.11.9
//by gjx

#include "Motor_Speed_pid.h"

PID_TypeDef motor_pid[4];
float set_spdL;// rpm  ���ֽ��ٶȣ�ת�٣�        1 rpm = pi/30 = 0.1047 ��rad/s��    1(rad/s) = 9.55(rpm)            //Pi rad = 180��    1 rad = 180/Pi ��    1 �� = Pi/180 rad
float set_spdR;// rpm  ���ֽ��ٶȣ�ת�٣�

float set_spdL1;
float set_spdR1;

float Vcx = 0;   //   m/s 
float Wc = 0;    //   rad/s 
float C = 0.5;     //   m 
float r = 0.1;     //   m 
int flaggg = 0;
int free_flag = 0; // true if motors




float low_pass_filter(float value, float fc, float Ts)
{
	
	
  float b = fc * Ts;
  float alpha = b / (b + 1);
  static float out_last = 0; //��һ���˲�ֵ
  float out;

  static char fisrt_flag = 1;
  if (fisrt_flag == 1)
  {
    fisrt_flag = 0;
    out_last = value;
  }

  out = out_last + alpha * (value - out_last);
  out_last = out;

  return out;
}


void Motor_Speed_Calc()
{
		if(motor_shutdown == 1)
		{
			set_spdL = 0;
			set_spdR = 0;
		}
		else
		{
  	set_spdL = (2*Vcx - Wc*C)/(2*r)*9.55*19.2;
   	set_spdR = (2*Vcx + Wc*C)/(2*r)*9.55*19.2;
		}
//		set_spdL =  low_pass_filter(set_spdL, 50, 0.005);
//		set_spdR =  low_pass_filter(set_spdR, 50, 0.005);
	
//	set_spdL = 1140;    // 60rpm
// 	set_spdR = 1140;
  	
}


void Motor_Speed_pid_init()  //static void pid_param_init(PID_TypeDef * pid, PID_ID   id,uint16_t maxout,uint16_t intergral_limit,float deadband,uint16_t period,int16_t  max_err,int16_t  target,float 	kp, float 	ki, float 	kd)
{
  for(int i=0; i<4; i++)
  {	
    pid_init(&motor_pid[i]);
    motor_pid[i].f_param_init(&motor_pid[i],PID_Speed,10000,10000,0,0,8000,0,10,3.2832,0);  
  }
}

void Set_free()
{
	CAN_cmd_chassis(0,0,0,0);
	for(int i=0; i<4; i++)
	{
		motor_pid[i].iout = 0;
		motor_pid[i].output = 0;
		motor_pid[i].calculate_output = 0;
	}
	
}


void Speed_set()
{
	if(motor_ready == 1)
	{
		if(motor_shutdown == 0)
		{
		
			if((PS2_LY < 133) && (PS2_LY > 123) && (PS2_RX < 130) && (PS2_RX > 124))
			{
				Set_free();
				free_flag = 1;
			}
			else
			{
				free_flag = 0;
			}
		}
		
		if(free_flag == 0)
		{
			Motor_Speed_Calc();
			motor_pid[0].target = set_spdL;    //׳ǰ
			motor_pid[1].target = set_spdL;    //׳º󍊉		
			motor_pid[2].target = -set_spdR;    //Ӓǰ
			motor_pid[3].target = -set_spdR;    //Ӓº󍊉		
			for(int i=0; i<4; i++)
			{	 																							
				motor_pid[i].f_cal_pid(&motor_pid[i],motor_chassis[i].speed_rpm);    //¸ù¾݉趨ֵ½øАPID¼Ƌ㡣
			}

			CAN_cmd_chassis(motor_pid[0].output,   //½«PIDµļƋ㽡¹ûͨ¹ýCAN·¢ˍµ½µ绺
											motor_pid[1].output,
											motor_pid[2].output,
											motor_pid[3].output);
		}
  }
		if(motor_ready == 0)
		{
		
				Set_free();
				free_flag = 1;
		
		}

	
	
	
}
//Using motor_speed(rpm) to calculate the velocity(m/s) and angular velocity(rad/s) of the car
void MOTORrpm2vw(float left_motor_speed,float right_motor_speed,float *vcx,float*w)
{
	const float c = 0.5;	 //m
	const float r = 0.1;   //m
	float left_wheel_w = left_motor_speed/19.0f/9.55f;  //motor_speed(rpm)->wheel_speed(rad/s)
	float right_wheel_w = right_motor_speed/19.0f/9.55f;
	float vL = left_wheel_w * r;
	float vR = right_wheel_w * r;
	*vcx = 0.5*vL + 0.5*vR;;   //  m/s
	*w = -vL/c + vR/c;           //  rad/s
}
void speed_print()
{
	usart_printf("%d,%f,%f,%d,%d,%f,%d,%d,%d\n",motor_chassis[0].speed_rpm,       set_spdL,   motor_pid[0].output,   PS2_LY,PS2_RX,MAX_Speed,motor_shutdown,motor_ready,free_flag);		
}
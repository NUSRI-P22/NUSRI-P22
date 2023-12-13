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
bool free_flag = false; // true if motors




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
		if(motor_shutdown)
		{
			set_spdL = 0;
			set_spdR = 0;
		}
		else
		{
  	set_spdL = (2*Vcx - Wc*C)/(2*r)*9.55*19.2;
   	set_spdR = (2*Vcx + Wc*C)/(2*r)*9.55*19.2;
		}
		set_spdL =  low_pass_filter(set_spdL, 100, 0.06);
		set_spdR =  low_pass_filter(set_spdR, 100, 0.06);
	
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


// Return true if the Joystick is centered
bool PS2_Is_Center(){
	return (PS2_LY < 130) && (PS2_LY > 126) && (PS2_RX < 129) && (PS2_RX > 125);
}



void Speed_set()
{
	if(motor_ready)
	{
		if(!motor_shutdown)
		{
			if(free_flag = PS2_Is_Center()) Set_free();
		}
		
		if(free_flag == 0)
		{
			Motor_Speed_Calc();
			motor_pid[0].target = set_spdL;    // left-motor
			motor_pid[1].target = set_spdL;    // left-motor
			motor_pid[2].target = -set_spdR;   // right-motor
			motor_pid[3].target = -set_spdR;   // right-motor
			for(int i=0; i<4; i++)
			{	 																							
				motor_pid[i].f_cal_pid(&motor_pid[i],motor_chassis[i].speed_rpm);    // PID calculated output
			}

			CAN_cmd_chassis(motor_pid[0].output,   // set current
											motor_pid[1].output,
											motor_pid[2].output,
											motor_pid[3].output);
		}
	}
	else{
			
		Set_free();
		free_flag = 1;
			
	}
	
}
void speed_print()
{
	usart_printf("%d,%f,%f,%d,%d,%f,%d,%d,%d\n",motor_chassis[0].speed_rpm,       set_spdL,   motor_pid[0].output,   PS2_LY,PS2_RX,MAX_Speed,motor_shutdown,motor_ready,free_flag);		
}
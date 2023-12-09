//Motor_Speed_pid.c
//2023.11.9
//by gjx

#include "Motor_Speed_pid.h"

PID_TypeDef motor_pid[4];
float set_spdL;// rpm  左轮角速度（转速）        1 rpm = pi/30 = 0.1047 （rad/s）    1(rad/s) = 9.55(rpm)            //Pi rad = 180度    1 rad = 180/Pi 度    1 度 = Pi/180 rad
float set_spdR;// rpm  左轮角速度（转速）

float set_spdL1;
float set_spdR1;

float Vcx = 0;   //   m/s    车辆转弯线速度    
float Wc = 0;    //   rad/s  车辆转弯角速度
float C = 0.5;     //   m      轴距
float r = 0.1;     //   m      车轮半径
int flaggg = 0;
int free_flag = 0;




float low_pass_filter(float value, float fc, float Ts)
{
	
	
	float b = fc * Ts;
  float alpha = b / (b + 1);
  static float out_last = 0; //上一次滤波值
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



void Speed_set()
{
	if(motor_ready == 1)
	{
		if(motor_shutdown == 0)
		{
		
			if((PS2_LY < 130) && (PS2_LY > 126) && (PS2_RX < 129) && (PS2_RX > 125))
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
			motor_pid[0].target = set_spdL;    //左前
			motor_pid[1].target = set_spdL;    //左后
			motor_pid[2].target = -set_spdR;    //右前
			motor_pid[3].target = -set_spdR;    //右后
			for(int i=0; i<4; i++)
			{	 																							
				motor_pid[i].f_cal_pid(&motor_pid[i],motor_chassis[i].speed_rpm);    //根据设定值进行PID计算。
			}

			CAN_cmd_chassis(motor_pid[0].output,   //将PID的计算结果通过CAN发送到电机
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
void speed_print()
{
	usart_printf("%d,%f,%f,%d,%d,%f,%d,%d,%d\n",motor_chassis[0].speed_rpm,       set_spdL,   motor_pid[0].output,   PS2_LY,PS2_RX,MAX_Speed,motor_shutdown,motor_ready,free_flag);		
}
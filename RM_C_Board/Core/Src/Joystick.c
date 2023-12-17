//Joystick.c
//2023.10.23
//by gjx

#include "Joystick.h"

# define max_count 3
float MAX_rotate_Speed = 2;
float Max_speed[max_count] = {1,2,3};
int speed_count = 0;


int motor_ready = 0;
int motor_shutdown = 0;
float MAX_Speed = 0;
int flagg = 0;
void Joystick_motor_start(void)
{

	if(PS2_KEY == 13 && PS2_LY == 128 && PS2_RX == 127)  //Y������ң�� �̵���
	{

		motor_shutdown = false;
		led_green_start();
		motor_ready = 1;
		free_flag = 0;
//		PS2_Vibration(0x00,0xFF);
//		HAL_Delay(100);
	}
	if(PS2_KEY == 16 || ((PS2_LY == 255) && (PS2_LX == 255) && (PS2_RX == 255) && (PS2_RY == 255)) || ((PS2_LY == 128) && (PS2_LX == 128) && (PS2_RX == 128) && (PS2_RY == 128)))  //X���ر�ң�� �����  //��ֹ�������
//if(PS2_KEY == 16|| ((PS2_LY == 128) && (PS2_LX == 128) && (PS2_RX == 128) && (PS2_RY == 128)))  //X���ر�ң�� �����  //��ֹ�������
	{
		motor_shutdown = 0;
		motor_ready = 0;

		led_red_start();
		
		
		speed_count = 0;
//		PS2_Vibration(0x00,0xFF);
//		HAL_Delay(100);
	}
 
	if(PS2_KEY == 14)   // B Button Pressed
	{
		motor_shutdown = 1;
		motor_ready = 1;
		free_flag = 0;
		speed_count = 0;
		led_red_start();
		
	}
}

void Joystick_v_set(void)
{
	if(PS2_KEY == 5)
	{
		if(!flagg)
		{
			if(speed_count == max_count -1)
			{
				speed_count = max_count -1;
			}
			else
			{
				speed_count +=1;
			}
			flagg =1;
		 }
//		if(speed_count == 0)
//		{
//			PS2_Vibration(0x00,0x45);
//			HAL_Delay(100);
//		}
//		if(speed_count == 1)
//		{
//			PS2_Vibration(0x00,0x60);
//			HAL_Delay(100);
//		}
//		if(speed_count == 2)
//		{
//			PS2_Vibration(0x00,0x75);
//			HAL_Delay(100);
//		}
//		if(speed_count == 3)
//		{
//			PS2_Vibration(0x00,0xFF);
//			HAL_Delay(100);
//		}
		
	}
	if(PS2_KEY == 7)
	{
		if(!flagg)
		{
			if(speed_count == 0)
			{
				speed_count = 0;
			}
			else
			{
				speed_count -=1;
			}
			flagg =1;
		 }
	 }
	if(PS2_KEY == 0)
	{
		flagg =0;
	}
	
	MAX_Speed = Max_speed[speed_count];

}
	
	


void Joystick_motor_control(void)
{		
		PS2_Receive(); // For PS2 Communication
		Joystick_v_set();
		Joystick_motor_start();

		if(motor_ready == 1)
		{
//			if(PS2_LY > 133 && PS2_LY < 135)
//			{
//				Vcx = 0;
//			}
//			else
//			{

			if(PS2_LY <= 128)
			{
				Vcx = (float)(MAX_Speed - 0)/(float)(0-128)*(PS2_LY-128);
			}
			
			if(PS2_LY > 128)
			{
				Vcx = (float)(MAX_Speed - 0)/(float)(0-127)*(PS2_LY-128);
			}
		
//			}
		
		if(Vcx > MAX_Speed)
			Vcx = MAX_Speed;
		
		if(Vcx < -MAX_Speed)
			Vcx = -MAX_Speed;

		}
//-----------------------------------------------------------------------------	
		
		if(motor_ready == 1)
		{
//			if(PS2_RX > 133 && PS2_RX < 135)
//			{
//				Wc = 0;
//			}
//			else
//			{
				
			if(PS2_LY <= 127)
			{
				Wc = (float)(MAX_rotate_Speed - 0)/(float)(0-127)*(PS2_RX-127);
			}
			
			if(PS2_LY > 127)
			{
				Wc = (float)(MAX_rotate_Speed - 0)/(float)(0-128)*(PS2_RX-127);
			}
		
//			}
		
		if(Wc > MAX_rotate_Speed)
			Wc = MAX_rotate_Speed;
		
		if(Wc < -MAX_rotate_Speed)
			Wc = -MAX_rotate_Speed;			
		}
}
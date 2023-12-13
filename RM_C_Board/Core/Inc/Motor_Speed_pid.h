#ifndef MOTOR_SPEED_PID_H
#define MOTOR_SPEED_PID_H
#include "headfile.h"

extern float set_spdL;
extern float set_spdR;
extern float set_spdL1;
extern float set_spdR1;
extern float Vcx;  
extern float Wc; 
extern bool free_flag;


void Motor_Speed_Calc(void);
void Motor_Speed_pid_init(void);
void Set_free(void);
void Speed_set(void);
void speed_print(void);
float low_pass_filter(float value, float fc, float Ts);
#endif

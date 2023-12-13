#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "headfile.h"
#include <stdbool.h>


extern bool motor_ready;
extern bool motor_shutdown;
extern int speed_count;
extern float Max_speed[];
extern float MAX_Speed;
void Joystick_motor_start(void);
void Joystick_motor_control(void);
void Joystick_v_set(void);


#endif

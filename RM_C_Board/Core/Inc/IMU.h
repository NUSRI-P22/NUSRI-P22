#ifndef IMU_H
#define IMU_H
#include "headfile.h"


extern FusionAhrs ahrs;
extern float IMUdeltaTime;

void IMU_update(void);
void IMU_print(void);
void IMU_Vofa_print(void);

#endif

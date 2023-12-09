#ifndef IMU_H
#define IMU_H
#include "headfile.h"


extern float gyro[3];
extern float accel[3];
extern float temp;

void IMU_read(void);
void IMU_print(void);
void IMU_Vofa_print(void);


#endif

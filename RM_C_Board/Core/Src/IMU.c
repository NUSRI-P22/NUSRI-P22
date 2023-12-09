//IMU.c
//2023.11.3
//by gjx

#include "IMU.h"
#include <math.h>

float gyro[3],accel[3],temp;

void IMU_read()
{
	static const float k1 = 57.295791;
	static const float k2 = 9.793;
	BMI088_read(gyro,accel,&temp);
	gyro[0] *= k1; gyro[1] *= k1; gyro[2] *= k1;
	accel[0] /= k2; accel[1] /= k2; accel[2] /= k2;
}

void IMU_print()
{
	usart_printf("Accel:X=%d,Y=%d,Z=%d\r\nGYRO:X=%d,Y=%d,Z=%d\r\ntemp=%d\r\n ",(int)(accel[0]*100),(int)(accel[1]*100),(int)(accel[2]*100),(int)(gyro[0]*100),(int)(gyro[1]*100),(int)(gyro[2]*100),(int)(temp*100));
}	
		
void IMU_Vofa_print()
{
	usart_printf("%d.%d,%d,%d,%d,%d,%d\n ",(int)(accel[0]*100),(int)(accel[1]*100),(int)(accel[2]*100),(int)(gyro[0]*100),(int)(gyro[1]*100),(int)(gyro[2]*100),(int)(temp*100));
}	
//IMU.c
//2023.11.3
//by gjx

#include "IMU.h"
#include <math.h>
#include "Fusion.h"

FusionAhrs ahrs;
float IMUdeltaTime = 0.005; // default 200Hz
float gyro[3], accel[3], temp, g = 9.975; // For SuZhou, JiangSu, China

void IMU_update()
{
	BMI088_read(gyro, accel, &temp); // read IMU Date

	const FusionVector gyroscope = {{FusionRadiansToDegrees(gyro[0]), FusionRadiansToDegrees(gyro[1]), FusionRadiansToDegrees(gyro[2])}}; // unit: dps
	const FusionVector accelerometer = FusionVectorMultiplyScalar((FusionVector){{accel[0], accel[1], accel[2]}}, 1/g); // unit: g
	//FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, IMUdeltaTime);
	const FusionVector magnetometer = {{IST8310data[0],IST8310data[1],IST8310data[2]}};
	FusionAhrsUpdate(&ahrs, gyroscope, accelerometer, magnetometer, IMUdeltaTime); // AHRS Calculation
}

void IMU_print()
{
	usart_printf("Accel:X=%d,Y=%d,Z=%d\r\nGYRO:X=%d,Y=%d,Z=%d\r\ntemp=%d\r\n ",(int)(accel[0]*100),(int)(accel[1]*100),(int)(accel[2]*100),(int)(gyro[0]*100),(int)(gyro[1]*100),(int)(gyro[2]*100),(int)(temp*100));
}	
		
void IMU_Vofa_print()
{
	usart_printf("%d.%d,%d,%d,%d,%d,%d\n ",(int)(accel[0]*100),(int)(accel[1]*100),(int)(accel[2]*100),(int)(gyro[0]*100),(int)(gyro[1]*100),(int)(gyro[2]*100),(int)(temp*100));
}	
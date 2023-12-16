//IMU.c
//2023.11.3
//by gjx

#include "IMU.h"
#include <math.h>
#include "Fusion.h"

// Do not Change!
#define g 9.795f // For SuZhou, JiangSu, China

// Initialise algorithms
FusionAhrs ahrs;
FusionOffset offset;
float IMUdeltaTime = 0.001; // default 1000Hz
float gyro[3], accel[3], temp;
FusionVector gyroscope;
FusionVector accelerometer;
FusionVector magnetometer;

// Define calibration (replace with actual calibration data if available)
const FusionMatrix gyroscopeMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // No need
const FusionVector gyroscopeSensitivity = {1.0f, 1.0f, 1.011047f}; // Done!
const FusionVector gyroscopeOffset = {0.067f, -0.045f, 0.038f}; // Done!
const FusionMatrix accelerometerMisalignment = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}; // No need
const FusionVector accelerometerSensitivity = {1.009082f, 1.006542f, 1.009082f}; // Done!
const FusionVector accelerometerOffset = {0.003f, -0.002f, -0.001f}; // Done!
const FusionMatrix softIronMatrix = {0.9580f, -0.0081f, 0.0222f, -0.0081f, 1.0402f, -0.0020f, 0.0222f, -0.0020f, 1.0041f};
const FusionVector hardIronOffset = {-4.4666f, 2.9855f, 7.9047f};


void IMU_update()
{
	BMI088_read(gyro, accel, &temp); // read IMU Date

	gyroscope = (FusionVector){{FusionRadiansToDegrees(gyro[0]), FusionRadiansToDegrees(gyro[1]), FusionRadiansToDegrees(gyro[2])}}; // unit: dps
	accelerometer = FusionVectorMultiplyScalar((FusionVector){{accel[0], accel[1], accel[2]}}, 1.0f / g); // unit: g
	magnetometer = (FusionVector){{IST8310data[0],IST8310data[1],-IST8310data[2]}};
	
	// Apply calibration
	gyroscope = FusionCalibrationInertial(gyroscope, gyroscopeMisalignment, gyroscopeSensitivity, gyroscopeOffset);
	accelerometer = FusionCalibrationInertial(accelerometer, accelerometerMisalignment, accelerometerSensitivity, accelerometerOffset);
	magnetometer = FusionCalibrationMagnetic(magnetometer, softIronMatrix, hardIronOffset);
	
	// Update gyroscope offset correction algorithm
	gyroscope = FusionOffsetUpdate(&offset, gyroscope);
	
	// FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, IMUdeltaTime);
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
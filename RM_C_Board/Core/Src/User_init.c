//User_init.c
//2023.11.3
//by gjx

#include "User_init.h"

#define SAMPLE_RATE (1.0f / IMUdeltaTime) // replace this with actual sample rate

extern FusionAhrs ahrs;
extern FusionOffset offset;
void Init_all()
{
	can_filter_init();
	Motor_Speed_pid_init();
	PS2_SetInit();
	ist8310_init();
	while(BMI088_init());
	FusionAhrsInitialise(&ahrs);
	FusionOffsetInitialise(&offset, SAMPLE_RATE);
	FusionAhrsInitialise(&ahrs);
	// Set AHRS algorithm settings
	const FusionAhrsSettings settings = {
					.convention = FusionConventionEnu,
					.gain = 0.5f,
					.gyroscopeRange = 2000.0f, /* replace this with actual gyroscope range in degrees/s */
					.accelerationRejection = 10.0f,
					.magneticRejection = 10.0f,
					.recoveryTriggerPeriod = 5 * SAMPLE_RATE, /* 5 seconds */
	};
	FusionAhrsSetSettings(&ahrs, &settings);
	//init_my_sweep();
}
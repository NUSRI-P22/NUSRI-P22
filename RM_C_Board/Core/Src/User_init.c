//User_init.c
//2023.11.3
//by gjx

#include "User_init.h"

void Init_all()
{
	can_filter_init();
	Motor_Speed_pid_init();
	PS2_SetInit();
	ist8310_init();
	while(BMI088_init());
	FusionAhrsInitialise(&ahrs);
	//nit_my_sweep();
}
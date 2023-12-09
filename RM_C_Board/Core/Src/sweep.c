//sweep.c
//2023.11.21
//by gjx

#include "sweep.h"



float t_0; /* t0 信号发送器开始工作的时刻, 单位 s */
float t_01; /* 从 t0 到 t1 的时间间隔, 单位 s */

float f0; /* 时刻 t0 对应的频率， 单位 hz */
float f1; /* 时刻 t1 对应的频率， 单位 hz */
float k; /* 指数函数的底数 */
float p; /* 系数 p */
float A; /* 扫频信号的幅值 */
float Y = 0.0f;//扫频信号
int N = 5;
float t_now = 0;
void init_my_sweep()
{  
	t_0 = 0;
	t_01 = 10;
	f0 = 0.5;
	f1 = 10;
	A = 5000;
	k = exp(log(f1 / f0) / t_01);
	float pi = acos(-1);
	p = 2 * pi * f0 / log(k);

}

void run_my_sweep()
{
	if(t_now < N*t_01)
	{	
		float t = 0.0f; //相对时间 t


		t = t_now - t_0; 
		t = fmod(t, t_01);/*通过求余操作实现，周期性扫频的过程*/

		t_now += 0.005;



		Y = A * sin(p * (pow(k, t) - 1));

		CAN_cmd_chassis(Y,0,0,0);

		usart_printf("%f,%d,%f,%f\n", Y,motor_chassis[0].speed_rpm,t_now,t);
	}
}
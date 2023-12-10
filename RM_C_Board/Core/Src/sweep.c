//sweep.c
//2023.11.21
//by gjx

#include "sweep.h"



float t_0; /* t0 �źŷ�������ʼ������ʱ��, ��λ s */
float t_01; /* �� t0 �� t1 ��ʱ����, ��λ s */

float f0; /* ʱ�� t0 ��Ӧ��Ƶ�ʣ� ��λ hz */
float f1; /* ʱ�� t1 ��Ӧ��Ƶ�ʣ� ��λ hz */
float k; /* ָ�������ĵ��� */
float p; /* ϵ�� p */
float A; /* ɨƵ�źŵķ�ֵ */
float Y = 0.0f;//ɨƵ�ź�
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
		float t = 0.0f; //���ʱ�� t


		t = t_now - t_0; 
		t = fmod(t, t_01);/*ͨ���������ʵ�֣�������ɨƵ�Ĺ���*/

		t_now += 0.005;



		Y = A * sin(p * (pow(k, t) - 1));

		CAN_cmd_chassis(Y,0,0,0);

		usart_printf("%f,%d,%f,%f\n", Y,motor_chassis[0].speed_rpm,t_now,t);
	}
}
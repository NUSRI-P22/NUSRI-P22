#ifndef SWEEP_H
#define SWEEP_H
#include "headfile.h"


extern float t_0; /* t0 信号发送器开始工作的时刻, 单位 ms */
extern float t_01; /* 从 t0 到 t1 的时间间隔, 单位 ms */

extern float f0; /* 时刻 t0 对应的频率， 单位 hz */
extern float f1; /* 时刻 t1 对应的频率， 单位 hz */
extern float k; /* 指数函数的底数 */
extern float p; /* 系数 p */
extern float A; /* 扫频信号的幅值 */
extern float Y ;//扫频信号
extern float t_now ;
extern int N;
void init_my_sweep(void);
void run_my_sweep(void);
#endif
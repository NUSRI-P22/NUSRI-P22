#ifndef HEADFILE_H
#define HEADFILE_H
#include "math.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include <bsp_can.h>
#include <CAN_receive.h>
#include <led.h>
#include <ps2.h>
#include <user_delay.h>
#include <user_usart.h>
#include <Joystick.h>

#include "BMI088driver.h"
#include "BMI088reg.h"
#include "BMI088Middleware.h"
#include "IMU.h"

#include "ist8310driver_middleWare.h"
#include "ist8310driver.h"
#include "IST.h"

#include "User_init.h"

#include "FusionAhrs.h"
#include "FusionCompass.h"
#include "FusionOffset.h"
#include "FusionMath.h"
#include "FusionCalibration.h"
#include "Fusion.h"

#include "pid.h"
#include "Motor_Speed_pid.h"

#include "sweep.h"

#include "gps.h"

#include "Task.h" // For Multi-Task
#endif

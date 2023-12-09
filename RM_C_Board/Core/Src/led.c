//led.c
//2023.10.17
//by gjx

#include "led.h"

//À¶µÆµãÁÁ
void led_blue_start(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,60000);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
}

//ÂÌµÆµãÁÁ
void led_green_start(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,60000);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
}

//ºìµÆµãÁÁ
void led_red_start(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,60000);
}

//°×µÆµãÁÁ
void led_white_start(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,60000);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,60000);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,60000);
}

//À¶µÆÏ¨Ãð
void led_blue_stop(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
}

//ÂÌµÆÏ¨Ãð
void led_green_stop(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
}

//ºìµÆÏ¨Ãð
void led_red_stop(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
}

//°×µÆÏ¨Ãð
void led_white_stop(void)
{
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
}

//À¶µÆÉÁË¸
void led_blue_blink(void)
{
	while(1)
	{
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,60000);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
	}
	
}

//ÂÌµÆÉÁË¸
void led_green_blink(void)
{
	while(1)
	{
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,60000);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
	}
	
}

//ºìµÆÉÁË¸
void led_red_blink(void)
{
	while(1)
	{
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,60000);
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
	}
	
}

//°×µÆÉÁË¸
void led_white_blink(void)
{
	while(1)
	{
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,60000);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,60000);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,60000);
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
		HAL_Delay(500);
	}
	
}





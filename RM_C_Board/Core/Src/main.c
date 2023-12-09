/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "headfile.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t flag_1ms;//程序循环标志
extern uint8_t flag_5ms;
extern uint8_t flag_10ms;
extern uint8_t flag_20ms;
extern uint8_t flag_50ms;
extern uint8_t flag_100ms;
extern uint8_t flag_200ms;
extern uint8_t flag_500ms;
extern uint8_t flag_1000ms;

extern int stop_flag;//按键中止标志



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM10_Init();
  MX_I2C3_Init();
  MX_SPI1_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
	Init_all();
	clrStruct();
	double yaw;
	double acc;
//	init_my_sweep();
	FusionAhrs ahrs;
	FusionAhrsInitialise(&ahrs);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//IO
//		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10,1);//蓝色
//		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_11,1);//绿色
//		HAL_GPIO_WritePin(GPIOH,GPIO_PIN_12,1);//红色
//		HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_11);//IO翻转
		//延时(ms)
//		HAL_Delay(5000);
//		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);//0-65535  蓝色
//		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);//0-65535  绿色
//		__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,50000);//0-65535  红色

//	  CAN_cmd_chassis(1500,0,0,0);	1500电流对应10000rpm


		if(stop_flag !=0)  //保险  按下KEY则停止程序
			
		{
//			led_red_blink();
			
		}
		else
		{
//			led_green_start();
			
		if(flag_1ms == 1)
		{
				
			flag_1ms = 0;
		}
		if(flag_5ms == 1)
		{
				Speed_set();
//			run_my_sweep();
				
				static int time = 0;
				static int dtime = 0;
				dtime = flag - time;
				const FusionVector gyroscope = {{gyro[0], gyro[1], gyro[2]}}; // unit: dps
				const FusionVector accelerometer = {{accel[0], accel[1], accel[2]}}; // unit: g
				const FusionVector magnetometer = {{IST8310data[0],IST8310data[1],IST8310data[2]}};
//				FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, 0.005f);
				FusionAhrsUpdate(&ahrs, gyroscope, accelerometer, magnetometer, 0.005f);
				time = flag;
				const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
//			const FusionVector EarthAcc = FusionAhrsGetEarthAcceleration(&ahrs);
				const FusionVector LinearAcc = FusionAhrsGetLinearAcceleration(&ahrs);
//			usart_printf("Yaw %0.1f\n", euler.angle.yaw);
				yaw = euler.angle.yaw;
//				acc = EarthAcc.axis.y;
				acc = LinearAcc.axis.x;
			//usart_printf("%0.3f,%0.3f,%0.3f\n", euler.angle.roll, euler.angle.pitch, euler.angle.yaw);
//					PS2_Receive();
			printf("%lf,%lf,%d,%d,%d,%d,%0.1f,%f,%d\n",
							Convert_to_degrees(Save_Data.latitude),
							Convert_to_degrees(Save_Data.longitude),
							motor_chassis[0].speed_rpm,
							motor_chassis[1].speed_rpm,
							-motor_chassis[2].speed_rpm,
							-motor_chassis[3].speed_rpm,
							yaw,
							acc,
							dtime);  //0左前 1左后 2右后 3右前
			flag_5ms = 0;
		}
		if(flag_10ms == 1)
		{
		
				IMU_read();
			flag_10ms = 0;
		}
		if(flag_20ms == 1) 
		{

 				//PS2_Receive();
				Joystick_motor_control();
				flag_20ms = 0;
		}
		if(flag_50ms == 1)
		{			 			
//			speed_print();
//			printf("123");

			   

			flag_50ms = 0;
		}
		if(flag_100ms == 1)
		{
			ParseGpsBuffer();
			
//			PrintGpsBuffer();
			
			flag_100ms = 0;
		}
		if(flag_200ms == 1)
		{
					
			flag_200ms = 0;
		}
		if(flag_500ms == 1)
		{
		
// 		PS2_Vofa_print();
//		IMU_print();
//		IST_print();
//   		Motor_print();
//  			Motor_Vofa_print();
			flag_500ms = 0;
		}
		if(flag_1000ms == 1)
		{
			    
			flag_1000ms = 0;
		}
		}
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

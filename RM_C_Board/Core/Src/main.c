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


extern int stop_flag; // KEY Button
extern FusionAhrs ahrs;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void VOFA_Print();

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


	
	TaskAdd(VOFA_Print, 20); // 50Hz Print to VOFA
	TaskAdd(Speed_set, 5); // 200Hz for wheel PID
	TaskAdd(IMU_update, IMUdeltaTime * 1000); // 1000Hz for updating IMU and print delta time // TaskPrintDeltaTime( TaskAdd(IMU_update, 1) );
	
	TaskAdd(Joystick_motor_control, 20); // 50Hz
	TaskAdd(ParseGpsBuffer, 100); // 10Hz

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		if(stop_flag)  // Stop Driving when stop_flag is true
		{
			// led_red_blink();
		}
		else
		{
			//led_green_start();
			//run_my_sweep();
			TaskRun();
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

extern float gyro[], accel[];
extern FusionOffset offset;
extern FusionVector gyroscope;
extern FusionVector accelerometer;
extern FusionVector magnetometer;
float real_vcx;
float real_w;    //clockwise stands for minus

void VOFA_Print(){
	const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
	const FusionVector LinearAcc = FusionAhrsGetLinearAcceleration(&ahrs);
	// const FusionVector EarthAcc = FusionAhrsGetEarthAcceleration(&ahrs);
	
	MOTORrpm2vw(motor_chassis[0].speed_rpm,-motor_chassis[2].speed_rpm,&real_vcx,&real_w);
	LongLat2XY(Convert_to_degrees(Save_Data.longitude),Convert_to_degrees(Save_Data.latitude),&gps_X,&gps_Y);
	LongLat2XY(120.742925,31.268221,&gps_X0,&gps_Y0);
	
	// Print to VOFA+
//	usart_printf("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
//			gyroscope.axis.x, gyroscope.axis.y, gyroscope.axis.z,
//			acc_x_avg, acc_y_avg, acc_z_avg,
//			magnetometer.axis.x, magnetometer.axis.y, magnetometer.axis.z,
//			euler.angle.roll, euler.angle.pitch, euler.angle.yaw
//	);
	
usart_printf("%lf,%lf,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",	
			Convert_to_degrees(Save_Data.latitude),
			Convert_to_degrees(Save_Data.longitude),
			motor_chassis[0].speed_rpm,
			motor_chassis[1].speed_rpm,
			-motor_chassis[2].speed_rpm,
			-motor_chassis[3].speed_rpm,
			real_vcx,
			real_w,
			gyro[2],
			euler.angle.roll,
			euler.angle.pitch,
			euler.angle.yaw,
			LinearAcc.axis.x,
			gps_X-gps_X0,
			gps_Y-gps_Y0
			);
	// usart_printf("%0.3f,%0.3f,%0.3f\n", euler.angle.roll, euler.angle.pitch, euler.angle.yaw);
//	 PrintGpsBuffer();
}

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

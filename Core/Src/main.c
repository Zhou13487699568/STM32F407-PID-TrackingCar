/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "beep.h"
#include "encode1.h"
#include "pid1.h"
#include "motor1.h"
#include "track_sensor.h"

#include <stdio.h>	//使用 printf
#include <string.h>	//使用 memset
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LENGTH  64  		//接收缓冲区大小
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t RxBuff[LENGTH];		//接收缓冲区
uint8_t rx_flag = 0;
uint16_t rx_len = 0;

float base_speed = 12.0f;   // 循迹基础直行速度，单位和你速度环目标一致
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//pid1新的pid函数
PID1_TypeDef pid1_left;
PID1_TypeDef pid1_right;




// 必须加volatile！！！跨中断
volatile float speed_L, speed_R;
volatile float pwmout_left,pwmout_right;
volatile float Target1_left;
volatile float Target1_right;
volatile float turn_speed;

	float pwm_left_out =0;
	float pwm_right_out =0;
			
 


uint8_t keynum;

//printf重定向
int fputc(int ch, FILE *f)
{
    uint8_t temp = ch;
    HAL_UART_Transmit(&huart2, &temp, 1, 100);
    return ch;
}

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
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);


  HAL_TIM_Base_Start_IT(&htim2);  //开启定时器中断50ms

	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);//开启编码器

	motor1_init();
//	OLED_Init();
	

	
	  pid1_Init(&pid1_left, 3.2f, 0.15f, 0.15f);
  pid1_Init(&pid1_right,3.2f, 0.15f, 0.15f);
	
		Target1_left = base_speed;
Target1_right = base_speed;
	
	printf("System Start!\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		printf("speed_left:%.2f,speed_right:%.2f\r\n",speed_L,speed_R);
		printf("pwm_left:%.2f,pwm_right:%.2f\r\n",pwm_left_out,pwm_right_out);
		printf("rho:%.2f,turn_speed:%.2f\r\n",rho,turn_speed);
		HAL_Delay(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
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
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart -> Instance == USART2)
	{
		 HAL_UART_Transmit_IT(&huart2 ,RxBuff ,Size);
		 HAL_UARTEx_ReceiveToIdle_IT(&huart2 ,RxBuff ,LENGTH);
	}
}

// 50ms 定时中断 → 计算编码器速度
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
     if(htim->Instance == TIM2)
    {
        // ========== 1. 循迹外环：计算转向差速 ==========
        Sensor_UpdateRho();                              // 更新黑线位置rho
        turn_speed = Track_PD_Calc(40.0f, rho);    // PD计算转向差速

        // 叠加差速到左右轮目标速度
        float target_L = base_speed - turn_speed;
        float target_R = base_speed + turn_speed;

        // 目标速度下限保护：避免低速弯道时倒车
        if(target_L < 0.5f) target_L = 0.5f;
        if(target_R < 0.5f) target_R = 0.5f;

        // ========== 2. 速度内环：编码器+PID+电机输出 ==========
        speed_L = (float)encode1_get(&htim5);
        speed_R = (float)encode1_get(&htim4);
        
        pwmout_left  = PID1_Calc(&pid1_left, speed_L, (int16_t)target_L);
        pwmout_right = PID1_Calc(&pid1_right, speed_R, (int16_t)target_R);
			
//			if(pwmout_left  < 0.0f) pwmout_left  = 0.0f;
//		if(pwmout_right < 0.0f) pwmout_right = 0.0f;
			
        
			 pwm_left_out  = MOTOR_DEAD_ZONE + (pwmout_left  / 100.0f) * (100.0f - MOTOR_DEAD_ZONE);
			pwm_right_out = MOTOR_DEAD_ZONE + (pwmout_right / 100.0f) * (100.0f - MOTOR_DEAD_ZONE);
			
    setpwm1_left((int16_t)pwm_left_out);
	setpwm1_right((int16_t)pwm_right_out);

}
		}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
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

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>



/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define key2_Pin GPIO_PIN_2
#define key2_GPIO_Port GPIOE
#define key0_Pin GPIO_PIN_4
#define key0_GPIO_Port GPIOE
#define ENC_left_A_Pin GPIO_PIN_0
#define ENC_left_A_GPIO_Port GPIOA
#define ENC_left_B_Pin GPIO_PIN_1
#define ENC_left_B_GPIO_Port GPIOA
#define AIN1_left_Pin GPIO_PIN_0
#define AIN1_left_GPIO_Port GPIOB
#define AIN2_right_Pin GPIO_PIN_1
#define AIN2_right_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_11
#define BEEP_GPIO_Port GPIOE
#define PWMA_Pin GPIO_PIN_8
#define PWMA_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_9
#define PWMB_GPIO_Port GPIOA
#define TR1_Pin GPIO_PIN_0
#define TR1_GPIO_Port GPIOD
#define TR2_Pin GPIO_PIN_1
#define TR2_GPIO_Port GPIOD
#define TR3_Pin GPIO_PIN_2
#define TR3_GPIO_Port GPIOD
#define TR4_Pin GPIO_PIN_3
#define TR4_GPIO_Port GPIOD
#define TR5_Pin GPIO_PIN_4
#define TR5_GPIO_Port GPIOD
#define TR6_Pin GPIO_PIN_6
#define TR6_GPIO_Port GPIOD
#define TR7_Pin GPIO_PIN_7
#define TR7_GPIO_Port GPIOD
#define BIN2_right_Pin GPIO_PIN_3
#define BIN2_right_GPIO_Port GPIOB
#define BIN2_left_Pin GPIO_PIN_4
#define BIN2_left_GPIO_Port GPIOB
#define STBY_Pin GPIO_PIN_5
#define STBY_GPIO_Port GPIOB
#define ENC_right_A_Pin GPIO_PIN_6
#define ENC_right_A_GPIO_Port GPIOB
#define ENC_right_B_Pin GPIO_PIN_7
#define ENC_right_B_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define MOTOR_DEAD_ZONE 30
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

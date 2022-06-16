/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW1_Pin GPIO_PIN_0
#define SW1_GPIO_Port GPIOF
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOF
#define J7_GPIO_Pin GPIO_PIN_0
#define J7_GPIO_GPIO_Port GPIOA
#define J9_GPIO_Pin GPIO_PIN_1
#define J9_GPIO_GPIO_Port GPIOA
#define J8_GPIO_Pin GPIO_PIN_2
#define J8_GPIO_GPIO_Port GPIOA
#define J10_GPIO_Pin GPIO_PIN_3
#define J10_GPIO_GPIO_Port GPIOA
#define BATT_Pin GPIO_PIN_4
#define BATT_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_0
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_1
#define LED3_GPIO_Port GPIOB
#define J11_GPIO_Pin GPIO_PIN_8
#define J11_GPIO_GPIO_Port GPIOA
#define UNUSED_Pin GPIO_PIN_9
#define UNUSED_GPIO_Port GPIOA
#define RC_RX_Pin GPIO_PIN_10
#define RC_RX_GPIO_Port GPIOA
#define U3_IN1_Pin GPIO_PIN_15
#define U3_IN1_GPIO_Port GPIOA
#define U3_IN2_Pin GPIO_PIN_3
#define U3_IN2_GPIO_Port GPIOB
#define U3_PWM_Pin GPIO_PIN_4
#define U3_PWM_GPIO_Port GPIOB
#define U3_PWMB5_Pin GPIO_PIN_5
#define U3_PWMB5_GPIO_Port GPIOB
#define U1_IN1_Pin GPIO_PIN_6
#define U1_IN1_GPIO_Port GPIOB
#define U1_IN2_Pin GPIO_PIN_7
#define U1_IN2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
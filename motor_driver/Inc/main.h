/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D7_CH3_Pin GPIO_PIN_0
#define D7_CH3_GPIO_Port GPIOF
#define ultrasound3_echo_Pin GPIO_PIN_1
#define ultrasound3_echo_GPIO_Port GPIOF
#define infrared1_gpio_Pin GPIO_PIN_0
#define infrared1_gpio_GPIO_Port GPIOA
#define infrared2_gpio_Pin GPIO_PIN_1
#define infrared2_gpio_GPIO_Port GPIOA
#define CS_OF_Pin GPIO_PIN_4
#define CS_OF_GPIO_Port GPIOA
#define infrared1_Pin GPIO_PIN_0
#define infrared1_GPIO_Port GPIOB
#define infrared1_EXTI_IRQn EXTI0_IRQn
#define infrared2_Pin GPIO_PIN_1
#define infrared2_GPIO_Port GPIOB
#define infrared2_EXTI_IRQn EXTI1_IRQn
#define D9_CH1_Pin GPIO_PIN_8
#define D9_CH1_GPIO_Port GPIOA
#define D1_CH2_Pin GPIO_PIN_9
#define D1_CH2_GPIO_Port GPIOA
#define ultrasound2_echo_Pin GPIO_PIN_10
#define ultrasound2_echo_GPIO_Port GPIOA
#define D10_CH4_Pin GPIO_PIN_11
#define D10_CH4_GPIO_Port GPIOA
#define ultrasound1_echo_Pin GPIO_PIN_12
#define ultrasound1_echo_GPIO_Port GPIOA
#define ultrasound_trigger_Pin GPIO_PIN_4
#define ultrasound_trigger_GPIO_Port GPIOB
#define ultrasound4_echo_Pin GPIO_PIN_5
#define ultrasound4_echo_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

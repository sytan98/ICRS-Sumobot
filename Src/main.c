/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "distance.h"
#include "motor.h"
#include "opticalflow.h"
#include "compass.h"
#include "CompassOptical.h"

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
    uint8_t hello[15] = "Hello World!\r\n";
    uint8_t OPFSuccess[30] = "Optical Flow Setup Success!\r\n";
    uint8_t txBuf[30];

    int16_t deltaX = 0, deltaY = 0;
    int16_t *deltaXptr = &deltaX;
    int16_t *deltaYptr = &deltaY;
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
//    HAL_UART_Transmit(&huart2, hello, sizeof(hello), 5);
//    if (initPMW3901s())
//        HAL_UART_Transmit(&huart2, OPFSuccess, sizeof(OPFSuccess), 5);
//
//    HAL_Delay(1000);
//    compass_init();
//    HAL_Delay(1000);
    startAngle = 0;
    updatePos(0, 0, 0);
    printf("current pos: x:%d, y:%d\n", (int)xycoords[0], (int)xycoords[1]);
    updatePolarCoords();
    printf("current polar pos: r:%f, theta:%f\n", polarcoords[0], polarcoords[1]);

    updateMaxSensorRange(0);

    for(int i = 0; i < 6; i++){
        printf("Sensor %d reading: %f\n", i, maxSensorRange[i]);
    }

    HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {

        // TEST STUFF
        HAL_Delay(500);

        // TEST STUFF END

        // Logic if enemy is detected
        // Assume locateEnemy is defined in distance.c and returns an int corresponding to location of enemy
        // 00 = Enemy not seen, 18 = Enemy between ultrasound 1 & 8, etc
        struct us_sensor enemyLocation = getClosestEnemies();
        if (enemyLocation.name == 0) {
            moveTank(10, 10);
            delayMicroseconds(50);
            moveTank(0, 0);
            continue;
        } else {
            switch (enemyLocation.name) {
                case 1: //Enemy is NNE, move slightly to the right
                    HAL_UART_Transmit(&huart2, "moving NNE\r\n", 12 - 1, 1000);
                    moveTank(100, 80);
                    break;
                case 2:
                    // Enemy is NE, move more to the right
                    HAL_UART_Transmit(&huart2, "moving ENE\r\n", 12 - 1, 1000);
                    moveTank(100, 70);
                    break;
                case 3:
                    // Enemy is ESE, turn right
                    HAL_UART_Transmit(&huart2, "moving ESE\r\n", 12 - 1, 1000);
                    moveTank(100, -50);
                    break;
                case 4:
                    // Enemy is SSE, turn right faster
                    HAL_UART_Transmit(&huart2, "moving SSE\r\n", 12 - 1, 1000);
                    moveTank(100, -75);
                    break;
                case 5:
                    // Enemy is SSW, turn left faster
                    HAL_UART_Transmit(&huart2, "moving SSW\r\n", 12 - 1, 1000);
                    moveTank(-75, 100);
                    break;
                case 6:
                    // Enemy is WSW, turn left
                    HAL_UART_Transmit(&huart2, "moving WSW\r\n", 12 - 1, 1000);
                    moveTank(-50, 100);
                    break;
                case 7:
                    // Enemy is NW, move more to the left
                    HAL_UART_Transmit(&huart2, "moving WNW\r\n", 12 - 1, 1000);
                    moveTank(70, 100);
                    break;
                case 8://Enemy is NNW, move slightly to the right
                    HAL_UART_Transmit(&huart2, "moving NNW\r\n", 12 - 1, 1000);
                    moveTank(80, 100);
                    break;
            }
            HAL_Delay(50);
        }


    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

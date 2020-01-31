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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "distance.h"
#include "motor.h"
#include "init_tests.h"
#include "UARTlink.h"
#include "remoteControl.h"

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
// Variables used in remote control
int TESTING_MODE = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void isFilterMode();

void torqueCheck();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int INITIAL_MOVEMENT = 0;
uint8_t data[14];
uint8_t request[1] = {'0'};
int8_t packet;
int32_t power;
int16_t heading;
int16_t deltaX;
int16_t deltaY;
int16_t tof1;
int16_t tof2;
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
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
    DWT_Init();
    pwm_init();
    remoteControl_init();

    if (TESTING_MODE) {
        __set_BASEPRI(2 << 4); // Disables all interrupts with priority 2 or lower
        printf("ENTERING TESTING MODE\n\n");
        run_tests();
        __set_BASEPRI(5 << 4); // Re-enables IR interrupts
        HAL_Delay(2000);
    }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        // TEST STUFF
        __set_BASEPRI(2 << 4);
            printf("Hi\n");
        pollUART(&huart1, data);
        parsePacket(data, &power, &heading, &deltaX, &deltaY, &tof1, &tof2);
        for (int i = 0; i < 14; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
        printf("time of flight 1 is %d\n", tof1);
        printf("time of flight 2 is %d\n", tof2);
        HAL_Delay(500);

        // TEST STUFF END

        // Controller turned off at start
        // By default, this will only be entered once, at the start
        __set_BASEPRI(2 << 4);
        while (get_RIGHT_KNOB() == 0) {
            moveTank(0, 0);
            HAL_Delay(500);
            printf("Controller is off!\n");
        }

        // Waiting mode
        while (get_RIGHT_KNOB() > (RIGHT_KNOB_MIN + 100) &&
               get_RIGHT_KNOB() < (RIGHT_KNOB_MAX - 100)) {
            check_right_knob_online();
            int INITIAL_MOVEMENT = 0;
            moveTank(0, 0);
            HAL_Delay(500);
            printf("Waiting to start...\n");
        }

        // Control mode
        while (get_RIGHT_KNOB() > RIGHT_KNOB_MAX - 100) {
            check_right_knob_online();

            int right_toggle = (int) get_RIGHT_TOGGLE();
            int left_toggle = (int) get_LEFT_TOGGLE();
            printf("\nControl mode\n");
            printf("Right toggle Diff is %d\n", right_toggle);
            printf("Right Knob Diff is %d\n", (int) get_RIGHT_KNOB());
            printf("Left toggle is %d\n", left_toggle);
            HAL_Delay(5);

            float steering = (float) (right_toggle - RIGHT_TOGGLE_MIN) /
                             (float) (RIGHT_TOGGLE_MAX - RIGHT_TOGGLE_MIN) *
                             200 - 100;
            float speed = (float) (left_toggle - LEFT_TOGGLE_MIN) /
                          (float) (LEFT_TOGGLE_MAX - LEFT_TOGGLE_MIN) * 200 -
                          100;
            printf("steering: %d\n", (int) steering);
            printf("speed: %d\n", (int) speed);
            moveSteering((int) speed, (int) steering);

        }
        __set_BASEPRI(5 << 4);

        // Auto mode
        while (get_RIGHT_KNOB() < RIGHT_KNOB_MIN + 100) {
            printf("Automode\n");

            if (!INITIAL_MOVEMENT) {
                moveTank(-60, -100);
                HAL_Delay(400);
                INITIAL_MOVEMENT = 1;
                moveTank(0, 0);
                HAL_Delay(2000);
            }

//            int dist1 = getDistance(1);
//            int dist2 = getDistance(2);
//            int dist3 = getDistance(3);
//            int dist4 = getDistance(4);
//
//            printf("dist1: %03d\n", dist1);
//            printf("dist2: %03d\n", dist2);
//            printf("dist3: %03d\n", dist3);
//            printf("dist4: %03d\n", dist4);

            pollUART(&huart1, data);
            parsePacket(data, &power, &heading, &deltaX, &deltaY, &tof1, &tof2);

            struct us_sensor us1 = getClosestEnemies();
            int enemyLocation = us1.name;
            float distance = us1.distance;

            printf("name: %d\n", enemyLocation);
            printf("dist: %d\n", (int) distance);

            switch (enemyLocation) {
                case 1:
                    moveTank(100, 100);
                    break;
                case 2:
                    moveTank(60, -60);
                    break;
                case 3:
                    moveTank(-60, 60);
                    break;
                case 4:
                    moveTank(80, 100);
                    break;
                case 5:
                    moveTank(100, 80);
                    break;
            }

            HAL_Delay(500);
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int getTOF1() {
    return tof1;
}

int getTOF2() {
    return tof2;
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

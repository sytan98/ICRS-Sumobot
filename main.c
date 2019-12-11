/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char string[] = "hello world";
/* USER CODE END PV */

int main(void) {
    // Assume peripherals reset and initialised, flash interface initialised, system clock configured

    /* USER CODE BEGIN 2 */
    printf(string);
    //printf('c');
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
      do_something()
    }
    /* USER CODE END WHILE */
}

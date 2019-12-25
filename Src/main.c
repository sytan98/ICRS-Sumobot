/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include <stdio.h>
#include "infrared.c"
#include "distance.c"
#include "motor.c"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char string[] = "hello";
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
void funcA();
/* USER CODE END PFP */

int main(void) {
    // Assume peripherals reset and initialised, flash interface initialised, system clock configured

    /* USER CODE BEGIN 2 */
    printf(string);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        // Logic if enemy is detected
        // Assume locateEnemy is defined in distance.c and returns an int corresponding to location of enemy
        // 00 = Enemy not seen, 18 = Enemy between ultrasound 1 & 8, etc
        int enemyLocation = locateEnemy();
        if (enemyLocation == 0) {
            moveSimple(10, 10);
            delay(50);
            moveSimple(0, 0);
            continue;
        }
        else {
            switch (enemyLocation) {
                case 18:
                    // Enemy is N, move straight ahead
                    moveSimple(100,100);
                case 12:
                    // Enemy is NE, move straight, but turn right a little
                    moveSimple(100, 75);
                case 23:
                    // Enemy is E, turn right
                    moveSimple(50, -50);
                case 34:
                    // Enemy is SE, turn right faster
                    moveSimple(75, -75);
                case 45:
                    // Enemy is S, turn around asap
                    moveSimple(100, -100);
                case 56:
                    // Enemy is SW, turn left faster
                    moveSimple(-75, 75);
                case 67:
                    // Enemy is W, turn left
                    moveSimple(-50, 50);
                case 78:
                    // Enemy is NE, move straight, but turn left a little
                    moveSimple(75, 100);
            }
            delay(50);
            continue;
        }

    }
    /* USER CODE END WHILE */
}

/* USER CODE BEGIN 4 */
void funcA() {
    int a = 1;
}
/* USER CODE END 4 */
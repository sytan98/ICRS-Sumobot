#include "infrared.h"

void lineDetected(int n) {
    // TODO: update getDistance to accept single int argument only
    // TODO: Create new function getSingleClosestEnemy in distance.c
    // (maybe) create a function that handles when the enemy is NE/NW/SE/SW and
    // use it in both infrared.c and in main.c
    struct us_sensor us1 = getClosestEnemies();
    int enemyLocation = us1.name;
    float distance = us1.distance;

    // if line detected is NE
    if (n == 1) {
        while (!HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port,
                                 infrared1_gpio_Pin)) {
            // and enemy is NE, BAMBOOZLED! so continue NE
            if ((enemyLocation == 1) && distance < 10) {
                moveTank(100, 75);
                uint8_t greenLEDMessage[] = "interrupt 1, case 1\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
            } else { // actual line, so move backwards
                moveTank(-100, -90);
                uint8_t greenLEDMessage[] = "interrupt1, case 2\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is SE
    if (n == 2) {
        // and enemy is behind us, rotate clockwise
        while (!HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                 infrared2_gpio_Pin)) {
            if ((enemyLocation == 2) && distance < 10) {
                uint8_t greenLEDMessage[] = "interrupt2, case 1\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(75, -75);
            } else { // actual line, so move forwards
                uint8_t greenLEDMessage[] = "interrupt2, case 2\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(90, 100);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is SW
    if (n == 3) {
        // and enemy is behind us, rotate anti-clockwise
        while (!HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                 infrared2_gpio_Pin)) {
            if ((enemyLocation == 5 || enemyLocation == 6) && distance < 5) {
                uint8_t greenLEDMessage[] = "interrupt3, case 1\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(-75, 75);
            } else { // actual line, so move forwards
                uint8_t greenLEDMessage[] = "interrupt3, case 2\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(100, 90);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is NW
    if (n == 3) {
        // and enemy is in front of us, push NW
        while (!HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                 infrared2_gpio_Pin)) {
            if ((enemyLocation == 7 || enemyLocation == 8) && distance < 5) {

                uint8_t greenLEDMessage[] = "interrupt4, case 1\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(75, 100);
            } else { // actual line, so move backwards
                uint8_t greenLEDMessage[] = "interrupt4, case 2\r\n";
                HAL_UART_Transmit(&huart2, greenLEDMessage,
                                  sizeof(greenLEDMessage) - 1, 1000);
                moveTank(-100, -90);
            }
            HAL_Delay(2000);
        }
    }
}
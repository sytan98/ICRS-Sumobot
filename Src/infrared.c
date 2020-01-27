#include "infrared.h"

#define THRESHOLD_DISTANCE 10

void lineDetected(int n) {

    struct us_sensor us1 = getClosestEnemies();
    int enemyLocation = us1.name;
    float distance = us1.distance;

    // if line detected is NE
    if (n == 1) {
        while (!HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port,
                                 infrared1_gpio_Pin)) {
            // and enemy is NE, BAMBOOZLED! so continue NE
            if (enemyLocation == 1 && distance < THRESHOLD_DISTANCE) {
                printf("interrupt 1, case 1\n");
                moveTank(100, 75);
            } else { // actual line, so move backwards
                printf("interrupt 1, case 2\n");
                moveTank(-100, -90);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is SE
    if (n == 2) {
        // and enemy is behind us, rotate clockwise
        while (!HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                 infrared2_gpio_Pin)) {
            if (enemyLocation == 2 && distance < THRESHOLD_DISTANCE) {
                printf("interrupt 2, case 1\n");
                moveTank(75, -75);
            } else { // actual line, so move forwards
                printf("interrupt 2, case 2\n");
                moveTank(90, 100);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is SW
    if (n == 3) {
        // and enemy is behind us, rotate anti-clockwise
        while (!HAL_GPIO_ReadPin(infrared3_gpio_GPIO_Port,
                                 infrared3_gpio_Pin)) {
            if (enemyLocation == 3 && distance < THRESHOLD_DISTANCE) {
                printf("interrupt 3, case 1\n");
                moveTank(-75, 75);
            } else { // actual line, so move forwards
                printf("interrupt 3, case 2\n");
                moveTank(100, 90);
            }
            HAL_Delay(2000);
        }
    }

    // if line detected is NW
    if (n == 4) {
        // and enemy is in front of us, push NW
        while (!HAL_GPIO_ReadPin(infrared4_gpio_GPIO_Port,
                                 infrared4_gpio_Pin)) {
            if (enemyLocation == 4 && distance < THRESHOLD_DISTANCE) {
                printf("interrupt 4, case 1\n");
                moveTank(75, 100);
            } else { // actual line, so move backwards
                printf("interrupt 4, case 2\n");
                moveTank(-100, -90);
            }
            HAL_Delay(2000);
        }
    }
}
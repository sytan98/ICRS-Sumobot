#include "init_tests.h"
#define ULTRASOUND_TEST_DISTANCE 10.0 //Distance in cm

void run_tests() {
    ultrasound_TOF_test();
    infrared_test();
    controller_test();
    motor_test();
}

static void ultrasound_TOF_test() {
    printf("Starting ultrasound test\n");
    /* Array distances
     * 1 : Ultrasound 1 (Front)
     * 2 : Ultrasound 2 (Right)
     * 3 : Ultrasound 3 (Left)
     * 4 : TOF 1 (Front left)
     * 5 : TOF 2 (Front right)
     */
    float us_distances[5];
    us_distances[0] = 1000;
    us_distances[1] = 1000;
    us_distances[2] = 1000;
    us_distances[3] = 1000;
    us_distances[4] = 1000;

    while (us_distances[0] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[1] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[2] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[3] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[4] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[0] <= 0 ||
            us_distances[1] <= 0 ||
            us_distances[2] <= 0 ||
            us_distances[3] <= 0 ||
            us_distances[4] <= 0) {
        us_distances[0] = getDistance(1);
        us_distances[1] = getDistance(2);
        us_distances[2] = getDistance(3);
        us_distances[3] = getTOF1();
        us_distances[4] = getTOF2();

        printf("\nUltrasound 1 distance: %03d\n", (int) us_distances[0]);
        printf("Ultrasound 2 distance: %03d\n", (int) us_distances[1]);
        printf("Ultrasound 3 distance: %03d\n", (int) us_distances[2]);
        printf("TOF 1 distance: %03d\n", (int) us_distances[3]);
        printf("TOF 2 distance: %03d\n", (int) us_distances[4]);
        HAL_Delay(500);
    }

    HAL_Delay(500);
    printf("Ultrasound/TOF test passed, all distances less than %03dcm\n",
            (int) ULTRASOUND_TEST_DISTANCE);
}

static void infrared_test() {
    printf("Starting infrared test\n");
    int ir_booleans[4] = {0, 0, 0, 0};
    while (!ir_booleans[0] || !ir_booleans[1]
        || !ir_booleans[2]) {
        ir_booleans[0] = !HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port,
                                           infrared1_gpio_Pin);
        ir_booleans[1] = !HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                           infrared2_gpio_Pin);
        ir_booleans[2] = !HAL_GPIO_ReadPin(infrared3_gpio_GPIO_Port,
                                           infrared3_gpio_Pin);

        printf("\nInfrared 1 boolean: %01d\n", ir_booleans[0]);
        printf("Infrared 2 boolean: %01d\n", ir_booleans[1]);
        printf("Infrared 3 boolean: %01d\n", ir_booleans[2]);

        HAL_Delay(500);
    }

    printf("Infrared test passed\n");
    HAL_Delay(1000);
}

static void motor_test() {
    printf("Starting motor test\n");
    printf("If test is successful, trigger infrared1 to move on to next test\n");

    HAL_Delay(1000);

    printf("Move left motor full speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveLeftMotor(100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move left motor backward full speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveLeftMotor(-100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move right motor full speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveRightMotor(100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move right motor backward full speed\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveRightMotor(-100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move backwards full speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveBackwards(100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move backwards 50% speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveBackwards(50);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move forwards full speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveForward(100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move forwards 50% speed:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveForward(50);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move tank function: 75% left, 25% right:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveTank(75, 25);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Move tank function: 25% left, 75% right:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveTank(25, 75);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Steering - turn right:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveSteering(100, 100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Steering - turn right one wheel:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveSteering(10, 40);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Steering - turn left:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveSteering(100, -100);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("Steering - turn left one wheel:\n");
    while (HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port, infrared1_gpio_Pin)) {moveSteering(100, -40);}
    printf("Test passed!\n");

    HAL_Delay(1000);

    printf("SUCCESS\n");
    printf("End of motor test\n");
}

static void controller_test() {
    printf("Starting controller test\n");

    HAL_Delay(1000);
    printf("Testing right knob..\n");
    while (get_RIGHT_KNOB() > RIGHT_KNOB_MIN + 50) {
        printf("Move right knob to minimum. Right knob: %d",
                get_RIGHT_KNOB());
    }
    while (get_RIGHT_KNOB() < RIGHT_KNOB_MAX - 50) {
        printf("Move right knob to maximum. Right knob: %d",
                get_RIGHT_KNOB());
    }

    HAL_Delay(1000);
    printf("Testing left toggle..\n");
    while (get_LEFT_TOGGLE() > LEFT_TOGGLE_MIN + 50) {
        printf("Move left toggle to minimum. Left toggle: %d",
                get_LEFT_TOGGLE());
    }
    while (get_LEFT_TOGGLE() < LEFT_TOGGLE_MAX - 50) {
        printf("Move left toggle to maximum. Left toggle: %d",
                get_LEFT_TOGGLE());
    }

    HAL_Delay(1000);
    printf("Testing right toggle..\n");
    while (get_RIGHT_TOGGLE() > RIGHT_TOGGLE_MIN + 50) {
        printf("Move right toggle to minimum. Right toggle: %d",
                get_RIGHT_TOGGLE());
    }
    while (get_RIGHT_TOGGLE() < RIGHT_TOGGLE_MAX - 50) {
        printf("Move right toggle to maximum. Right toggle: %d",
                get_RIGHT_TOGGLE());
    }

    HAL_Delay(2000);
    printf("SUCCESS\n");
    printf("End of controller test\n");
}

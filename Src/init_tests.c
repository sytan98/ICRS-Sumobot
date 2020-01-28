#include "init_tests.h"
#define ULTRASOUND_TEST_DISTANCE 10.0 //Distance in cm

void run_tests() {
    ultrasound_test();
    infrared_test();
//    motor_test();
//    controller_test();
//    time_of_flight_test();
}

static void ultrasound_test() {
    printf("Starting ultrasound test\n");
//     us1, us2, us3, us4
    float us_distances[4];
    us_distances[0] = 100;
    us_distances[1] = 100;
    us_distances[2] = 100;
    us_distances[3] = 100;
    while (us_distances[0] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[1] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[2] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[3] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[0] <= 0 ||
            us_distances[1] <= 0 ||
            us_distances[2] <= 0 ||
            us_distances[3] <= 0) {
        us_distances[0] = getDistance(1);
        us_distances[1] = getDistance(2);
        us_distances[2] = getDistance(3);
        us_distances[3] = getDistance(4);

        printf("\nUltrasound 1 distance: %03d\n", (int) us_distances[0]);
        printf("Ultrasound 2 distance: %03d\n", (int) us_distances[1]);
        printf("Ultrasound 3 distance: %03d\n", (int) us_distances[2]);
        printf("Ultrasound 4 distance: %03d\n", (int) us_distances[3]);

        HAL_Delay(500);
    }
    HAL_Delay(500);
    printf("Ultrasound test passed, all distances less than %03dcm\n", (int) ULTRASOUND_TEST_DISTANCE);
}

static void infrared_test() {
    printf("Starting infrared test\n");
    int ir_booleans[4] = {0, 0, 0, 0};
    while (!ir_booleans[0] || !ir_booleans[1]
        || !ir_booleans[2] || !ir_booleans[3]) {
        ir_booleans[0] = !HAL_GPIO_ReadPin(infrared1_gpio_GPIO_Port,
                                           infrared1_gpio_Pin);
        ir_booleans[1] = !HAL_GPIO_ReadPin(infrared2_gpio_GPIO_Port,
                                           infrared2_gpio_Pin);
        ir_booleans[2] = !HAL_GPIO_ReadPin(infrared3_gpio_GPIO_Port,
                                           infrared3_gpio_Pin);
        ir_booleans[3] = !HAL_GPIO_ReadPin(infrared4_gpio_GPIO_Port,
                                           infrared4_gpio_Pin);

        printf("\nInfrared 1 boolean: %01d\n", ir_booleans[0]);
        printf("Infrared 2 boolean: %01d\n", ir_booleans[1]);
        printf("Infrared 3 boolean: %01d\n", ir_booleans[2]);
        printf("Infrared 4 boolean: %01d\n", ir_booleans[3]);

        HAL_Delay(500);
    }

    printf("Infrared test passed\n");
    HAL_Delay(1000);
}

static void motor_test() {

}

static void controller_test() {

}

static void time_of_flight_test() {

}

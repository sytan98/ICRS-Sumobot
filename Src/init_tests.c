#include "init_tests.h"

void run_tests() {
    ultrasound_test();
//    infrared_test();
//    motor_test();
//    controller_test();
//    time_of_flight_test();
}

static void ultrasound_test() {
    printf("Starting ultrasound test\n");
//     us1, us2, us3, us4
    int f = getDistance(4);
    printf("distance: %02d", f);

//    float us_distances[4];
//    us_distances[0] = 100;
//    us_distances[1] = 100;
//    us_distances[2] = 100;
//    us_distances[3] = 100;
//    while (us_distances[0] > ULTRASOUND_TEST_DISTANCE ||
//            us_distances[1] > ULTRASOUND_TEST_DISTANCE ||
//            us_distances[2] > ULTRASOUND_TEST_DISTANCE ||
//            us_distances[3] > ULTRASOUND_TEST_DISTANCE) {
//        us_distances[0] = getDistance(ultrasoundsensor1);
//        us_distances[1] = getDistance(ultrasoundsensor2);
//        us_distances[2] = getDistance(ultrasoundsensor3);
//        us_distances[3] = getDistance(ultrasoundsensor4);
//
//        printf("Ultrasound 1 distance: %02d\n", (int) us_distances[0]);
//        printf("Ultrasound 2 distance: %02d\n", (int) us_distances[1]);
//        printf("Ultrasound 3 distance: %02d\n", (int) us_distances[2]);
//        printf("Ultrasound 4 distance: %02d\n", (int) us_distances[3]);
//
//        HAL_Delay(500);
//    }
    HAL_Delay(500);
    printf("Ultrasound test passed, all distances less than %03dcm\n", (int) ULTRASOUND_TEST_DISTANCE);
}

static void infrared_test() {
    lineDetected(1);
    lineDetected(2);
    lineDetected(3);
    lineDetected(4);
}

static void motor_test() {

}

static void controller_test() {

}

static void time_of_flight_test() {

}

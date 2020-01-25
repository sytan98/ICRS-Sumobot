#include "init_tests.h"

void run_tests() {
    ultrasound_test();
    infrared_test();
    motor_test();
    controller_test();
    time_of_flight_test();
}

static void ultrasound_test() {
    // us1, us2, us3, us4
    float us_distances[5] = {100, 100, 100, 100};
    while (us_distances[0] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[1] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[2] > ULTRASOUND_TEST_DISTANCE ||
            us_distances[3] > ULTRASOUND_TEST_DISTANCE) {
        us_distances[0] = getDistance(ultrasoundsensor1);
        us_distances[1] = getDistance(ultrasoundsensor2);
        us_distances[2] = getDistance(ultrasoundsensor3);
        us_distances[3] = getDistance(ultrasoundsensor4);

        printf("Ultrasound 1 distance: %02d", (int) us_distances[0]);
        printf("Ultrasound 2 distance: %02d", (int) us_distances[1]);
        printf("Ultrasound 3 distance: %02d", (int) us_distances[2]);
        printf("Ultrasound 4 distance: %02d", (int) us_distances[3]);
    }
}

static void infrared_test() {

}

static void motor_test() {

}

static void controller_test() {

}

static void time_of_flight_test() {

}

#ifndef ICRS_SUMOBOT_INIT_TESTS_H
#define ICRS_SUMOBOT_INIT_TESTS_H

#include "utils.h"
#include "distance.h"
#include "infrared.h"
#include "motor.h"

#define ULTRASOUND_TEST_DISTANCE 10.0 //Distance in cm

void run_tests();
static void ultrasound_test();
static void infrared_test();
static void motor_test();
static void controller_test();
static void time_of_flight_test();

#endif //ICRS_SUMOBOT_INIT_TESTS_H

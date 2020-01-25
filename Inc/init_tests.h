#ifndef ICRS_SUMOBOT_INIT_TESTS_H
#define ICRS_SUMOBOT_INIT_TESTS_H

#import "utils.h"
#import "distance.h"
#import "infrared.h"
#import "motor.h"

#define ULTRASOUND_TEST_DISTANCE 10.0 //Distance in cm

void run_tests();
static void ultrasound_test();
static void infrared_test();
static void motor_test();
static void controller_test();
static void time_of_flight_test();

#endif //ICRS_SUMOBOT_INIT_TESTS_H

#ifndef ICRS_SUMOBOT_INIT_TESTS_H
#define ICRS_SUMOBOT_INIT_TESTS_H

#include "utils.h"
#include "distance.h"
#include "infrared.h"
#include "motor.h"
#include "remoteControl.h"

void run_tests();
static void ultrasound_TOF_test();
static void infrared_test();
static void controller_test();
static void motor_test();


#endif //ICRS_SUMOBOT_INIT_TESTS_H

//
// Created by tianyilim on 1/21/20.
//

#ifndef ICRS_SUMOBOT_SERVO_H
#define ICRS_SUMOBOT_SERVO_H

#include "main.h"
#include "tim.h"

void servo_init();
void servowrite(int servo, int angle);

#endif //ICRS_SUMOBOT_SERVO_H

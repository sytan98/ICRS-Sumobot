//
// Created by tianyilim on 1/18/20.
//

#ifndef MOTOR_DRIVER_MOTOR_DRIVER_H
#define MOTOR_DRIVER_MOTOR_DRIVER_H

#include "main.h"
#include "tim.h"

// define primitive functions
void pwm_init(void);
void analogWrite(int pin, int speed);

// Motor driver functions

void moveSteering(int speed, int steering);
void moveTank(int leftSpeed, int rightSpeed);
void moveForward(int speed);
void moveBackwards(int speed);
void moveLeftMotor(int speed);
void moveRightMotor(int speed);


#endif //MOTOR_DRIVER_MOTOR_DRIVER_H

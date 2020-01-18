//
// Created by tianyilim on 1/18/20.
//

/* ports:
 * Right Motor: D0 and D1 (CH3 and CH2)
 * Left Motor: D9 and D10 (CH1 and CH4)
 */

/* Hardware config for motor driver:
 * VIN - Battery terminal
 * GND - Ground
 * Vdd, SF, FB - disconnect
 * IN1 - CH1 / CH3
 * IN2 - CH2 / CH4
 * D2 - 5V
 * D1 - GND
 * EN - 5V
 * SLEW - 5V
 * INV - something
 */

#include "motor.h"

void pwm_init(void){
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}
void analogWrite(int channel, int speed){
    switch(channel)
    {
        case 1:
            htim1.Instance->CCR1 = speed;
            break;

        case 2:
            htim1.Instance->CCR2 = speed;
            break;

        case 3:
            htim1.Instance->CCR3 = speed;
            break;

        case 4:
            htim1.Instance->CCR4 = speed;
            break;

    }
}

// speed ranges from 100 to -100 (forward / backwards)
// steering ranges from 100 to -100 (right / left)
// 100 is turning clockwise (right) on the spot for example.
// -100 is turning anti-clockwise (left) on the spot
// 0 moves directly straight
// 50/-50 turns with one wheel only

void moveSteering(int speed, int steering){
    if (steering > 0) {
        // steering > 0, turn right: Left motor stays unchanged, Right motor is scaled.
        moveLeftMotor(speed);
        moveRightMotor(100 + (-2*speed));
    }  else if (steering < 0) {
        // steering < 0, turn left: Right motor stays unchanged, Left motor is scaled.
        moveRightMotor(speed);
        moveLeftMotor(100 + (2*speed));
    } else {
        // Steering is 0, move straight
        moveForward(speed); // doesn't matter if speed is negative, due to the definition of moveforward anyway.
    }
}

void moveTank(int leftSpeed, int rightSpeed){
    moveRightMotor(rightSpeed);
    moveLeftMotor(leftSpeed);
}
// Sets both speeds as the same
void moveForward(int speed){
    moveLeftMotor(speed);
    moveRightMotor(speed);
}

void moveBackwards(int speed){
    speed *= -1;
    moveLeftMotor(speed);
    moveRightMotor(speed);
}

void moveLeftMotor(int speed){
    if(speed > 0){
        analogWrite(1, speed);
        analogWrite(4, 0);
    }  else {
        analogWrite(4, -1*speed);
        analogWrite(1, 0);
    }
}

void moveRightMotor(int speed){
    if(speed > 0){
        analogWrite(2, speed);
        analogWrite(3, 0);
    } else if (speed <= 0) {
        analogWrite(3, -1*speed);
        analogWrite(2, 0);
    }
}


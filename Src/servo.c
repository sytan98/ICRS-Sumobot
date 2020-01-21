//
// Created by tianyilim on 1/21/20.
//

#include "servo.h"

/* How to define this in STM32CubeMX:
 * Because we dont have enough pins on the current STM32, i just made
 * this with another timer on a separate config file.
 *
 * However, it should work if configured with the specific instructions if configured correctly:
 *
 * >TIM3
 * >Clock Source: Internal Clock
 * Channel 1 PWM Generation CH1
 * Channel 2 PWM Generation CH2
 * Prescaler 128
 * Counter Period 1225
 *
 * Should give a roughly 50Hz waveform. The following functions should be a drop-in replacement.
 * CH1 is meant to be for "Servo 1", however it is defined.
 * CH2 is for "Servo 2"
 * servoWrite also will write the same angle to both servos if the argument for servo is not 1 or 2.
 */

void servo_init(){
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void servoWrite(int servo, float angle){
    // Angle from 0 to 180
    // 0: 1/20 duty cycle
    // 180: 2/20 duty cycle
    float proportion = (angle/180) + 1;
    int time =  1225/20*proportion;

    switch(servo){
        case 1:
            htim3.Instance->CCR1 = time;
            break;
        case 2:
            htim3.Instance->CCR2 = time;
            break;
        default:
            htim3.Instance->CCR1 = time;
            htim3.Instance->CCR2 = time;
    }
}
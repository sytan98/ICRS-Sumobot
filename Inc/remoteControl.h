//
// Created by jqp on 1/30/20.
//

#ifndef ICRS_SUMOBOT_REMOTECONTROL_H
#define ICRS_SUMOBOT_REMOTECONTROL_H

#include <stdint.h>
#include <stdio.h>
#include "tim.h"

#define RIGHT_KNOB_MAX 1805
#define RIGHT_KNOB_MIN 896
#define RIGHT_TOGGLE_MAX 1711
#define RIGHT_TOGGLE_MIN 1024
#define LEFT_TOGGLE_MAX 1646
#define LEFT_TOGGLE_MIN 1056

void remoteControl_init();
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
int get_RIGHT_KNOB();
int get_LEFT_TOGGLE();
int get_RIGHT_TOGGLE();
int check_right_knob_online();

#endif //ICRS_SUMOBOT_REMOTECONTROL_H
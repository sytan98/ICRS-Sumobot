//
// Created by tansi on 16/1/2020.
//

#ifndef ICRS_SUMOBOT_TIM_H
#define ICRS_SUMOBOT_TIM_H

#define DWT_DELAY_NEWBIE 0
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

void DWT_Init(void);
void delayMicroseconds(uint32_t us);
void error(int errorCode);
void print_f(char msg[]);

#endif //ICRS_SUMOBOT_TIM_H

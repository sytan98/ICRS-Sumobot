//
// Created by tansi on 16/1/2020.
//

#ifndef ICRS_SUMOBOT_TIM_H
#define ICRS_SUMOBOT_TIM_H


#define DWT_DELAY_NEWBIE 0
#include <stdint.h>

void DWT_Init(void);
void delayMicroseconds(uint32_t us);

#endif //ICRS_SUMOBOT_TIM_H

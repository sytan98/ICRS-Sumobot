//
// Created by tansi on 16/1/2020.
//

#ifndef ICRS_SUMOBOT_OPTICALFLOW_H
#define ICRS_SUMOBOT_OPTICALFLOW_H

#include <stdint.h>
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "delayMicrosec.h"

// Define Functions:

uint8_t initPMW3901(void);
void readMotionCount(int16_t *deltaX, int16_t *deltaY);
void initRegisters(void);
void registerWrite(uint8_t reg, uint8_t value);
uint8_t registerRead(uint8_t reg);


#endif //ICRS_SUMOBOT_OPTICALFLOW_H

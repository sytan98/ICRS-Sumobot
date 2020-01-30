//
// Created by tansi on 30/1/2020.
//

#ifndef ICRS_SUMOBOT_UARTLINK_H
#define ICRS_SUMOBOT_UARTLINK_H


#include "main.h"
#include <stdio.h>

void pollUART(UART_HandleTypeDef *huart, uint8_t *data);
void parsePacket(uint8_t *data,int32_t *power, int16_t *heading, int16_t *deltaX, int16_t *deltaY, int16_t *tof1, int16_t *tof2);

#endif //ICRS_SUMOBOT_UARTLINK_H

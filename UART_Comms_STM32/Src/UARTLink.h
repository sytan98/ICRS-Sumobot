#ifndef UART_LINK_H
#define UART_LINK_H

#include "main.h"

void pollUART(UART_HandleTypeDef *huart, uint8_t *data);
void parsePacket(uint8_t *data,int32_t *power, int16_t *heading, int16_t *deltaX, int16_t *deltaY, int16_t *tof1, int16_t *tof2);

#endif
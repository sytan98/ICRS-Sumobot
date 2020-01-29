#ifndef UART_LINK_H
#define UART_LINK_H

#include "main.h"

void pollUART(UART_HandleTypeDef *huart, uint8_t *data);

#endif
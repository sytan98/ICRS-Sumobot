#include "UARTLink.h"

void pollUART(UART_HandleTypeDef *huart, uint8_t *data)	{
	uint8_t request[1]={'0'};
	HAL_UART_Transmit(huart,request,1,1);
	HAL_UART_Receive(huart,data,sizeof(data),(int)(((sizeof(data)/4800)*1000)+2));
}
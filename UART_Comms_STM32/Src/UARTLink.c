#include "UARTLink.h"

void pollUART(UART_HandleTypeDef *huart, uint8_t *data)	{
	uint8_t request[1]={'0'};
	HAL_UART_Transmit(huart,request,1,1);
	HAL_UART_Receive(huart,data,sizeof(data),(int)(((sizeof(data)/4800)*1000)+2));
}

void parsePacket(uint8_t *packet,int32_t *power, int16_t *heading, int16_t *deltaX, int16_t *deltaY, int16_t *tof1, int16_t *tof2)	{
	*power=(packet[0]<<24)+(packet[1]<<16)+(packet[2]<<8)+packet[3];
	*heading=(packet[4]<<8)+packet[5];
	*deltaX=(packet[6]<<8)+packet[7];
	*deltaY=(packet[8]<<8)+packet[9];
	*tof1=(packet[10]<<8)+packet[11];
	*tof2=(packet[12]<<8)+packet[13];
}
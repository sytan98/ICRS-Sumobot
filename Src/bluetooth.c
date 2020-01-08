#include "bluetooth.h"

void checkStart(UART_HandleTypeDef *huart){   
    char _out[8] = "WhoisJoe?";
    HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out),  0xFFFF);
    char newline[2] = "\r\n";
    HAL_UART_Transmit(huart, (uint8_t *) newline, 2,  0xFFFF);

    for(;;){
        char in[5];
        HAL_UART_Receive(&huart2, (uint8_t *)in, 5, 1000);
        if (in == "start"){
            break
        }
    }
}
//import this file into stm32f4xx_it.c
//Use this function within the function "void EXTI15_10_IRQHandler(void)"

#ifndef infrared_h
#define infrared_h

#include "distance.h"
#include "motor.h"
#include "usart.h"

void lineDetected(int n);

#endif
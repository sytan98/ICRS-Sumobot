//import this file into stm32f4xx_it.c
//Use this function within the function "void EXTI15_10_IRQHandler(void)"

#ifndef infrared_h
#define infrared_h

#include "distance.h"
#include "motor.h"
//#include "stm32f4xx_hal_gpio.h"
//void linedetected(uint32_t GPIO_Pin)

void linedetected(int n){
    if (get_distance(n)<10){
        move_forward();
    } else {
        move_backward();
    }
}

#endif
#ifndef distance_h
#define distance_h
#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "tim.h"
#include "usart.h"

void timer_init(void);

void delay(unsigned int tick);

float getDistance(GPIO_TypeDef* Trig_Port , uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port , uint32_t Echo_Pin);

int getEnemy();

#endif

#ifndef distance_h
#define distance_h
#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "tim.h"

struct us_sensor{
  int name;
  float distance;
};

void delay (float us);

float getDistance(GPIO_TypeDef* Trig_Port , uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port , uint32_t Echo_Pin);

us_sensor getClosestEnemies();

#endif

#ifndef distance_h
#define distance_h
#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "tim.h"

struct us_sensor{
  int name;
  float distance;
  GPIO_TypeDef* Trig_Port;
  uint32_t Trig_Pin;
  GPIO_TypeDef* Echo_Port;
  uint32_t Echo_Pin;
};

void timer_init(void);

void delay(unsigned int tick);

us_sensor createSensor(us_sensor sensor, int name, GPIO_TypeDef* Trig_Port, uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port, uint32_t Echo_Pin);

float getDistance(us_sensor sensor);

us_sensor getClosestEnemies();

#endif

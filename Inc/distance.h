#ifndef distance_h
#define distance_h

#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "utils.h"
#include "main.h"
#define MAX_DISTANCE_IN_CM 200

struct us_sensor{
    int name;
    float distance;
    GPIO_TypeDef* Trig_Port;
    uint32_t Trig_Pin;
    GPIO_TypeDef* Echo_Port;
    uint32_t Echo_Pin;
};

float getDistance(int sensorChoose);

struct us_sensor getClosestEnemies();

#endif

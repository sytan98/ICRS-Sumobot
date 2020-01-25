#ifndef distance_h
#define distance_h

#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "utils.h"

struct us_sensor{
    int name;
    float distance;
    GPIO_TypeDef* Trig_Port;
    uint32_t Trig_Pin;
    GPIO_TypeDef* Echo_Port;
    uint32_t Echo_Pin;
};

extern struct us_sensor ultrasoundsensor1;

extern struct us_sensor ultrasoundsensor2;

extern struct us_sensor ultrasoundsensor3;

extern struct us_sensor ultrasoundsensor4;

struct us_sensor createSensor(int name, GPIO_TypeDef* Trig_Port, uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port, uint32_t Echo_Pin);

float getDistance(struct us_sensor sensor);

struct us_sensor getClosestEnemies();

#endif

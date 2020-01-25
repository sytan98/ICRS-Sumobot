//
// Created by tansi on 16/1/2020.
//

#include "distance.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float cachedDistance = 1000.0f;

extern struct us_sensor ultrasoundsensor1 = {00, 0.0,
                                             ultrasound_trigger_GPIO_Port,
                                             ultrasound_trigger_Pin,
                                             ultrasound1_echo_GPIO_Port,
                                             ultrasound1_echo_Pin};

extern struct us_sensor ultrasoundsensor2 = {00, 0.0,
                                             ultrasound_trigger_GPIO_Port,
                                             ultrasound_trigger_Pin,
                                             ultrasound2_echo_GPIO_Port,
                                             ultrasound2_echo_Pin};

extern struct us_sensor ultrasoundsensor3 = {00, 0.0,
                                             ultrasound_trigger_GPIO_Port,
                                             ultrasound_trigger_Pin,
                                             ultrasound3_echo_GPIO_Port,
                                             ultrasound3_echo_Pin};

extern struct us_sensor ultrasoundsensor4 = {00, 0.0,
                                             ultrasound_trigger_GPIO_Port,
                                             ultrasound_trigger_Pin,
                                             ultrasound4_echo_GPIO_Port,
                                             ultrasound4_echo_Pin};

struct us_sensor createSensor(int name, GPIO_TypeDef* Trig_Port, uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port, uint32_t Echo_Pin){
    struct us_sensor sensor = {name, 0, Trig_Port, Trig_Pin, Echo_Port, Echo_Pin};
    return sensor;
}

float getDistance(struct us_sensor sensor){

    float local_time=0;

    // Reset pin
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin LOW
    delayMicroseconds(2);  // wait for 2 us

    // Send trigger ultrasound wave
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
    delayMicroseconds(10);  // wait for 10 us
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    // Read the time for which the pin is high
    while (!(HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin)));  // wait for the ECHO pin to go high

    //TODO: what if there is no echo because nothing is detected
    while (HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin))    // while the pin is high
    {
        local_time++;   // measure time for which the pin is high
        delayMicroseconds(1);
    }

    cachedDistance = (local_time * .0343)/2 * 20;

    return cachedDistance;
}

struct us_sensor getClosestEnemies(){
    float sensor[8];
    const int INT_MAX = 10000;

    sensor[0] = getDistance(ultrasoundsensor1);
    sensor[1] = getDistance(ultrasoundsensor2);
    sensor[2] = getDistance(ultrasoundsensor3);
    sensor[3] = getDistance(ultrasoundsensor4);

    int dist1 = INT_MAX;
    int dist2 = INT_MAX;
    int sensor1 = 0;
    int sensor2 = 0;

    // TODO: what if 2 smallest distance sensors are not next to each other
    for(int i=0; i<4; i++){
        if(sensor[i]<dist1){
            dist2 = dist1;
            sensor2 = sensor1;
            dist1 = sensor[i];
            sensor1 = i+1;
        }
        else if(sensor[i] < dist2 && sensor[i] > dist1){
            dist2 = sensor[i];
            sensor2 = i+1;
        }
            // same value of distance
        else if(sensor[i] < dist2 && sensor[i] == dist1){
            dist2 = sensor[i];
            sensor2 = i+1;
        }
    }

    int final_name;
    // if nothing is detected
    if(dist1 == dist2 && dist1 == 0){
        final_name = 0;
    }
        //reorganise the order of two sensors if they are not in the correct order
    else if (sensor2 < sensor1){
        int tmp = sensor2;
        sensor2 = sensor1;
        sensor1 = tmp;

//		final_name = sensor1 * 10 + sensor2;
        final_name = sensor2;
    }
    else {
//		final_name = sensor1 * 10 + sensor2;
        final_name = sensor1;
    }

    struct us_sensor result = {final_name, MIN(dist1, dist2), NULL, 0, NULL, 0};

    return result;
}

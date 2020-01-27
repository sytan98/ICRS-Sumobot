//
// Created by tansi on 16/1/2020.
//

#include "distance.h"

struct us_sensor ultrasoundsensor1 = {00, -1,
                                      ultrasound_trigger_GPIO_Port,
                                      ultrasound_trigger_Pin,
                                      ultrasound1_echo_GPIO_Port,
                                      ultrasound1_echo_Pin};

struct us_sensor ultrasoundsensor2 = {00, -1,
                                      ultrasound_trigger_GPIO_Port,
                                      ultrasound_trigger_Pin,
                                      ultrasound2_echo_GPIO_Port,
                                      ultrasound2_echo_Pin};

struct us_sensor ultrasoundsensor3 = {00, -1,
                                      ultrasound_trigger_GPIO_Port,
                                      ultrasound_trigger_Pin,
                                      ultrasound3_echo_GPIO_Port,
                                      ultrasound3_echo_Pin};

struct us_sensor ultrasoundsensor4 = {00, -1,
                                      ultrasound_trigger_GPIO_Port,
                                      ultrasound_trigger_Pin,
                                      ultrasound4_echo_GPIO_Port,
                                      ultrasound4_echo_Pin};

// Used to check for timeout, notice this is reverse math to calculate dist
static const int LOCAL_TIME_MAX = MAX_DISTANCE_IN_CM * 10 / 3 * 2 / 0.343;

float getDistance(int ultrasoundChoose) {
    /* Returns distances in cm
     * Error distance values:
     * -1 : Invalid ultrasoundChoose variable entered (Must be from 1-4)
     * -2 : Error in initialising trigger/echo sequence
     * -3 : Distance returned more than MAX_DISTANCE_IN_CM
     */

    float cachedDistance;
    struct us_sensor sensor;
    switch (ultrasoundChoose) {
        case 1 :
            sensor = ultrasoundsensor1;
            break;
        case 2 :
            sensor = ultrasoundsensor2;
            break;
        case 3 :
            sensor = ultrasoundsensor3;
            break;
        case 4 :
            sensor = ultrasoundsensor4;
            break;
        default :
            return -1;
    }

    int local_time = 0;

    // Reset pin
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin,
                      GPIO_PIN_RESET);  // pull the TRIG pin LOW
    delayMicroseconds(2);  // wait for 2 us

    // Send trigger ultrasound wave
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin,
                      GPIO_PIN_SET);  // pull the TRIG pin HIGH
    delayMicroseconds(10);  // wait for 10 us
    HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin,
                      GPIO_PIN_RESET);  // pull the TRIG pin low

    // Read the time for which the pin is high
    // Wait for the pin to go high, if it doesn't within 1ms, skip measurement
    int count = 0;
    while (!(HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin))) {
        if (count > 1000) {
            return -2;
        }
        delayMicroseconds(1);
        count++;
    }

    // While pin high, start timer. Also, check for timeout condition
    while (HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin)) {
        if (local_time > LOCAL_TIME_MAX) {
            return -3;
        }

        local_time++;   // measure time for which the pin is high
        delayMicroseconds(1);
    }

    cachedDistance = (float) (local_time * .0343) / 2 * 3;
    return cachedDistance;
}

struct us_sensor getClosestEnemies() {
    float sensor[4];

    sensor[0] = getDistance(1);
    sensor[1] = getDistance(2);
    sensor[2] = getDistance(3);
    sensor[3] = getDistance(4);

    int min_dist = MAX_DISTANCE_IN_CM * 10;
    int min_sensor = 0;

    // Loops through to find closest enemy
    for (int i=0; i<4; i++) {
        if (sensor[i] < min_dist) {
            min_dist = sensor[i];
            min_sensor = i + 1;
        }
    }

    struct us_sensor result = {min_sensor, min_dist, NULL, 0, NULL, 0};
    return result;
}

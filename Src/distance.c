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

// Used to check for timeout, notice this is reverse math to calculate dist
static const int LOCAL_TIME_MAX = MAX_DISTANCE_IN_CM * 10 / 3 * 2 / 0.343;

float getDistance(int sensorChoose) {
    /* Returns distances in cm
     * sensorChoose values:
     * 1 : Ultrasound 1 (Front)
     * 2 : Ultrasound 2 (Right)
     * 3 : Ultrasound 3 (Left)
     * 4 : TOF 1 (Front left)
     * 5 : TOF 2 (Front right)
     *
     * Error distance values:
     * -1 : Invalid ultrasoundChoose variable entered (Must be from 1-4)
     * -2 : Error in initialising trigger/echo sequence
     * -3 : Distance returned more than MAX_DISTANCE_IN_CM
     */

    float cachedDistance;
    struct us_sensor sensor;
    switch (sensorChoose) {
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
            return getTOF1();
        case 5:
            return getTOF2();
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
        if (count > 10000) {
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
    int min_dist = MAX_DISTANCE_IN_CM * 10;
    int min_sensor = 0;
    int tof1 = getTOF1();
    int tof2 = getTOF2();

    // Prioritises TOF data over ultrasound sensors
    if (tof1 < MAX_DISTANCE_IN_CM && tof2 < MAX_DISTANCE_IN_CM) {
        min_dist = tof1;
        min_sensor = 1;
    } else if (tof1 < MAX_DISTANCE_IN_CM) {
        min_dist = tof1;
        min_sensor = 4;
    } else if (tof2 < MAX_DISTANCE_IN_CM) {
        min_dist = tof2;
        min_sensor = 5;
    }
    // If we didn't find any TOF data, then look at ultrasound data
    else {
        float sensor[3];

        sensor[0] = getDistance(1);
        sensor[1] = getDistance(2);
        sensor[2] = getDistance(3);

        // Loops through to find closest enemy
        for (int i = 0; i < 3; i++) {
            if (sensor[i] < min_dist) {
                min_dist = sensor[i];
                min_sensor = i + 1;
            }
        }
    }

    struct us_sensor result = {min_sensor, min_dist,
                               NULL, 0, NULL, 0};
    return result;
}

#include "distance.h"

void delay (float us)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim1))<us);
}

float cachedDistance = 1000.0f;

// TODO: use pointers or just create in main
us_sensor createSensor(us_sensor sensor, int name, GPIO_TypeDef* Trig_Port, uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port, uint32_t Echo_Pin){
	sensor = {name, 0, Trig_Port, Trig_Pin, Echo_Port, Echo_Pin};
	return sensor;
}

float getDistance(us_sensor sensor){
    // // don't try to update more quickly than the delay... in the meantime, return a cached value.
    // if(millis() - lastUpdated < ultrasonicDelayMs)
    //     return cachedDistance;

    float local_time=0;
	HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin LOW
	delay(2);  // wait for 2 us


	HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(sensor.Trig_Port, sensor.Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

	// read the time for which the pin is high

	while (!(HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin)));  // wait for the ECHO pin to go high

	//TODO: what if there is no echo because nothing is detected
	while (HAL_GPIO_ReadPin(sensor.Echo_Port, sensor.Echo_Pin))    // while the pin is high
	 {
		local_time++;   // measure time for which the pin is high
		delay (1);
	 }

    cachedDistance = (local_time * .0343)/2;

    // lastUpdated = millis();
    return cachedDistance;

		// return the same sensor struct with a distance value?
		// sensor.distance = cachedDistance;
		// return sensor;
}

us_sensor getClosestEnemies(){
	float sensor[8];

	sensor[0]= getDistance(sensor1);
	sensor[1]= getDistance(sensor2);
	sensor[2]= getDistance(sensor3);
	sensor[3]= getDistance(sensor4);
	sensor[4]= getDistance(sensor5);
	sensor[5]= getDistance(sensor6);
	sensor[6]= getDistance(sensor7);
	sensor[7]= getDistance(sensor8);

	int dist1 = INT_MAX;
	int dist2 = INT_MAX;
	int sensor1 = 0;
	int sensor2 = 0;

	// TODO: what if 2 smallest distance sensors are not next to each other
	for(int i=0; i<8; i++){
		if(sensor[i]<dist1){
			dist2 = dist1;
			sensor2 = sensor1;
			dist1 = sensor[i];
			sensor1 = i;
		}
		else if(sensor[i] < dist2 && sensor[i] > dist1){
			dist2 = sensor[i];
			sensor2 = i;
		}
		// same value of distance
		else if(sensor[i] < dist2 && sensor[i] = dist1){
			dist2 = sensor[i];
			sensor2 = i;
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

		final_name = sensor1*10 + sensor2;
	}
	else {
		final_name = sensor1*10 + sensor2;
	}

	us_sensor result = {final_name, min(dist1, dist2), nullptr, 0, nullptr, 0};

	return result;
}

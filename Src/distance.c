#include "distance.h"

void delay (float us)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim1))<us);
}

float cachedDistance = 1000.0f;

float getDistance(GPIO_TypeDef* Trig_Port , uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port , uint32_t Echo_Pin){
    // // don't try to update more quickly than the delay... in the meantime, return a cached value.
    // if(millis() - lastUpdated < ultrasonicDelayMs)
    //     return cachedDistance;

    float local_time=0;
	HAL_GPIO_WritePin(Trig_Port, Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin LOW
	delay(2);  // wait for 2 us


	HAL_GPIO_WritePin(Trig_Port, Trig_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(Trig_Port, Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

	// read the time for which the pin is high

	while (!(HAL_GPIO_ReadPin(Echo_Port, Echo_Pin)));  // wait for the ECHO pin to go high
	while (HAL_GPIO_ReadPin(Echo_Port, Echo_Pin))    // while the pin is high
	 {
		local_time++;   // measure time for which the pin is high
		delay (1);
	 }

    cachedDistance = (local_time * .0343)/2;

    // lastUpdated = millis();
    return cachedDistance;
}

int getEnemy(){
	float sensor[8];

	for(int i=0; i<8; i++){
		sensor[i]= getDistance(Trig_Port1, Trig_Pin1, Echo_Port1, Echo_Pin1);

	}
	// TODO: for loop may not be used here depending on how ports are named

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
		else if (sensor[i] < dist2 && sensor[i] > dist1){
			dist2 = sensor[i];
			sensor2 = i;
		}
	}

	if(sensor2 < sensor1){
		int tmp = sensor2;
		sensor2 = sensor1;
		sensor1 = tmp;
	}

	int final = sensor1*10 + sensor2;
	return final;
}

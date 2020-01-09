#include "distance.h"


volatile unsigned int *DWT_CYCCNT = (volatile unsigned int *)0xE0001004; //address of the register
volatile unsigned int *DWT_CONTROL = (volatile unsigned int *)0xE0001000; //address of the register
volatile unsigned int *SCB_DEMCR = (volatile unsigned int *)0xE000EDFC; //address of the register

void timer_init(void){
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0; // reset the counter
    *DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter
}

void delay(unsigned int tick){
    // Compare current time with start time to see if delay period has ended.
    unsigned int start, current;
    start = *DWT_CYCCNT;

    do {
        current = *DWT_CYCCNT;
    }
    while((current - start) < tick * 10);
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

	while (!(HAL_GPIO_ReadPin(Echo_Port, Echo_Pin))) {
	}  // wait for the ECHO pin to go high
	while ((HAL_GPIO_ReadPin(Echo_Port, Echo_Pin)))    // while the pin is high
	 {
		local_time++;   // measure time for which the pin is high
         delay(1);
	 }

    cachedDistance = (local_time * .0343)/2 * 3;

    // lastUpdated = millis();
    return cachedDistance;
}

int getEnemy(GPIO_TypeDef* Trig_Port , uint32_t Trig_Pin, GPIO_TypeDef* Echo_Port , uint32_t Echo_Pin){
    const int INT_MAX = 100;
	float sensor[8];

	for(int i=0; i<8; i++){
		sensor[i]= getDistance(Trig_Port, Trig_Pin, Echo_Port, Echo_Pin);

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

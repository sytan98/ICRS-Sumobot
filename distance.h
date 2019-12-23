#ifndef distance_h
#define distance_h
#include <stdio.h>
#include <stdint.h>

void delay (float us)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim1))<us);
}

float cachedDistance = 1000.0f;

float getDistance(GPIO_TypeDef* Trig_Port , uint32_t Trig_Pin){
    // // don't try to update more quickly than the delay... in the meantime, return a cached value.
    // if(millis() - lastUpdated < ultrasonicDelayMs)
    //     return cachedDistance;

    float local_time=0;
	HAL_GPIO_WritePin(Trig_Port, Trig_Pin, GPIO_PIN_RESET);  // pull the TRIG pin HIGH
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

#endif



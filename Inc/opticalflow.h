#ifndef opticalflow_h
#define opticalflow_h

#include <stdint.h>
#include "main.h"

// Variables
SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart2;

// Timer Registers for delayMicroseconds
volatile unsigned int *DWT_CYCCNT = (volatile unsigned int *)0xE0001004; //address of the register
volatile unsigned int *DWT_CONTROL = (volatile unsigned int *)0xE0001000; //address of the register
volatile unsigned int *SCB_DEMCR = (volatile unsigned int *)0xE000EDFC; //address of the register

// Define Functions:
void delayMicroseconds(unsigned int tick);
uint8_t initPMW3901(void);
void readMotionCount(int16_t *deltaX, int16_t *deltaY);
void initRegisters(void);
void registerWrite(uint8_t reg, uint8_t value);
uint8_t registerRead(uint8_t reg);

// Low level register access
void registerWrite(uint8_t reg, uint8_t value) {
  reg |= 0x80u;

	// Pull CS low to initiate
	HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_RESET);

  delayMicroseconds(50);

	HAL_SPI_Transmit(&hspi1, &reg, 1, 5);
	HAL_SPI_Transmit(&hspi1, &value, 1, 5);

  delayMicroseconds(50);

  HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_SET);

  delayMicroseconds(200);
}

uint8_t registerRead(uint8_t reg) {
  reg &= ~0x80u;
	uint8_t value;

  HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_RESET);

  delayMicroseconds(50);

  HAL_SPI_Transmit(&hspi1, &reg, 1, 5);

  delayMicroseconds(50);

  HAL_SPI_Receive(&hspi1, &value, 1, 5);

  delayMicroseconds(200);

  HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_SET);

  delayMicroseconds(200);

  return value;
}



// Reads the motion of the optical flow sensor.
// Takes 2 pointers as args and returns the modified values.
void readMotionCount(int16_t *deltaX, int16_t *deltaY){
	registerRead(0x02);
  *deltaX = ((int16_t)registerRead(0x04) << 8) | registerRead(0x03);
  *deltaY = ((int16_t)registerRead(0x06) << 8) | registerRead(0x05);
}



// Performance optimisation registers (propietary)
// Takes place at startup.
void initRegisters() {
  registerWrite(0x7F, 0x00);
  registerWrite(0x61, 0xAD);
  registerWrite(0x7F, 0x03);
  registerWrite(0x40, 0x00);
  registerWrite(0x7F, 0x05);

  registerWrite(0x41, 0xB3);
  registerWrite(0x43, 0xF1);
  registerWrite(0x45, 0x14);
  registerWrite(0x5B, 0x32);
  registerWrite(0x5F, 0x34);
  registerWrite(0x7B, 0x08);
  registerWrite(0x7F, 0x06);
  registerWrite(0x44, 0x1B);
  registerWrite(0x40, 0xBF);
  registerWrite(0x4E, 0x3F);
  registerWrite(0x7F, 0x08);
  registerWrite(0x65, 0x20);
  registerWrite(0x6A, 0x18);

  registerWrite(0x7F, 0x09);
  registerWrite(0x4F, 0xAF);
  registerWrite(0x5F, 0x40);
  registerWrite(0x48, 0x80);
  registerWrite(0x49, 0x80);

  registerWrite(0x57, 0x77);
  registerWrite(0x60, 0x78);
  registerWrite(0x61, 0x78);
  registerWrite(0x62, 0x08);
  registerWrite(0x63, 0x50);
  registerWrite(0x7F, 0x0A);
  registerWrite(0x45, 0x60);
  registerWrite(0x7F, 0x00);
  registerWrite(0x4D, 0x11);

  registerWrite(0x55, 0x80);
  registerWrite(0x74, 0x1F);
  registerWrite(0x75, 0x1F);
  registerWrite(0x4A, 0x78);
  registerWrite(0x4B, 0x78);

  registerWrite(0x44, 0x08);
  registerWrite(0x45, 0x50);
  registerWrite(0x64, 0xFF);
  registerWrite(0x65, 0x1F);
  registerWrite(0x7F, 0x14);
  registerWrite(0x65, 0x60);
  registerWrite(0x66, 0x08);
  registerWrite(0x63, 0x78);
  registerWrite(0x7F, 0x15);
  registerWrite(0x48, 0x58);
  registerWrite(0x7F, 0x07);
  registerWrite(0x41, 0x0D);
  registerWrite(0x43, 0x14);
  registerWrite(0x4B, 0x0E);
  registerWrite(0x45, 0x0F);
  registerWrite(0x44, 0x42);
  registerWrite(0x4C, 0x80);
  registerWrite(0x7F, 0x10);
  registerWrite(0x5B, 0x02);
  registerWrite(0x7F, 0x07);
  registerWrite(0x40, 0x41);
  registerWrite(0x70, 0x00);

  HAL_Delay(10);

  registerWrite(0x32, 0x44);
  registerWrite(0x7F, 0x07);
  registerWrite(0x40, 0x40);
  registerWrite(0x7F, 0x06);
  registerWrite(0x62, 0xf0);
  registerWrite(0x63, 0x00);
  registerWrite(0x7F, 0x0D);
  registerWrite(0x48, 0xC0);
  registerWrite(0x6F, 0xd5);
  registerWrite(0x7F, 0x00);

  registerWrite(0x5B, 0xa0);
  registerWrite(0x4E, 0xA8);
  registerWrite(0x5A, 0x50);
  registerWrite(0x40, 0x80);

	HAL_Delay(100);

	// Enable LED pulsing
	registerWrite(0x7F, 0x14);
  registerWrite(0x6F, 0x1C);
  registerWrite(0x7F, 0x00);

}


// Initializes the sensor.
// Returns true if success and false if failure.
uint8_t initPMW3901(){
	// Wrangle around in STM32 registers to enable delayMicroseconds()
	*SCB_DEMCR = *SCB_DEMCR | 0x01000000;
	*DWT_CYCCNT = 0; // reset the counter
	*DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter

  // Make sure the SPI bus is reset
	HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(CS_OF_GPIO_Port, CS_OF_Pin, GPIO_PIN_SET);
	HAL_Delay(1);

  // Power on reset
  registerWrite(0x3A, 0x5A);
  HAL_Delay(5);

  // Test the SPI communication, checking chipId and inverse chipId
  uint8_t chipId = registerRead(0x00);
  uint8_t dIpihc = registerRead(0x5F);

  if (chipId != 0x49 && dIpihc != 0xB8) return 0;

  // Reading the motion registers one time
  registerRead(0x02);
  registerRead(0x03);
  registerRead(0x04);
  registerRead(0x05);
  registerRead(0x06);
  HAL_Delay(1);

	// Initializes the registers in the propietary way.
  initRegisters();

  return 1;
}

 
// HAL_Delay is in mills() so we have to make our own
// Microsecond delay function.
void delayMicroseconds(unsigned int tick){
	// Compare current time with start time to see if delay period has ended.
	unsigned int start, current;
	start = *DWT_CYCCNT;
	
	do {
		current = *DWT_CYCCNT; 
	} 
	while((current - start) < tick);
 
}


 #endif
 

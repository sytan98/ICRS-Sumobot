#ifndef i2c_primitives_h
#define i2c_primitives_h

// Defines the read/write functions to i2c registers.
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

const int transactionTimeout = 5;
// Parameter to pass into the HAL function

// Declare components
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

// Function Declarations
void writeReg(uint8_t address, uint8_t reg, uint8_t value);
void writeReg16Bit(uint8_t address, uint8_t reg, uint16_t value);
void writeReg16Bit(uint8_t address, uint8_t reg, uint16_t value);
uint8_t readReg(uint8_t address, uint8_t reg);
uint16_t readReg16Bit(uint8_t address, uint8_t reg);
uint32_t readReg32Bit(uint8_t address, uint8_t reg);

// Hardware interfacing (not 100% tested - use with caution!)
// Write an 8-bit register
void writeReg(uint8_t address, uint8_t reg, uint8_t value)
{
	address -= 1; // i2c WRITE address last bit is always 0, READ address last bit is always 1.
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;
	
	HAL_I2C_Master_Transmit(&hi2c1, address, data, 2, transactionTimeout);
  // last_status = Wire.endTransmission();
}

// Write a 16-bit register
void writeReg16Bit(uint8_t address, uint8_t reg, uint16_t value)
{
	address -= 1;
	// Change to WRITE address
	uint8_t data[3];
	data[0] = reg;
	data[1] = ( (value >> 8) & 0xFF );	// Value high byte
	data[2] = ( value       & 0xFF);		// Value low byte
	
	HAL_I2C_Master_Transmit(&hi2c1, address, data, 3, 2*transactionTimeout);
  // last_status = Wire.endTransmission();
}

// Write a 32-bit register
void writeReg32Bit(uint8_t address, uint8_t reg, uint32_t value)
{
	address -= 1;
	// Change to WRITE address
	uint8_t data[5];
	data[0] = reg;
	data[1] = ( (value >> 24) & 0xFF );	// Value high byte
	data[2] = ( (value >> 16) & 0xFF );
	data[3] = ( (value >> 8) & 0xFF );
	data[4] = ( value       & 0xFF);		// Value low byte
	
	HAL_I2C_Master_Transmit(&hi2c1, address, data, 5, 4*transactionTimeout);
  // last_status = Wire.endTransmission();
}

// Read an 8-bit register
uint8_t readReg(uint8_t address, uint8_t reg)
{
  uint8_t value;
	address -= 1;
	
	HAL_I2C_Master_Transmit(&hi2c1, address, &reg, 1, transactionTimeout);	// The address of the register to read
	HAL_I2C_Master_Receive(&hi2c1, address, &value, 1, transactionTimeout);	// Read data

  return value;
}

// Read a 16-bit register
uint16_t readReg16Bit(uint8_t address, uint8_t reg)
{
  uint16_t value;
	uint8_t data[2];
	
	HAL_I2C_Master_Transmit(&hi2c1, address-1, &reg, 1, 2*transactionTimeout);	// The address of the register to read
	HAL_I2C_Master_Receive(&hi2c1, address, data, 2, 2*transactionTimeout);	// Read data

  value  = data[1] << 8; // value high byte
  value |= data[0];      // value low byte

  return value;
}

// Read a 32-bit register
uint32_t readReg32Bit(uint8_t address, uint8_t reg)
{
  uint32_t value;
	uint8_t data[4];
	
	HAL_I2C_Master_Transmit(&hi2c1, address-1, &reg, 1, 4*transactionTimeout);	// The address of the register to read
	HAL_I2C_Master_Receive(&hi2c1, address, data, 4, 4*transactionTimeout);	// Read data

  value  = data[3] << 24; // value highest byte
  value |= data[2] << 16;
  value |= data[1] <<  8;
  value |= data[0];       // value lowest byte

  return value;
}

#endif

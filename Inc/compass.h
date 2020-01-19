#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "usart.h"
#include "i2c.h"

#ifndef COMPASS_LSM303_H
#define COMPASS_LSM303_H

struct mag_struct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

// Register addresses
enum regAddr {
    MAG_ADDR_READ = 0x3D,
    MAG_ADDR_WRITE = 0x3C,

    // Register Addresses for Magnetic Sensor
    // Config Registers (RW)

    CRA_REG_MAG = 0x00, // RW Temperature sensor on/off, data rate of sensor
    CRB_REG_MAG = 0x01, // RW Magnetic sensor gain
    MR_REG_MAG = 0x02,  // RW Sensor Mode Select

    // Data outputs (R)

    OUT_X_H_MAG = 0x03,
    OUT_X_LH_MAG = 0x04,    // X-axis magnetic field data as 2's complement
    OUT_Z_H_MAG = 0x05,
    OUT_Z_LH_MAG = 0x06,    // Z-axis magnetic field data as 2's complement
    OUT_Y_H_MAG = 0x07,
    OUT_Y_LH_MAG = 0x08,    // Y-axis magnetic field data as 2's complement

    SR_REG_MAG = 0x09,  // Check if new data is available

    // Register configurations
    // Data rate: Goes into CRA_REG_MAG

    MAG_RATE_0_7 = 0x00,    // Also disables the temperature sensor embedded inside.
    MAG_RATE_1_5 = 0x04,
    MAG_RATE_3_0 = 0x08,
    MAG_RATE_7_5 = 0x0C,
    MAG_RATE_15 = 0x10,
    MAG_RATE_30 = 0x14,
    MAG_RATE_75 = 0x18,
    MAG_RATE_220 = 0x1C,

    // Sensor gain: Goes into CRB_REG_MAG

    MAG_GAIN_1_3 = 0x20,
    MAG_GAIN_1_9 = 0x40,
    MAG_GAIN_2_5 = 0x60,
    MAG_GAIN_4_0 = 0x80,
    MAG_GAIN_4_7 = 0xA0,
    MAG_GAIN_5_6 = 0xC0,
    MAG_GAIN_8_1 = 0xE0,

    // Mode: goes into MR_REG_MAG

    MAG_CONTINUOUS = 0x00,
    MAG_SINGLE = 0x01,  // Of course when initialized we set the sensor to be in this mode.
    MAG_SLEEP = 0x02,

    // Sanity Checkers

    IRA_REG_MAG = 0x0A, // Read only reg that does not change.
    IRA_REG_SANITY = 0x48   // Perhaps useful upon reset.
};

// Function Prototypes

// Util functions
void error(int errorCode);
void print_f(char msg[]);

// Initialize Compass
void compass_init();
static void set_gain(uint8_t MAG_GAIN);
static void set_frequency(uint8_t MAG_RATE);
static void set_continuous_read(uint8_t MAG_MODE);

// Read values
struct mag_struct read_mag_values(I2C_HandleTypeDef *i2c);

#endif
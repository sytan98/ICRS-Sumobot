#include "compass.h"

// Util functions
void error(int errorCode) {
    /* Error codes:
     * 1 - Device is not ready
     * 2 - Fail sanity check of fixed register
     * 3 - Set gain fail
     * 4 - Set frequency fail
     * 5 - Set continuous read fail
     * 10 - Failure to ask for mag readings
     * 11 - Failure to receive mag readings
     */
    while (1) {
        u_int8_t errorMsg[12];
        sprintf(errorMsg, "error: %02d\r\n", errorCode);
        print_f(errorMsg);
        HAL_Delay(1000);
    }
}

void print_f(char msg[]) {
    HAL_UART_Transmit(&huart2, msg, strlen(msg), 1000);
}

// Initialize Compass
void compass_init() {
    print_f("\n\n\nInitialising compass..\n");
    HAL_Delay(500);
    uint8_t i2cRead[2];
    // Check if there is an i2c device at the chosen address.
    if (HAL_I2C_IsDeviceReady(&hi2c1, MAG_ADDR_READ, 10, 10) != HAL_OK) {
        error(1);        HAL_Delay(200);
    }

    // Sanity Check Read a fixed register
    print_f("\nInitialising sanity check...\n");
    HAL_Delay(500);
    i2cRead[0] = IRA_REG_MAG;
    i2cRead[1] = 0;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, &i2cRead[0], 1,
                            5);    // The address of the register to read
    HAL_I2C_Master_Receive(&hi2c1, MAG_ADDR_READ, &i2cRead[1], 1,
                           5);    // Read data

    if (i2cRead[1] != IRA_REG_SANITY) {
        error(2);
    } else {
        print_f("Sanity check success!\n");
        HAL_Delay(500);
    }

    // Configure settings
    set_gain(MAG_GAIN_1_3);
    set_frequency(MAG_RATE_75);
    set_continuous_read(MAG_CONTINUOUS);

    print_f("Compass init success!\n\n");
    HAL_Delay(2000);
}

static void set_gain(uint8_t MAG_GAIN) {
    print_f("\nSetting gain...\n");
    HAL_Delay(500);
    uint8_t i2cRead[2];

    // Write gain setting
    i2cRead[0] = CRB_REG_MAG;
    i2cRead[1] = MAG_GAIN;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, i2cRead, 2, 5);

    // Check gain setting
    i2cRead[1] = 0;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, &i2cRead[0], 1, 5);
    HAL_I2C_Master_Receive(&hi2c1, MAG_ADDR_READ, &i2cRead[1], 1, 5);

    if (i2cRead[1] != MAG_GAIN) {
        error(3);
    } else {
        print_f("Gain set success!\n");
    }
}

static void set_frequency(uint8_t MAG_RATE) {
    print_f("\nSetting frequency...\n");
    HAL_Delay(500);
    uint8_t i2cRead[2];
    // Write frequency settings
    i2cRead[0] = CRA_REG_MAG;
    i2cRead[1] = MAG_RATE;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, i2cRead, 2, 5);

    // Check frequency setting
    i2cRead[1] = 0;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, &i2cRead[0], 1, 5);
    HAL_I2C_Master_Receive(&hi2c1, MAG_ADDR_READ, &i2cRead[1], 1, 5);

    if (i2cRead[1] != MAG_RATE) {
        error(4);
    } else {
        print_f("Frequency set success!\n");
    }
}

static void set_continuous_read(uint8_t MAG_MODE) {
    uint8_t i2cRead[2];
    print_f("\nSetting continuous read...\n");
    HAL_Delay(500);
    // Write read settings
    i2cRead[0] = MR_REG_MAG;
    i2cRead[1] = MAG_MODE;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, i2cRead, 2, 5);

    // Check read settings
    i2cRead[1] = 0;
    HAL_I2C_Master_Transmit(&hi2c1, MAG_ADDR_WRITE, &i2cRead[0], 1, 5);
    HAL_I2C_Master_Receive(&hi2c1, MAG_ADDR_READ, &i2cRead[1], 1, 5);

    if (i2cRead[1] != MAG_MODE) {
        error(5);
    } else {
        print_f("Continuous read set success!\n");
    }
}

// Actual reading of values
struct mag_struct read_mag_values(I2C_HandleTypeDef *i2c) {
    // Since all magnetic registers X, Y, Z are in continuous addresses,
    // we only need to start reading from the first register
    uint8_t val[6];
    uint8_t reg = OUT_X_H_MAG;
    HAL_StatusTypeDef ret;

    // Ask for data at register reg
    ret = HAL_I2C_Master_Transmit(i2c, MAG_ADDR_WRITE, &reg, 1, 1000);
    if (ret != HAL_OK) {
        error(10);
    }

    // Read all six registers at once
    ret = HAL_I2C_Master_Receive(i2c, MAG_ADDR_WRITE, val, 6, 1000);
    if (ret != HAL_OK) {
        error(11);
    }

    // Some bitwise processing of low and high bytes
    uint8_t xVal = val[0] << 8 | val[1];
    uint8_t zVal = val[2] << 8 | val[3];
    uint8_t yVal = val[4] << 8 | val[5];

    struct mag_struct mag_readings = {xVal, yVal, zVal};
    return mag_readings;
}
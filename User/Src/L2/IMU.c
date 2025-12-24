#include "L2/IMU.h"
#include "L1/SPI_driver.h"

// #include <stdint.h>

uint8_t LSM_check_status(void)
{
    uint8_t whoami;
    whoami = LSM_read(0x0F, 1); // WHO_AM_I register address

    /*check important CTRL registers for XL and gyro*/
    // WIP
    return whoami;
}

void LSM_init(void)
{

    // /*Software reset of all CTRL registers*/
    // uint8_t CTRL3 = 0x12;
    // uint8_t CTRL3_data = 0x01;
    // LSM_write(CTRL3, CTRL3_data);

    /*initialize accelerometer*/

    uint8_t CTRL1 = 0x10;
    uint8_t CTRL1_data = 0x09;
    LSM_write(CTRL1, CTRL1_data);
}

void LSM_accel_raw_read(LSM_accel_raw_t *accel)
{
    // LSM_accel_raw_t accel_raw;
    //  uint8_t tx[7] = {0};
    //  uint8_t rx[7] = {0};

    // tx[0] = 0x28 | 0x80; // OUTX_L_A | READ

    // LSM_CS_LOW();
    // HAL_SPI_TransmitReceive(&hspi2, tx, rx, 7, HAL_MAX_DELAY);
    // LSM_CS_HIGH();
    LSM_read(0x28, 6);

    // accel->x = (int16_t)(rx[1] | (rx[2] << 8));
    // accel->y = (int16_t)(rx[3] | (rx[4] << 8));
    // accel->z = (int16_t)(rx[5] | (rx[6] << 8));
}

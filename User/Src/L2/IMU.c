#include "L2/IMU.h"
#include "L1/SPI_driver.h"
#include "L1/USART_driver.h"
#include "spi.h"
#include <memory.h>
#include <stdio.h>
#include <stm32h7xx_hal.h>

#define CTRL1 (uint8_t)0x10
#define CTRL3 (uint8_t)0x12

// #include <stdint.h>

void LSM_check_status(void)
{
    char buf[50];
    uint8_t whoami[2];
    LSM_read(0x0F, 1, whoami);
    sprintf(buf, "WHO_AM_I = 0x%02X\r\n", whoami[1]);
    send_host_message(buf);

    /*check important CTRL registers for XL and gyro*/
    // uint8_t check_CTRL3 = LSM_read(CTRL3, 1);
    uint8_t check_CTRL1[2];
    LSM_read(CTRL1, 1, check_CTRL1);

    // sprintf(buf, "CTRL3 = 0x%02X\r\n", check_CTRL3);
    // send_host_message(buf);
    sprintf(buf, "CTRL1 = 0x%02X\r\n", check_CTRL1[1]);
    send_host_message(buf);
}

void LSM_init(void)
{

    /*Software reset of all CTRL registers*/
    uint8_t CTRL3_data = 0x01;
    LSM_write(CTRL3, CTRL3_data);
    HAL_Delay(1000); // wait for reset to complete

    /*initialize accelerometer*/
    uint8_t CTRL1_data = 0x09;
    LSM_write(CTRL1, CTRL1_data);
}

void LSM_accel_raw_read(LSM_accel_raw_t *accel_raw)
{
    uint8_t rx[7] = {0};
    LSM_read(0x28, 6, rx);

    accel_raw->x = (int16_t)(rx[1] | (rx[2] << 8));
    accel_raw->y = (int16_t)(rx[3] | (rx[4] << 8));
    accel_raw->z = (int16_t)(rx[5] | (rx[6] << 8));

}

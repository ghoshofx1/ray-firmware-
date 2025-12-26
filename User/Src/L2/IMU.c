#include "L2/IMU.h"
#include "L1/SPI_driver.h"
#include "L1/USART_driver.h"
#include "spi.h"
#include <memory.h>
#include <stdio.h>
#include <stm32h7xx_hal.h>

#define CTRL1 (uint8_t)0x10
#define CTRL2 (uint8_t)0x11
#define CTRL3 (uint8_t)0x12
#define CTRL4 (uint8_t)0x13
#define CTRL5 (uint8_t)0x14
#define CTRL6 (uint8_t)0x15
#define CTRL7 (uint8_t)0x16
#define CTRL8 (uint8_t)0x17
#define CTRL9 (uint8_t)0x18
#define CTRL10 (uint8_t)0x19
// #include <stdint.h>

#define G 9.80665
#define ACC_SENSITIVITY_2G 0.061   // mg/LSB
#define GYRO_SENSITIVITY_125DPS 4.375 // mdps/LSB

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

    sprintf(buf, "CTRL1 = 0x%02X\r\n", check_CTRL1[1]);
    send_host_message(buf);

    uint8_t check_CTRL2[2];
    LSM_read(CTRL2, 1, check_CTRL2);
    sprintf(buf, "CTRL2 = 0x%02X\r\n", check_CTRL2[1]);
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

    /*initialize gyroscope*/
    uint8_t CTRL2_data = 0x09;
    LSM_write(CTRL2, CTRL2_data);
}

void LSM_accel_raw_read(LSM_accel_raw_t *accel_raw)
{
    uint8_t rx[7] = {0};
    LSM_read(0x28, 6, rx);

    accel_raw->x = (int16_t)(rx[1] | (rx[2] << 8));
    accel_raw->y = (int16_t)(rx[3] | (rx[4] << 8));
    accel_raw->z = (int16_t)(rx[5] | (rx[6] << 8));
}

void LSM_gyro_raw_read(LSM_gyro_raw_t *gyro_raw)
{
    uint8_t rx[7] = {0};
    LSM_read(0x22, 6, rx);

    gyro_raw->x = (int16_t)(rx[1] | (rx[2] << 8));
    gyro_raw->y = (int16_t)(rx[3] | (rx[4] << 8));
    gyro_raw->z = (int16_t)(rx[5] | (rx[6] << 8));

}

/* CHANGE THIS AS NEEDED - Accelerometer and gyroscope conversion functions for FSR = 2G and 125DPS */

float accel_mps2(int16_t raw) {
    return raw * ACC_SENSITIVITY_2G * G / 1000.0;
}

float gyro_dps(int16_t raw) {
    return raw * GYRO_SENSITIVITY_125DPS / 1000.0;
}

float gyro_rads(int16_t raw) {
    return gyro_dps(raw) * 3.14159265 / 180.0;
}


void LSM_convert(const LSM_accel_raw_t *accel_raw, const LSM_gyro_raw_t *gyro_raw, IMU_phys_t *phys)
{
    phys->ax = accel_mps2(accel_raw->x);
    phys->ay = accel_mps2(accel_raw->y);
    phys->az = accel_mps2(accel_raw->z);

    phys->gx = gyro_rads(gyro_raw->x);
    phys->gy = gyro_rads(gyro_raw->y);
    phys->gz = gyro_rads(gyro_raw->z);
}


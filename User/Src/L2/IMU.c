#include "L2/IMU.h"
#include "L1/SPI_driver.h"
#include "L1/USART_driver.h"
#include <stdio.h>
#include "spi.h"
#include <memory.h>


#define CTRL3 (uint8_t) 0x12
#define CTRL1 (uint8_t) 0x10


// #include <stdint.h>

uint8_t LSM_check_status(void)
{
    uint8_t whoami = LSM_read(0x0F, 1); // WHO_AM_I register address

    /*check important CTRL registers for XL and gyro*/
    //uint8_t check_CTRL3 = LSM_read(CTRL3, 1);
    uint8_t check_CTRL1 = LSM_read(CTRL1, 1);

    char buf[50];
    //sprintf(buf, "CTRL3 = 0x%02X\r\n", check_CTRL3);
    //send_host_message(buf); 
    sprintf(buf, "CTRL1 = 0x%02X\r\n", check_CTRL1);
    send_host_message(buf);

    return whoami;
}

void LSM_init(void)
{

    /*Software reset of all CTRL registers*/
    // uint8_t CTRL3_data = 0x01;
    // LSM_write(CTRL3, CTRL3_data);


    /*initialize accelerometer*/
    uint8_t CTRL1_data = 0x09;
    LSM_write(CTRL1, CTRL1_data);


}

void LSM_accel_raw_read(LSM_accel_raw_t *accel)
{
    // LSM_accel_raw_t accel_raw;
     uint8_t tx[7] = {0};
     uint8_t rx[7] = {0};

    tx[0] = 0x80|0x28; // READ OPERATION starting at reg 0x28
    memset(&tx[1], 0x00, 6);

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx, 7, HAL_MAX_DELAY);
    LSM_CS_HIGH();
    //LSM_read(0x28, 6);

    accel->x = (int16_t)(rx[1] | (rx[2] << 8));
    accel->y = (int16_t)(rx[3] | (rx[4] << 8));
    accel->z = (int16_t)(rx[5] | (rx[6] << 8));

    //print to host
    char buf[50];
    sprintf(buf, "AX: %d AY: %d AZ: %d\r\n", accel->x, accel->y, accel->z);
    send_host_message(buf);
}

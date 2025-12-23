// #include "main.h"
#include "sensors.h"
#include "spi.h"
#include <stdint.h>
#include "host_UART.h"


// typedef struct {
//     int16_t x;
//     int16_t y;
//     int16_t z;
// } lsm6dsv_accel_raw_t;


void LSM_write(uint8_t reg, uint8_t data)
{
    uint8_t tx[2];
    // uint8_t rx[2];

    tx[0] = 0x7F & reg; // WRITE OPERATION to reg 
    tx[1] = data;       // data byte

    LSM_CS_LOW();
    HAL_SPI_Transmit(&hspi2, tx, 2, HAL_MAX_DELAY);
    LSM_CS_HIGH();
}

uint8_t LSM_read(uint8_t reg, uint8_t bytes)
{

    uint8_t tx[bytes];
    uint8_t rx[bytes];

    tx[0] = 0x80 | reg; // READ OPERATION starting at reg

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx, bytes, HAL_MAX_DELAY);
    LSM_CS_HIGH();

    return rx[1]; 
}

// uint8_t LSM_check(void)
// {
//     uint8_t whoami;
//     whoami = LSM_read(0x0F); // WHO_AM_I register address
//     return whoami;
// }

void LSM_init(void) {
    uint8_t CTRL1 = 0x10;
    uint8_t CTRL1_data = 0x09;
    LSM_write(CTRL1, CTRL1_data);
}

void LSM_accel_raw_read(void) {
    // LSM_accel_raw_t accel; 
    uint8_t tx[7] = { 0 };
    uint8_t rx[7] = { 0 };

    tx[0] = 0x28 | 0x80;  // OUTX_L_A | READ

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx, 7, HAL_MAX_DELAY);
    LSM_CS_HIGH();

}




#include "L1/SPI_driver.h"
#include "spi.h"
#include <stdint.h>
#include "memory.h"


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


uint8_t LSM_read(uint8_t start_reg, uint8_t len)
{
    // uint8_t count = bytes;
    uint8_t tx[len + 1];
    uint8_t rx[len + 1];

    tx[0] = 0x80 | start_reg; // READ OPERATION starting at reg
    memset(&tx[1], 0x00, len);

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx, len + 1, HAL_MAX_DELAY);
    LSM_CS_HIGH();

    return rx[1];
}
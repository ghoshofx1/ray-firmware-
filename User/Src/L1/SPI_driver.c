#include "L1/SPI_driver.h"
#include "spi.h"
#include <stdint.h>
#include "memory.h"
#include "main.h"


/*SPI drivers for LSM6DSV16X IMU*/

#define LSM_CS_LOW() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_SET)

/*SPI drivers for MS5 Barometer*/

#define MS5_CS_LOW() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_RESET)
#define MS5_CS_HIGH() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_SET)

void LSM_write(uint8_t reg, uint8_t data)
{
    uint8_t tx[2];
   
    tx[0] = 0x7F & reg; // WRITE OPERATION to reg
    tx[1] = data;       // data byte

    LSM_CS_LOW();
    HAL_SPI_Transmit(&hspi2, tx, 2, HAL_MAX_DELAY);
    LSM_CS_HIGH();
}


void LSM_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer)
{
   
    uint8_t tx[len + 1];
  
    tx[0] = 0x80 | start_reg; // READ OPERATION starting at reg
    memset(&tx[1], 0x00, len); // fill rest with dummy bytes

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx_buffer, len + 1, HAL_MAX_DELAY);
    LSM_CS_HIGH();

}



void MS5_write(uint8_t data)
{
    MS5_CS_LOW();
    HAL_SPI_Transmit(&hspi6, &data, 1, HAL_MAX_DELAY);
    //HAL_Delay(1); // NOTE: THERE NEEDS TO BE A MINMUM 3-5ms DELAY FOR MS5_RESET COMMAND
    MS5_CS_HIGH();
}

void MS5_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer)
{   
    // uint8_t tx[len + 1];
    uint8_t tx[1 + len]; 
    tx[0] = start_reg; // starting at reg
    memset(&tx[1], 0x00, len); // fill rest with dummy bytes

    MS5_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi6, tx, rx_buffer, len + 1, HAL_MAX_DELAY);
    MS5_CS_HIGH();
}


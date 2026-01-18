#include "L1/SPI_driver.h"
#include "spi.h"
#include <stdint.h>
#include "memory.h"
#include "main.h"


/* Note which peripherals are on which SPI buses 
SPI2 - seen as "SPI" in schematic - has LSM6DSV, ADXL375, LIS2MD
Note that for SPI2 is currently in MODE 3 (CPOL=1, CPHA=1) --> change later
SPI6 - seen as "SPI2" in schematic - has E22900MM22S, ICM40609, CAM-M8Q-0 
Note that SPI6 is currently in MODE 0*/


/*SPI drivers for LSM6DSV16X IMU*/

#define LSM_CS_LOW() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_SET)

void LSM_write(uint8_t reg, uint8_t data)
{
    uint8_t tx[2];

    tx[0] = 0x7F & reg; 
    tx[1] = data;      

    LSM_CS_LOW();
    HAL_SPI_Transmit(&hspi2, tx, 2, HAL_MAX_DELAY);
    LSM_CS_HIGH();
}

void LSM_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer)
{
    uint8_t tx[len + 1];
    tx[0] = 0x80 | start_reg;  
    memset(&tx[1], 0x00, len); 

    LSM_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi2, tx, rx_buffer, len + 1, HAL_MAX_DELAY);
    LSM_CS_HIGH();
}

/*SPI drivers for MS5 Barometer*/

#define MS5_CS_LOW() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_RESET)
#define MS5_CS_HIGH() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_SET)

void MS5_write(uint8_t data)
{
    MS5_CS_LOW();
    HAL_SPI_Transmit(&hspi6, &data, 1, HAL_MAX_DELAY);
    MS5_CS_HIGH();
}

void MS5_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer)

/* SPI driver for SX1262 Lora radio*/
#define E22_CS_LOW() HAL_GPIO_WritePin(SX1262_CS_GPIO_Port, SX1262_CS_Pin, GPIO_PIN_RESET)
#define E22_CS_HIGH() HAL_GPIO_WritePin(SX1262_CS_GPIO_Port, SX1262_CS_Pin, GPIO_PIN_SET)

{

}

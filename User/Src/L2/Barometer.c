#include "L2/Barometer.h"
#include "L1/SPI_driver.h"
#include <stm32h7xx_hal.h>

#define CMD_RESET 0x1E    // ADC reset command
#define CMD_ADC_READ 0x00 // ADC read command
#define CMD_ADC_CONV 0x40 // ADC conversion command
#define CMD_ADC_D1 0x00   // ADC D1 conversion
#define CMD_ADC_D2 0x10   // ADC D2 conversion
#define CMD_ADC_256 0x00  // ADC OSR=256
#define CMD_ADC_512 0x02  // ADC OSR=512
#define CMD_ADC_1024 0x04 // ADC OSR=1024
#define CMD_ADC_2048 0x06 // ADC OSR=2056
#define CMD_ADC_4096 0x08 // ADC OSR=4096
#define CMD_PROM_RD 0xA0  // Prom read command

void MS5_init(void)
{
    // Send reset command to MS5 barometer
    MS5_write(CMD_RESET);
    HAL_Delay(10); // Wait for reset to complete
}

void MS5_read_PROM(MS5_prom_t *prom)
{
    uint8_t rx_buffer[3]; // 1 byte for dummy data, 2 bytes for PROM data

    for (uint8_t i = 1; i <= 6; i++)
    {

        uint8_t cmd = CMD_PROM_RD + (i << 1); // Calculate PROM read address for each coefficient

        MS5_read(cmd, 2, rx_buffer); // Read 2 bytes from each PROM address

        uint16_t coeff = ((uint16_t)rx_buffer[1] << 8) | rx_buffer[2];

        switch (i)
        {
        case 1:
            prom->C1 = coeff;
            break;
        case 2:
            prom->C2 = coeff;
            break;
        case 3:
            prom->C3 = coeff;
            break;
        case 4:
            prom->C4 = coeff;
            break;
        case 5:
            prom->C5 = coeff;
            break;
        case 6:
            prom->C6 = coeff;
            break;
        }
    }
}


void MS5_start_conversion(uint8_t cmd)
{
    MS5_write(cmd);
    HAL_Delay(10); // Wait for conversion to complete (NOTE THAT THIS VARIES BASED ON THE CHOSEN OST=R)
}


void MS5_read_raw_values(MS5_raw_values_t *values)
{
    //uint8_t rx_buffer[4]; // 1 byte for dummy data, 3 bytes for ADC data

    uint8_t cmd = CMD_ADC_CONV | CMD_ADC_D1 | CMD_ADC_4096; // NOTE THAT OSR CAN BE CHANGED HERE
    MS5_start_conversion(cmd);

    uint8_t rx_buffer[4]; // 1 byte for dummy data, 3 bytes for ADC data

    // Read raw pressure (D1)
    MS5_read(CMD_ADC_READ, 3, rx_buffer); // Read 3 bytes from ADC
    values->raw_pressure = ((int32_t)rx_buffer[1] << 16) | ((int32_t)rx_buffer[2] << 8) | rx_buffer[3];

    // // Read raw temperature (D2)
    // MS5_read(CMD_ADC_READ, 3, rx_buffer); // Read 3 bytes from ADC
    // values->raw_temperature = ((int32_t)rx_buffer[1] << 16) | ((int32_t)rx_buffer[2] << 8) | rx_buffer[3];
}

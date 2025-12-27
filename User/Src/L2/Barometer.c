#include "L1/USART_driver.h"
#include "L2/Barometer.h"
#include "L1/SPI_driver.h"
#include <stm32h7xx_hal.h>
#include "spi.h"
#include <stdint.h>
#include <stdio.h>

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

#define MS5_CS_LOW() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_RESET)
#define MS5_CS_HIGH() HAL_GPIO_WritePin(MS5_CS_GPIO_Port, MS5_CS_Pin, GPIO_PIN_SET)

/*Struct to hold MS5 barometer calibration coefficients*/
typedef struct
{
    uint16_t C1;
    uint16_t C2;
    uint16_t C3;
    uint16_t C4;
    uint16_t C5;
    uint16_t C6;
} MS5_prom_t;

typedef struct
{
    int32_t raw_pressure;    // Raw pressure value
    int32_t raw_temperature; // Raw temperature value
} MS5_raw_values_t;


static MS5_prom_t ms5_coeffs;


/* Static Helper functions */

static void MS5_read_PROM(MS5_prom_t *prom)
{
    uint8_t rx_buffer[3];

    for (uint8_t i = 1; i <= 6; i++)
    {

        uint8_t cmd = CMD_PROM_RD + (i << 1); // 0XA2, 0XA4, ...

        MS5_read(cmd, 2, rx_buffer);

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

static void MS5_read_raw_values(MS5_raw_values_t *values)
{
    uint8_t rx_buffer[4];

    // convert and read D1
    uint8_t cmd = CMD_ADC_CONV | CMD_ADC_D1 | CMD_ADC_4096;
    MS5_write(cmd);
    HAL_Delay(10); // varies based on OSR
    MS5_read(CMD_ADC_READ, 3, rx_buffer);
    values->raw_pressure = ((int32_t)rx_buffer[1] << 16) | ((int32_t)rx_buffer[2] << 8) | rx_buffer[3];

    // convert and read D2
    cmd = CMD_ADC_CONV | CMD_ADC_D2 | CMD_ADC_4096;
    MS5_write(cmd);
    HAL_Delay(10); // varies based on OSR
    MS5_read(CMD_ADC_READ, 3, rx_buffer);
    values->raw_temperature = ((int32_t)rx_buffer[1] << 16) | ((int32_t)rx_buffer[2] << 8) | rx_buffer[3];
}

/* Public-facing functions*/

void MS5_initialize(void)
{
    // Send reset command
    uint8_t cmd = CMD_RESET;
    MS5_CS_LOW();
    HAL_SPI_Transmit(&hspi6, &cmd, 1, HAL_MAX_DELAY);
    HAL_Delay(5);
    MS5_CS_HIGH();

    // Read PROM coefficients once
    MS5_read_PROM(&ms5_coeffs);

}

void MS5_read_compensated_values(MS5_compensated_values_t *comp_values)
{
    char buf[75];
    MS5_raw_values_t raw_values;
    MS5_read_raw_values(&raw_values);

    sprintf(buf, "C1: %u C2: %u C3: %u C4: %u C5: %u C6: %u\r\n", ms5_coeffs.C1, ms5_coeffs.C2, ms5_coeffs.C3, ms5_coeffs.C4, ms5_coeffs.C5, ms5_coeffs.C6);
    send_host_message(buf);
    sprintf(buf, "Raw Pressure: %ld Raw Temperature: %ld\r\n", raw_values.raw_pressure, raw_values.raw_temperature);
    send_host_message(buf);

}

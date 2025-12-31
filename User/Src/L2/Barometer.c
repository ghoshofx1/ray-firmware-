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
    uint32_t raw_pressure;    // Raw pressure value
    uint32_t raw_temperature; // Raw temperature value
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

    uint32_t D1 = raw_values.raw_pressure;
    uint32_t D2 = raw_values.raw_temperature;

    double_t TEMP, PRESSURE, dT, OFF, SENS;
    float x;
    float y;

    /* Not sure if this is the most efficient way. Maybe it is better to store the coeffs as double_t in the first place??*/
    double_t C[] = {
        0,
        (double_t)ms5_coeffs.C1,
        (double_t)ms5_coeffs.C2,
        (double_t)ms5_coeffs.C3,
        (double_t)ms5_coeffs.C4,
        (double_t)ms5_coeffs.C5,
        (double_t)ms5_coeffs.C6
    };
    
    /* Calculate 1st order pressure and temperature */

    dT = (double_t)D2 - (C[5] * 256.0);          // 2^8

    OFF = (C[2] * 131072.0) + (dT * C[4]) / 64.0;   // 2^17, 2^6

    SENS = (C[1] * 65536.0) + (dT * C[3]) / 128.0;  // 2^16, 2^7

    TEMP = (2000.0 + (dT * C[6]) / 8388608.0) / 100.0; // 2^23

    PRESSURE = ((((double_t)D1 * SENS) / 2097152.0 - OFF)  // 2^21
                / 32768.0)                                 // 2^15
     / 100.0;

    
    comp_values->pressure = PRESSURE;    // in mbar
    comp_values->temperature = TEMP;      // in deg C

    // x = (float)TEMP;
    // y = (float)PRESSURE;

    // sprintf(buf, "FLOAT TEMP: %.2f C, FLOAT PRESSURE: %.2f mbar\r\n", x, y);
    // send_host_message(buf);
}

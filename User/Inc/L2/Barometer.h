#ifndef BAROMETER_H
#define BAROMETER_H

#include <stdint.h>


/*Struct to hold MS5 barometer calibration coefficients*/
typedef struct {
    uint16_t C1;
    uint16_t C2;
    uint16_t C3;
    uint16_t C4;
    uint16_t C5;
    uint16_t C6;
} MS5_prom_t;

typedef struct {
    int32_t raw_pressure; // Raw pressure value
    int32_t raw_temperature; // Raw temperature value
} MS5_raw_values_t;

void MS5_init(void);
void MS5_read_PROM(MS5_prom_t *prom);
void MS5_start_conversion(uint8_t cmd);
void MS5_read_raw_values(MS5_raw_values_t *values);

#endif // BAROMETER_H
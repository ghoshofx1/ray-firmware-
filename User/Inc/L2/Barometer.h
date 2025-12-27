#ifndef BAROMETER_H
#define BAROMETER_H

#include <stdint.h>


typedef struct {
    float pressure;    // Compensated pressure in mbar
    float temperature; // Compensated temperature in degrees Celsius
} MS5_compensated_values_t;

void MS5_reset(void);
// void MS5_read_PROM(MS5_prom_t *prom);
// void MS5_start_conversion(uint8_t cmd);
// void MS5_read_raw_values(MS5_raw_values_t *values);
void MS5_read_compensated_values(MS5_compensated_values_t *comp_values);

#endif // BAROMETER_H
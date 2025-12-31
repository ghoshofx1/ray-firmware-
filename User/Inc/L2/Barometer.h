#ifndef BAROMETER_H
#define BAROMETER_H

#include <stdint.h>

typedef struct
{
    int32_t pressure;    // Compensated pressure in mbar
    int32_t temperature; // Compensated temperature in degrees Celsius
} MS5_compensated_values_t;

void MS5_initialize(void);

void MS5_read_compensated_values(MS5_compensated_values_t *comp_values);

#endif // BAROMETER_H
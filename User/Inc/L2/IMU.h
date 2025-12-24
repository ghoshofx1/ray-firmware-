#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LSM_accel_raw_t;


uint8_t LSM_check_status(void);
void LSM_init(void);
void LSM_accel_raw_read(LSM_accel_raw_t *accel);


#endif /* SENSORS_H */

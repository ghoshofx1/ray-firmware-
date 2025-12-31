#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>


/* Physical values in m/s^2 and rad/s */
typedef struct {
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
} IMU_phys_t;

void LSM_check_status(void);
void LSM_init(void);

void LSM_get_phys(IMU_phys_t *phys);

#endif /* SENSORS_H */

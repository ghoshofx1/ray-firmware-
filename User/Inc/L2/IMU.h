#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

/* Accelerometer raw data */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LSM_accel_raw_t;

/* Gyroscope raw data */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LSM_gyro_raw_t;

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

void LSM_accel_raw_read(LSM_accel_raw_t *accel_raw);
void LSM_gyro_raw_read(LSM_gyro_raw_t *gyro_raw);

void LSM_convert(const LSM_accel_raw_t *raw, const LSM_gyro_raw_t *gyro_raw, IMU_phys_t *phys);
float gyro_rads(int16_t raw);
float accel_mps2(int16_t raw);
float gyro_dps(int16_t raw);

#endif /* SENSORS_H */

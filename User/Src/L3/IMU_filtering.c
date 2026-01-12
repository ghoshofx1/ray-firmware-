#include "L3/IMU_filtering.h"
#include "L2/IMU.h"
#include <math.h>
#include <stdint.h>
#include "stm32h7xx_hal.h"

// Raw IMU data
static IMU_phys_t IMU_raw; 

// Complementary filter variables
static float theta_measured, phi_measured, theta_filtered, phi_filtered, dt, theta_gyro, phi_gyro, sys_theta, sys_phi;
static uint32_t last_tick;

/*NOTE: This is a very basic complementary filter - will not work for angles greater than 50 degrees*/
void complementary_filter_update(float* roll, float* pitch) {

    LSM_get_phys(&IMU_raw);

    theta_measured = -atan2(IMU_raw.ax/9.81, IMU_raw.az/9.81)/2/3.14159265*360;
    phi_measured = atan2(IMU_raw.ay/9.81, IMU_raw.az/9.81)/2/3.14159265*360;

    // Apply a simple low-pass filter
    theta_filtered = 0.9*theta_filtered + 0.1*theta_measured;
    phi_filtered = 0.9*phi_filtered + 0.1*phi_measured;

    // get dt
    dt = (HAL_GetTick() - last_tick) * 0.001f;  // ms → seconds
    last_tick = HAL_GetTick();

    // Pitch is rotation about Y axis
    theta_gyro = theta_gyro + IMU_raw.gy * dt;
    // Roll is rotation about X axis
    phi_gyro = phi_gyro + IMU_raw.gx * dt;


    sys_theta = 0.95 * (sys_theta + IMU_raw.gy * dt) + 0.05 * theta_measured;
    sys_phi = 0.95 * (sys_phi + IMU_raw.gx * dt) + 0.05 * phi_measured;

    *pitch = sys_theta;
    *roll = sys_phi;

}
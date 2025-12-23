#ifndef SENSORS_H
#define SENSORS_H

#include "main.h"
#include "user_main.h"


// #include "spi.h"
// #include <stdint.h>


#define LSM_CS_PORT GPIOC
#define LSM_CS_PIN  GPIO_PIN_5


// extern uint8_t rx[2];

#define LSM_CS_LOW() HAL_GPIO_WritePin(LSM_CS_PORT, LSM_CS_Pin, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(LSM_CS_PORT, LSM_CS_PIN, GPIO_PIN_SET)


// typedef struct {
//     int16_t x;
//     int16_t y;
//     int16_t z;
// } LSM_accel_raw_t;

uint8_t LSM_check(void);
void LSM_init(void);
uint8_t LSM_read(uint8_t reg, uint8_t bytes);
void LSM_accel_raw_read(void);


#endif /* SENSORS_H */

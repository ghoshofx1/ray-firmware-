#ifndef SENSORS_H
#define SENSORS_H

#include "main.h"
// #include "spi.h"
// #include <stdint.h>

extern uint8_t rx[2];

#define LSM_CS_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET)

uint8_t lsm6dsv_read_whoami(void);

#endif /* SENSORS_H */

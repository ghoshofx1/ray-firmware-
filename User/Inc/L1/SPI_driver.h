#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H
#include <stdint.h>
#include "main.h"

/*SPI drivers for LSM6DSV16X IMU*/

#define LSM_CS_LOW() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(LSM_CS_GPIO_Port, LSM_CS_Pin, GPIO_PIN_SET)

void LSM_write(uint8_t reg, uint8_t data);
void LSM_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer);

#endif // SPI_DRIVER_H
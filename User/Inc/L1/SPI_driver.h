#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H
#include <stdint.h>

/*SPI drivers for LSM6DSV16X IMU*/
#define LSM_CS_PORT GPIOC
#define LSM_CS_PIN  GPIO_PIN_5

#define LSM_CS_LOW() HAL_GPIO_WritePin(LSM_CS_PORT, LSM_CS_Pin, GPIO_PIN_RESET)
#define LSM_CS_HIGH() HAL_GPIO_WritePin(LSM_CS_PORT, LSM_CS_PIN, GPIO_PIN_SET)

void LSM_write(uint8_t reg, uint8_t data);
uint8_t LSM_read(uint8_t start_reg, uint8_t bytes);


#endif // SPI_DRIVER_H
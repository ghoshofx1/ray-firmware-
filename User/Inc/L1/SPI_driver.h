#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H
#include <stdint.h>


void LSM_write(uint8_t reg, uint8_t data);
void LSM_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer);

void MS5_write(uint8_t data);
void MS5_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer);
#endif // SPI_DRIVER_H
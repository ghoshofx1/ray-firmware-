#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H
#include <stdint.h>

typedef enum sx126x_hal_status_e
{
    SX126X_HAL_STATUS_OK    = 0,
    SX126X_HAL_STATUS_ERROR = 3,
}   sx126x_hal_status_t;


// SPI functions for LSM6SV IMU
void LSM_write(uint8_t reg, uint8_t data);
void LSM_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer);


// SPI functions for MS5 Barometer
void MS5_write(uint8_t data);
void MS5_read(uint8_t start_reg, uint8_t len, uint8_t *rx_buffer);

// SPI HAL functions for SX126x Radio
sx126x_hal_status_t sx126x_hal_write( const uint8_t* command, const uint16_t command_length,
                                      const uint8_t* data, const uint16_t data_length );

sx126x_hal_status_t sx126x_hal_read( const uint8_t* command, const uint16_t command_length,
                                     uint8_t* data, const uint16_t data_length );

sx126x_hal_status_t sx126x_hal_reset();

sx126x_hal_status_t sx126x_hal_wakeup();

#endif // SPI_DRIVER_H
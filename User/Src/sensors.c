// #include "main.h"
#include "sensors.h"
#include "spi.h"
#include <stdint.h>
#include "host_UART.h"




uint8_t lsm6dsv_read_whoami(void)
{
    uint8_t tx[2];
    uint8_t rx[2];
    //rx[1] = 33; // dummy init value

    tx[0] = 0x0F | 0x80; // WHO_AM_I register, read bit set
    tx[1] = 0x00;        // dummy byte

    LSM_CS_LOW();
    if (HAL_SPI_TransmitReceive(&hspi2, tx, rx, 2, HAL_MAX_DELAY) == HAL_OK)
    {
        send_host_message("SPI transaction successful.\r\n");
    }
    else
    {
        send_host_message("SPI transaction failed.\r\n");
        // return 0xFF; // error code
    }
    LSM_CS_HIGH();

    return rx[1]; // valid data
}



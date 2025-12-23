#include "user_main.h"
#include "host_UART.h"
// #include "usart.h"
#include "sensors.h"
#include <stdio.h>
#include <string.h>

// typedef struct {
//     int16_t x;
//     int16_t y;
//     int16_t z;
// } lsm6dsv_accel_raw_t;

// typedef struct
// {
//     int16_t x;
//     int16_t y;
//     int16_t z;
// } LSM_accel_raw_t;

void user_main(void)
{

    char buf[20]; // buffer for the message
    uint8_t check;

    LSM_init();

    while (1)
    {

        // check = LSM_read(0x10);

        // sprintf(buf, "CTRL1 = 0x%02X\r\n", check);

        // send_host_message(buf);
        // send_host_message("\r\n");
        LSM_accel_raw_read();

        HAL_Delay(1000);
    }
}
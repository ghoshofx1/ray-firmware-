#include "user_main.h"
#include "host_UART.h"
// #include "usart.h"
#include "sensors.h"
#include <stdio.h>
#include <string.h>

void user_main(void)
{
    // static char name_buffer[50];  // STATIC → no stack corruption

    // while (1)
    // {
    //     send_host_message("\r\nHello, Host! What is your name?\r\n");
    //     receive_host_message(name_buffer, sizeof(name_buffer));

    //     send_host_message("Nice to meet you, ");
    //     send_host_message(name_buffer);
    //     send_host_message("\r\n");

    //     HAL_Delay(1000);
    // }
    char buf[20];  // buffer for the message
    uint8_t whoami;

    
    while (1)
    {
        whoami = lsm6dsv_read_whoami();
        sprintf(buf, "WHO_AM_I = 0x%02X\r\n", whoami);
        // send_host_message("what i see is: ");
        // send_host_message((char *) whoami);
        send_host_message(buf);
        send_host_message("\r\n");
        HAL_Delay(1000);
    }
}
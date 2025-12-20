#include "user_main.h"
#include "main.h"
#include "host_UART.h"


void user_main(void)
{
    char name_buffer[50];
    while (1)
    {
        send_host_message("Hello, Host! What is your name\r\n");
        // receive_host_message(name_buffer, sizeof(name_buffer));
        // send_host_message("Nice to meet you, ");
        // send_host_message(name_buffer);
        // send_host_message("\r\n");

        HAL_Delay(1000); // Delay for 1 second
    }
}

#include "user_main.h"
#include "main.h"
#include "host_UART.h"
#include "usart.h"


void user_main(void)
{
    static char name_buffer[50];  // STATIC → no stack corruption

    while (1)
    {
        send_host_message("\r\nHello, Host! What is your name?\r\n");
        receive_host_message(name_buffer, sizeof(name_buffer));

        send_host_message("Nice to meet you, ");
        send_host_message(name_buffer);
        send_host_message("\r\n");

        HAL_Delay(1000);
    }
}
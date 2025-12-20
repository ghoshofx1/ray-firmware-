#include "host_UART.h"
#include "usart.h"
#include <string.h>

void send_host_message(const char* message)
{
  
    HAL_UART_Transmit(&huart5, (const uint8_t*)message, strlen(message), HAL_MAX_DELAY); // Implementation for sending a message to the host via UART
}

void receive_host_message(char* buffer, int max_length)
{

    uint16_t i = 0;
    char c;

    while (i < max_length - 1)
    {
        HAL_UART_Receive(&huart5, (uint8_t *)&c, 1, HAL_MAX_DELAY);

        // Echo back so user sees typing
        HAL_UART_Transmit(&huart5, (uint8_t *)&c, 1, HAL_MAX_DELAY);

        if (c == '\r' || c == '\n')
        {
            break;
        }

        buffer[i++] = c;
    }

    buffer[i] = '\0';
}



#include "L1/USART_driver.h"
#include "usart.h"
#include <string.h>

/*variable definitions for GPS data reception */
volatile uint8_t gps_rx_ch = 0;
volatile char gps_line[GPS_LINE_MAX];
volatile uint16_t gps_character_count = 0;
volatile uint8_t gps_line_ready = 0;

void send_host_message(const char *message)
{
    HAL_UART_Transmit(&huart5, (const uint8_t *)message, strlen(message), HAL_MAX_DELAY); // Implementation for sending a message to the host via UART
}

void receive_host_message(char *buffer, int max_len)
{
    uint16_t i = 0;
    char c;

    // Clear buffer defensively
    for (uint16_t j = 0; j < max_len; j++)
        buffer[j] = 0;

    while (1)
    {
        HAL_UART_Receive(&huart5, (uint8_t *)&c, 1, HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart5, (uint8_t *)&c, 1, HAL_MAX_DELAY);

        if (c == '\r' || c == '\n')
            break;

        if (i < max_len - 1)
            buffer[i++] = c;
    }

    buffer[i] = '\0';
}

void GPS_arm_receive_interrupt(void)
{
    HAL_UART_Receive_IT(&huart1, &gps_rx_ch, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        uint8_t ch = gps_rx_ch;

        if (ch == '\n') {
            gps_line[gps_character_count] = '\0';
            gps_line_ready = 1;
            gps_character_count = 0;
            
        }
        else if (gps_character_count < GPS_LINE_MAX - 1)
         {
            gps_line[gps_character_count] = ch;
            gps_character_count++;
        }
        else {
            gps_character_count = 0;
        }

        // Re-arm interrupt
        GPS_arm_receive_interrupt();
    }
}

// void print_GPS(void)
// {
//     if (gps_line_ready)
//     {   
//         gps_line_ready = 0;
//         send_host_message(gps_line);
//         send_host_message("\r\n");
        
//     }
// }


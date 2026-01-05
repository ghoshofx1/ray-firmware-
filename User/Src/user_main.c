#include "L2/IMU.h"
#include "L2/Barometer.h"
#include "L1/USART_driver.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>
#include <math.h>
#include "usart.h"




#define GPS_LINE_MAX 128

//  UART_HandleTypeDef huart_gps;

volatile uint8_t gps_rx_ch;
volatile uint8_t gps_line_ready = 0;

char gps_line[GPS_LINE_MAX];
volatile uint16_t gps_idx = 0;

//UART_HandleTypeDef huart_gps;



// void float_to_str(float x) {

// char str[100];
// char *tmpSign = (x < 0) ? "-" : "";
// float tmpVal = (x < 0) ? -x : x;
// int tmpInt1 = tmpVal;                  // Get the integer (678).
// float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
// int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

// sprintf(str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
// send_host_message(str);
// }

uint8_t cha;





void user_main(void)
{

    HAL_UART_Receive_IT(&huart1, &gps_rx_ch, 1);
    char buf[256];
    
    //uint8_t i = 0;

    while (1)

    {   

    
       
    // if (HAL_UART_Receive(&huart1, &cha, 1, HAL_MAX_DELAY) == HAL_OK)
    // {   


    //     //send_host_message(&cha);
    //     //i++;

    if (gps_line_ready)
        {
            
            gps_line_ready = 0;
            sprintf(buf, "GPS: %s\r\n", gps_line);
            send_host_message(buf);
        }
        
    

    //HAL_Delay(1000);
    }

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1)
    {
        uint8_t ch = gps_rx_ch;

        if (ch == '\n') {
            gps_line[gps_idx] = '\0';
            gps_line_ready = 1;
            gps_idx = 0;
        }
        else if (gps_idx < GPS_LINE_MAX - 1) {
            gps_line[gps_idx++] = ch;
        }
        else {
            gps_idx = 0;
        }

        // 🔑 Re-arm interrupt
        HAL_UART_Receive_IT(&huart1, &gps_rx_ch, 1);
    }
}
#include "L2/IMU.h"
#include "L2/Barometer.h"
#include "L1/USART_driver.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>
#include <math.h>
#include "usart.h"

void float_to_str(float x) {

char str[100];
char *tmpSign = (x < 0) ? "-" : "";
float tmpVal = (x < 0) ? -x : x;
int tmpInt1 = tmpVal;                  // Get the integer (678).
float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

sprintf(str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
send_host_message(str);
}

void user_main(void)
{
    uint8_t ch;

    while (1)
    {   
               
    // Non-blocking GPS RX
    // if (HAL_UART_Receive(&huart_gps, &ch, 1, 0) == HAL_OK)
    // {
    //     if (ch == '\n') {
    //         gps_line[gps_idx] = 0;
    //         process_nmea(gps_line);
    //         gps_idx = 0;
    //     } else if (gps_idx < GPS_BUF_LEN - 1) {
    //         gps_line[gps_idx++] = ch;
    //     }
    // }
        //send_host_message("Reading IMU Data...\r\n");
        HAL_Delay(1000);
    }

}
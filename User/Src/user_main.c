#include "L1/USART_driver.h"
#include "L2/IMU.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>



void user_main(void)
{

    char buf[50]; 

    //LSM_check_status();
    LSM_init();
    HAL_Delay(1000);
    LSM_accel_raw_t accel;

    while (1)
    {   
        //LSM_check_status();
        LSM_accel_raw_read(&accel);
        sprintf(buf, "AX: %d AY: %d AZ: %d\r\n", accel.x, accel.y, accel.z);
        send_host_message(buf);
        HAL_Delay(10);
    }
}
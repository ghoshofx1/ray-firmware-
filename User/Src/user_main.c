#include "L2/IMU.h"
#include "user_main.h"
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
        LSM_check_status();
        LSM_accel_raw_read(&accel);
        HAL_Delay(1000);
    }
}
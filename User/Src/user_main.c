#include "L2/IMU.h"
#include "L2/Barometer.h"
#include "L1/USART_driver.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>



void user_main(void)
{

    float buf[75]; 
    

    LSM_init();
    
    MS5_initialize();
 
    MS5_compensated_values_t comp_values;
    IMU_phys_t imu_data;

    
    while (1)
    {   
               
        MS5_read_compensated_values(&comp_values);
        LSM_get_phys(&imu_data);
      
        HAL_Delay(100);
    }
}
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
    // LSM_init();
    // HAL_Delay(1000);
    // LSM_accel_raw_t accel;
    // LSM_gyro_raw_t gyro;
    // IMU_phys_t imu_data;


    
    while (1)
    {   
        
        // LSM_accel_raw_read(&accel);
        
        // LSM_gyro_raw_read(&gyro);
      
        // sprintf(buf, "AX: %d AY: %d AZ: %d\r\n", accel.x, accel.y, accel.z);
        // send_host_message(buf);
        // sprintf(buf, "GX: %d GY: %d GZ: %d\r\n", gyro.x, gyro.y, gyro.z);
        // send_host_message(buf);  
        // LSM_convert(&accel, &gyro, &imu_data);  
       
    
        HAL_Delay(10);
    }
}
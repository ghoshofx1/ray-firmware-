#include "L2/IMU.h"
#include "L2/Barometer.h"
#include "L1/USART_driver.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>



void user_main(void)
{

    char buf[75]; 

    //LSM_check_status();
    // LSM_init();
    // HAL_Delay(1000);
    // LSM_accel_raw_t accel;
    // LSM_gyro_raw_t gyro;
    // IMU_phys_t imu_data;
    MS5_init();
    MS5_prom_t prom;
    MS5_raw_values_t values;

    
    while (1)
    {   
        
        // LSM_accel_raw_read(&accel);
        
        // LSM_gyro_raw_read(&gyro);
      
        // sprintf(buf, "AX: %d AY: %d AZ: %d\r\n", accel.x, accel.y, accel.z);
        // send_host_message(buf);
        // sprintf(buf, "GX: %d GY: %d GZ: %d\r\n", gyro.x, gyro.y, gyro.z);
        // send_host_message(buf);  
        // LSM_convert(&accel, &gyro, &imu_data);  


        // MS5_read_PROM(&prom);
        // sprintf(buf, "C1: %u C2: %u C3: %u C4: %u C5: %u C6: %u\r\n", prom.C1, prom.C2, prom.C3, prom.C4, prom.C5, prom.C6);
        // send_host_message(buf);

        MS5_read_raw_values(&values);
        sprintf(buf, "Raw Pressure: %ld Raw Temperature: %ld\r\n", values.raw_pressure, values.raw_temperature);
        send_host_message(buf);



        HAL_Delay(1000);
    }
}
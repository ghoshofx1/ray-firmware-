#include "L2/IMU.h"
#include "L2/Barometer.h"
#include "L1/USART_driver.h"
#include "user_main.h"
#include <stdio.h>
#include <string.h>
#include <stm32h7xx_hal.h>
#include <math.h>

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

    char buf[75]; 
    
    LSM_init();
    
    MS5_initialize();
 
    MS5_compensated_values_t comp_values;
    IMU_phys_t imu_data;

    float theta_m, phi_m;
    float theta_f = 0;
    float phi_f = 0;
    // float theta_f_old = 0;
    // float phi_f_old = 0;
    // float theta_f_new =0;
    // float phi_f_new =0;




    uint32_t last_tick = HAL_GetTick();
    float dt;
    //uint32_t now;


    float theta_gyro = 0;
    float phi_gyro = 0;

    float sys_theta = 0;
    float sys_phi = 0; 

    
    while (1)
    {   
               
        //MS5_read_compensated_values(&comp_values);
        LSM_get_phys(&imu_data);

        theta_m = -atan2(imu_data.ax/9.81, imu_data.az/9.81)/2/3.14159265*360;
        phi_m = atan2(imu_data.ay/9.81, imu_data.az/9.81)/2/3.14159265*360;

        // Apply a simple low-pass filter
        theta_f = 0.9*theta_f + 0.1*theta_m;
        phi_f = 0.9*phi_f + 0.1*phi_m;



        // get dt
        dt = (HAL_GetTick() - last_tick) * 0.001f;  // ms → seconds
        last_tick = HAL_GetTick();


        // Pitch is rotation about Y axis
        theta_gyro = theta_gyro + imu_data.gy * dt;
        // Roll is rotation about X axis
        phi_gyro = phi_gyro + imu_data.gx * dt;



        // Complementary filter to combine accelerometer and gyroscope
        sys_theta = 0.9 * (sys_theta + imu_data.gy * dt) + 0.1 * theta_f;
        sys_phi = 0.9 * (sys_phi + imu_data.gx * dt) + 0.1 * phi_f;

        

    
        send_host_message("ax: ");
        float_to_str(imu_data.ax/9.81);
        send_host_message(", ");
        send_host_message("ay: ");
        float_to_str(imu_data.ay/9.81);
        send_host_message(", ");    
        send_host_message("az: ");
        float_to_str(imu_data.az/9.81);
        send_host_message(", ");
        // send_host_message("\r\n");
        send_host_message("theta : ");
        float_to_str(theta_m);
        send_host_message(", ");
        send_host_message("phi : ");
        float_to_str(phi_m);
        send_host_message(", ");
        //send_host_message("\r\n");
        send_host_message("theta_f : ");
        float_to_str(theta_f);
        send_host_message(", ");
        send_host_message("phi_f : ");
        float_to_str(phi_f);
        //send_host_message("\r\n");
        send_host_message(", ");
        send_host_message("theta_gyro: ");
        float_to_str(theta_gyro);
        send_host_message(", ");
        send_host_message("phi_gyro: ");
        float_to_str(phi_gyro);
        // send_host_message(", ");
        // send_host_message("Gyro X: ");      
        // float_to_str(imu_data.gx); 
        // send_host_message(", ");
        // send_host_message("Gyro Y: ");
        // float_to_str(imu_data.gy);
        send_host_message(", ");
        send_host_message("sys_theta: ");
        float_to_str(sys_theta);
        send_host_message(", ");
        send_host_message("sys_phi: ");
        float_to_str(sys_phi);
        send_host_message("\r\n");
        
        // Update old filtered values
        // theta_f_old = theta_f_new;
        // phi_f_old = phi_f_new;
        HAL_Delay(100);


    }
}
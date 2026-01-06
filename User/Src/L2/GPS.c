#include "GPS.h"
#include "USART_driver.h"
#include <stdint.h>



void GPS_init(void)
{
    GPS_arm_receive_interrupt();
}
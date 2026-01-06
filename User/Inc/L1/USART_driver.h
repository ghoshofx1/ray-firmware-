#ifndef USART_DRIVER_H
#define USART_DRIVER_H

// volatile uint8_t gps_rx_ch;
// volatile uint8_t gps_line_ready = 0;
// char gps_line[GPS_LINE_MAX];
// volatile uint16_t gps_idx = 0;
#include <stdint.h>

#define GPS_LINE_MAX 128

/* these variables are serviced inside an ISR (volatile) and are available to higher layers (extern)*/
extern volatile uint8_t gps_rx_ch;
extern volatile uint8_t gps_line_ready;
extern volatile char gps_line[GPS_LINE_MAX];
extern volatile uint16_t gps_character_count;


void send_host_message(const char* message);
void receive_host_message(char* buffer, int max_len);

void GPS_arm_receive_interrupt(void);
//void print_GPS(void);

#endif /* USART_DRIVER_H */
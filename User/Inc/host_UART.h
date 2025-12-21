#ifndef HOST_UART_H
#define HOST_UART_H

void send_host_message(const char* message);

void receive_host_message(char* buffer, int max_len);

#endif /* HOST_UART_H */


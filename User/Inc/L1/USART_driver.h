#ifndef USART_DRIVER_H
#define USART_DRIVER_H

void send_host_message(const char* message);
void receive_host_message(char* buffer, int max_len);

#endif /* USART_DRIVER_H */
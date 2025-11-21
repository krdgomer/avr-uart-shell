#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#define FOSC 16000000UL  // Most Arduinos are 16MHz
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Transmit_str(const char* str);;
int USART_DataAvailable(void);

#endif
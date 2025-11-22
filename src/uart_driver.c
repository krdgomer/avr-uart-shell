#include "uart_driver.h"
#include <avr/io.h>


void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1<<UDRE0)));  
    UDR0 = data;  
}

unsigned char USART_Receive(void) {
    while (!(UCSR0A & (1<<RXC0)));  
    return UDR0;  
}
void USART_Transmit_str(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

int USART_DataAvailable(void) {
    return (UCSR0A & (1 << RXC0));  
}
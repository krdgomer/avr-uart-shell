#include "uart.h"
#include <avr/io.h>


void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1<<UDRE0)));  // Fixed: n → 0
    UDR0 = data;  // Fixed: n → 0
}

unsigned char USART_Receive(void) {
    while (!(UCSR0A & (1<<RXC0)));  // Fixed: n → 0
    return UDR0;  // Fixed: n → 0
}

void USART_Transmit_str(char* str) {
    while(*str) {
        USART_Transmit(*str);
        str++;
    }
}
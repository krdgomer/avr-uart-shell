#include <stdio.h>
#include "uart.h"
#include <util/delay.h>
#include <string.h>

int main(void) {  
    char buffer[128];
    int buffer_index = 0;
    int line_ready = 0;

    USART_Init(MYUBRR);
    _delay_ms(100);
    USART_Transmit('>');
    
    while(1) {
        char c = USART_Receive();

        if(c == '\r' || c == '\n') {
            buffer[buffer_index] = '\0'; 
            line_ready = 1;
        }
        else {
            buffer[buffer_index] = c;
            buffer_index++;
            USART_Transmit(c);
        }

        if(line_ready == 1) {
            // Echo the received line
            if(strcmp(buffer,"hello") == 0){
                USART_Transmit('\r');
                USART_Transmit('\n');
                USART_Transmit_str("Hello with UART");
            }
            
            USART_Transmit('\r');
            USART_Transmit('\n');
            USART_Transmit('>');
            
            line_ready = 0;
            buffer_index = 0;
        }
    }
}
#include <stdio.h>
#include "uart_driver.h"
#include <util/delay.h>
#include "shell.h"

// Example usage of shell

int main(void) {  

    USART_Init(MYUBRR);
    _delay_ms(100);
    shell_init();
    
    while(1) {
       shell_poll();
    }
}
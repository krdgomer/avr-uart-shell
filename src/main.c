#include <stdio.h>
#include "uart_driver.h"
#include <util/delay.h>
#include "shell.h"

int main(void) {  

    USART_Init(MYUBRR);
    _delay_ms(100);
    init_shell();
    
    while(1) {
       update_shell();
    }
}
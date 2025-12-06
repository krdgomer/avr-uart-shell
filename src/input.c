#include "input.h"
#include "shell.h"
#include "uart_driver.h"

void handle_key_pressed(char key, uint8_t *buffer_index, char *buffer, uint8_t *line_ready) {
    // Enter pressed
    if (key == '\r' || key == '\n') {
        if (*buffer_index > 0) {  
            buffer[*buffer_index] = '\0'; 
            *line_ready = 1;  
        }
    }
    // Backspace pressed
    else if (key == 8 || key == 127) {
        if (*buffer_index > 0) {  
            (*buffer_index)--;  
            USART_Transmit('\b'); 
            USART_Transmit(' ');       
            USART_Transmit('\b'); 
        }
    }
    // Normal key pressed
    else if (*buffer_index < (BUFFER_LENGTH - 1)) {  
        buffer[(*buffer_index)++] = key;  
        USART_Transmit(key);
    }
}


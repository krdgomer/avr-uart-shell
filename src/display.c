#include "display.h"
#include "uart_driver.h"

static void display_ansi_clear_line(void) {
    // ANSI escape sequence: ESC [2K = clear entire line
    USART_Transmit(0x1B);  // ESC
    USART_Transmit('[');
    USART_Transmit('2');
    USART_Transmit('K');
    
    // Move cursor to beginning of line
    USART_Transmit('\r');
}

void display_prompt(void) {
    USART_Transmit('\r');
    USART_Transmit('\n');
    USART_Transmit('>');
}

void display_line(const char* str) {
    USART_Transmit_str(str);
}

void display_clear_line(void) {
    display_ansi_clear_line();
}

void display_history_command(const char *cmd) {
    display_ansi_clear_line();
    USART_Transmit('>');
    USART_Transmit_str(cmd);
}
#include "shell.h"
#include "uart_driver.h"
#include <string.h>
#include <avr/io.h>
#include "command.h"
#include "commands/led.h"
#include "commands/help.h"

static char buffer[BUFFER_LENGTH];
static uint8_t buffer_index = 0;
static uint8_t line_ready = 0;

static void display_prompt(void) {
    USART_Transmit('\r');
    USART_Transmit('\n');
    USART_Transmit('>');
}

void display_line(const char* str) {
    USART_Transmit_str(str);
}

static void process_command(int argc, char **argv) {
    command_def_t *cmd = find_command(argv[0]);
    if (cmd) {
        if (cmd->validate(argc, argv)) {
            cmd->execute(argc, argv);
        } else {
            display_line("Invalid syntax. Use: ");
            display_line(cmd->help);
        }
    } else {
        display_line("Unknown command. Write \"help\" for command list.");
    }
}

void init_shell(void) {
    register_led_command();
    register_help_command();
    DDRB |= (1 << DDB5);  
    display_line("ATmega328P UART shell initialized.");
    display_prompt();
}

void update_shell(void) {
    if (USART_DataAvailable()) {  
        char c = USART_Receive();
        
        if (c == '\r' || c == '\n') {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0'; 
                line_ready = 1;
            }
        }
        else if (buffer_index < (BUFFER_LENGTH - 1)) {
            buffer[buffer_index++] = c;
            USART_Transmit(c);
        }
        
        if (line_ready) {
            USART_Transmit('\r');
            USART_Transmit('\n');
            
            // Parse buffer into argc/argv
            char *argv[10];
            int argc = 0;
            
            char *token = strtok(buffer, " ");
            while (token != NULL && argc < 10) {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            
            if (argc > 0) {
                process_command(argc, argv); 
            }
            
            display_prompt();
            line_ready = 0;
            buffer_index = 0;
        }
    }
}
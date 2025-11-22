#include "shell.h"
#include "uart_driver.h"
#include <string.h>
#include <avr/io.h>
#include "command.h"
#include "commands/led.h"
#include "commands/help.h"
#include <stdio.h>

static char buffer[BUFFER_LENGTH];
static uint8_t buffer_index = 0;
static uint8_t line_ready = 0;
static char cmd_history[HISTORY_SIZE][25];
static uint8_t history_index = 0;
static uint8_t history_count= 0;


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

static void clear_line(void) {
    // ANSI escape sequence: ESC [2K = clear entire line
    USART_Transmit(0x1B);  // ESC
    USART_Transmit('[');
    USART_Transmit('2');
    USART_Transmit('K');
    
    // Move cursor to beginning of line
    USART_Transmit('\r');
}

static void handle_up_arrow(void) {
    if (history_count == 0) return;  
    
    if (history_index < history_count - 1) {
        history_index++;
    } else {
        // Loop back to the beginning (oldest command)
        history_index = 0;
    }
    
    clear_line();
    USART_Transmit('>');
    USART_Transmit_str(cmd_history[history_index]);
    
    strcpy(buffer, cmd_history[history_index]);
    buffer_index = strlen(cmd_history[history_index]);
}

static void handle_down_arrow(void) {
    if (history_count == 0) return;
    
    if (history_index > 0) {
        history_index--;
    } else {
        // Loop back to the end (newest command)
        history_index = history_count - 1;
    }
    
    clear_line();
    USART_Transmit('>');
    USART_Transmit_str(cmd_history[history_index]);
    
    strcpy(buffer, cmd_history[history_index]);
    buffer_index = strlen(cmd_history[history_index]);
}

void update_shell(void) {
    if (USART_DataAvailable()) {  
        char c = USART_Receive();
        static char prev1 = 0, prev2 = 0;
        
        // Check for arrow keys first
        if (prev1 == 0x1B && prev2 == '[') {
            if (c == 'A') {
                handle_up_arrow();
                prev1 = prev2 = 0;
                return;  // Skip normal processing
            }
            else if (c == 'B') {
                handle_down_arrow();
                prev1 = prev2 = 0;
                return;  // Skip normal processing
            }
        }
        
        // Update the detection buffer
        prev1 = prev2;
        prev2 = c;
        
        //Enter pressed
        if (c == '\r' || c == '\n') {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0'; 
                line_ready = 1;
            }
        }

        //Backspace pressed
        else if (c == 8 || c == 127) {
            if (buffer_index > 0) {
                buffer_index--;
                USART_Transmit('\b'); 
                USART_Transmit(' ');       
                USART_Transmit('\b'); 
            }
        }

        //Normal key pressed
        else if (buffer_index < (BUFFER_LENGTH - 1)) {
            buffer[buffer_index++] = c;
            USART_Transmit(c);
        }
        
        if (line_ready) {
            USART_Transmit('\r');
            USART_Transmit('\n');
            
          
            if (history_count < HISTORY_SIZE) {
                strncpy(cmd_history[history_count], buffer, sizeof(cmd_history[0]) - 1);
                cmd_history[history_count][sizeof(cmd_history[0]) - 1] = '\0';
                history_count++;
            } else {
                for (int i = 0; i < HISTORY_SIZE - 1; i++) {
                    strcpy(cmd_history[i], cmd_history[i + 1]);
                }
                strncpy(cmd_history[HISTORY_SIZE - 1], buffer, sizeof(cmd_history[0]) - 1);
                cmd_history[HISTORY_SIZE - 1][sizeof(cmd_history[0]) - 1] = '\0';
            }
            
            history_index = history_count;  

            
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
#include "shell.h"
#include "uart_driver.h"
#include <string.h>
#include <avr/io.h>
#include "command.h"
#include "commands/led.h"
#include "commands/help.h"
#include <stdio.h>
#include "input.h"
#include "history.h"
#include "display.h"

static char buffer[BUFFER_LENGTH];
static uint8_t buffer_index = 0;
static uint8_t line_ready = 0;


/* ============================================================================
 * COMMAND PROCESSING
 * ========================================================================== */

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


/* ============================================================================
 * ARROW KEY HANDLERS
 * ========================================================================== */

static void handle_up_arrow(void) {
    history_navigate_up(buffer, &buffer_index);
    display_history_command(buffer);
}

static void handle_down_arrow(void) {
    history_navigate_down(buffer, &buffer_index);
    display_history_command(buffer);
}


/* ============================================================================
 * INITIALIZATION
 * ========================================================================== */

void shell_init(void) {
    register_led_command();
    register_help_command();
    history_init();
    DDRB |= (1 << DDB5);  // For built-in Arduino LED
    display_line("ATmega328P UART shell initialized.");
    display_prompt();
}


/* ============================================================================
 * MAIN POLLING LOOP
 * ========================================================================== */

void shell_poll(void) {
    if (USART_DataAvailable()) {  
        char c = USART_Receive();
        static char prev1 = 0, prev2 = 0;
        
        // Check for arrow keys (ESC [ A/B sequences)
        if (prev1 == 0x1B && prev2 == '[') {
            if (c == 'A') {
                handle_up_arrow();
                prev1 = prev2 = 0;
                return;
            }
            else if (c == 'B') {
                handle_down_arrow();
                prev1 = prev2 = 0;
                return;
            }
        }
        
        // Update escape sequence detection buffer
        prev1 = prev2;
        prev2 = c;
        
        // Handle regular key input
        handle_key_pressed(c, &buffer_index, buffer, &line_ready);
        
        if (line_ready) {
            USART_Transmit('\r');
            USART_Transmit('\n');
            
            // Store command in history
            history_add(buffer);
            history_reset_index();
            
            // Parse command into argc/argv
            char *argv[10];
            int argc = 0;
            
            char *token = strtok(buffer, " ");
            while (token != NULL && argc < 10) {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            
            // Execute command
            if (argc > 0) {
                process_command(argc, argv); 
            }
            
            display_prompt();
            line_ready = 0;
            buffer_index = 0;
        }
    }
}
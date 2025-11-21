#include "command.h"
#include "shell.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 


// Helper function for case-insensitive comparison
static int str_equal(const char *a, const char *b) {
    return strcasecmp(a, b) == 0;
}

// Validation: Check if command syntax is correct
static int validate_led(int argc, char **argv) {
    // argv[0] is "led", so we check arguments starting from argv[1]
    
    if (argc == 2) {
        // "led on" or "led off" - exactly 2 arguments total
        return str_equal(argv[1], "on") || str_equal(argv[1], "off");
    }
    else if (argc == 3) {
        // "led blink 5" - exactly 3 arguments total
        // Check: argv[1] must be "blink", argv[2] must be a number
        if (!str_equal(argv[1], "blink")) return 0;
        
        // Check if argv[2] is a positive number
        for (int i = 0; argv[2][i] != '\0'; i++) {
            if (argv[2][i] < '0' || argv[2][i] > '9') return 0;
        }
        return 1;
    }
    return 0; // Wrong number of arguments
}

// Execution: Actually perform the LED action
static void execute_led(int argc, char **argv) {
    if (argc == 2) {
        // "led on" or "led off"
        if (str_equal(argv[1], "on")) {
            PORTB |= (1 << PORTB5);  // Turn LED on
            display_line("LED turned ON");
        } else {
            PORTB &= ~(1 << PORTB5); // Turn LED off
            display_line("LED turned OFF");
        }
    }
    else if (argc == 3) {
        // "led blink 5"
        int blink_count = atoi(argv[2]);  // Convert "5" to number 5
        
        for (int i = 0; i < blink_count; i++) {
            PORTB |= (1 << PORTB5);   // LED on
            _delay_ms(200);
            PORTB &= ~(1 << PORTB5);  // LED off
            _delay_ms(200);
        }
        
        char message[32];
        snprintf(message, sizeof(message), "LED blinked %d times", blink_count);
        display_line(message);
    }
}

// Command definition
static const command_def_t led_command = {
    .name = "led",
    .help = "led [on|off|blink N] - Control built-in LED",
    .validate = validate_led,
    .execute = execute_led
};

// Registration function
void register_led_command(void) {
    register_command(&led_command);
}
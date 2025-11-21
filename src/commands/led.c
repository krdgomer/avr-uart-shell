#include "command.h"
#include "shell.h"
#include "led.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 



static int str_equal(const char *a, const char *b) {
    return strcasecmp(a, b) == 0;
}


static int validate(int argc, char **argv) {

    if (argc == 2) {
        return str_equal(argv[1], "on") || str_equal(argv[1], "off");
    }
    else if (argc == 3) {
        if (!str_equal(argv[1], "blink")) return 0;
        
        for (int i = 0; argv[2][i] != '\0'; i++) {
            if (argv[2][i] < '0' || argv[2][i] > '9') return 0;
        }
        return 1;
    }
    return 0; 
}

static void execute(int argc, char **argv) {
    if (argc == 2) {
        if (str_equal(argv[1], "on")) {
            PORTB |= (1 << PORTB5);  // Turn LED on
            display_line("LED turned ON");
        } else {
            PORTB &= ~(1 << PORTB5); // Turn LED off
            display_line("LED turned OFF");
        }
    }
    else if (argc == 3) {
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

static const command_def_t led_command = {
    .name = "led",
    .help = "led [on|off|blink N] - Control built-in LED",
    .validate = validate,
    .execute = execute
};

void register_led_command(void) {
    register_command(&led_command);
}
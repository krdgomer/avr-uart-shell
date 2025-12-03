#include "command.h"
#include "shell.h" 
#include "help.h"
#include <stdio.h>

static int validate(int argc, char **argv) {
    return (argc == 1 || argc == 2);
}

static void execute(int argc, char **argv) {
    if (argc == 1) {

        display_line("Available commands:\r\n");
        
        for (int i = 0; i < command_count; i++) {
            char line[64];
            snprintf(line, sizeof(line), "  %s\r\n", command_table[i].name);
            display_line(line);
        }
        display_line("Use 'help <command>' for more info");
    }
    else if (argc == 2) {
        command_def_t *cmd = find_command(argv[1]);
        if (cmd) {
            display_line(cmd->help);
        } else {
            char msg[64];
            snprintf(msg, sizeof(msg), "Unknown command: %s", argv[1]);
            display_line(msg);
        }
    }
}

static const command_def_t help_command = {
    .name = "help",
    .help = "help [command] - Show available commands or command help",
    .validate = validate,
    .execute = execute
};

void register_help_command(void) {
    register_command(&help_command);
}
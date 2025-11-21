#include "command.h"
#include <stddef.h>
#include <string.h>

#define MAX_COMMANDS 20
command_def_t command_table[MAX_COMMANDS];
int command_count = 0;

void register_command(const command_def_t *command) {
    if (command_count < MAX_COMMANDS) {
        command_table[command_count++] = *command;
    }
}

command_def_t *find_command(const char *name) {
    for (int i = 0; i < command_count; i++) {
        if (strcasecmp(command_table[i].name, name) == 0) {
            return &command_table[i];
        }
    }
    return NULL;
}
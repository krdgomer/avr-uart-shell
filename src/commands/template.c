/*
    Example command template for AVR UART shell.
    Copy and modify this file to create new commands.
*/

#include "command.h"

// Validate function: checks if the arguments are valid for this command.
// Return 1 if valid, 0 if invalid.
static int validate(int argc, char **argv) {

    if (argc == 2) {
        // Example: validate for a single argument after the command
        // e.g., "command arg"
        // Add your validation logic here
    }
    else if (argc == 3) {
        // Example: validate for two arguments after the command
        // e.g., "command arg1 arg2"
        // Add your validation logic here
    }
    // Return 0 if arguments do not match expected patterns
    return 0; 
}

// Execute function: performs the command's action.
// argc: number of arguments, argv: argument strings.
static void execute(int argc, char **argv) {
    if (argc == 2) {
        // Handle the case for one argument after the command
        // e.g., perform action with argv[1]
    }
    else if (argc == 3) {
        // Handle the case for two arguments after the command
        // e.g., perform action with argv[1] and argv[2]
    }
    // Add more cases as needed
}

// Command definition structure.
// .name: command string to type in shell
// .help: help text shown in shell
// .validate: pointer to validate function
// .execute: pointer to execute function
static const command_def_t template_command = {
    .name = "command",           // Change this to your command name
    .help = "sample command",    // Change this to your help text
    .validate = validate,
    .execute = execute
};

// Registration function: call this in your shell init to register the command.
void register_template_command(void) {
    register_command(&template_command);
}
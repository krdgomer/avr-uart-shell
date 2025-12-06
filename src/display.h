#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * Display the shell prompt (> character with newline)
 */
void display_prompt(void);

/**
 * Display a string to the user
 */
void display_line(const char* str);

/**
 * Clear the current line using ANSI escape sequence
 */
void display_clear_line(void);

/**
 * Display a command from history (used by arrow key handlers)
 */
void display_history_command(const char *cmd);

#endif
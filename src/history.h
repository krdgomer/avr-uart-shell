#ifndef HISTORY_H
#define HISTORY_H

#include <stdint.h>

#define HISTORY_SIZE 10
/**
 * Initialize the command history system
 */
void history_init(void);

/**
 * Add a command to the history
 */
void history_add(const char *cmd);

/**
 * Get command at index in history
 */
char* history_get(uint8_t index);

/**
 * Get total number of commands in history
 */
uint8_t history_get_count(void);

/**
 * Navigate up in history and restore command to buffer
 */
void history_navigate_up(char *buffer, uint8_t *buffer_index);

/**
 * Navigate down in history and restore command to buffer
 */
void history_navigate_down(char *buffer, uint8_t *buffer_index);

/**
 * Reset history index (call when a new command is entered)
 */
void history_reset_index(void);

#endif
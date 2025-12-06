#include "history.h"
#include <string.h>
#include "uart_driver.h"

#define HISTORY_CMD_SIZE 25

static char cmd_history[HISTORY_SIZE][HISTORY_CMD_SIZE];
static uint8_t history_index = 0;
static uint8_t history_count = 0;

void history_init(void) {
    memset(cmd_history, 0, sizeof(cmd_history));
    history_index = 0;
    history_count = 0;
}

void history_add(const char *cmd) {
    if (history_count < HISTORY_SIZE) {
        strncpy(cmd_history[history_count], cmd, HISTORY_CMD_SIZE - 1);
        cmd_history[history_count][HISTORY_CMD_SIZE - 1] = '\0';
        history_count++;
    } else {
        // Shift history up and add new command at the end
        for (int i = 0; i < HISTORY_SIZE - 1; i++) {
            strcpy(cmd_history[i], cmd_history[i + 1]);
        }
        strncpy(cmd_history[HISTORY_SIZE - 1], cmd, HISTORY_CMD_SIZE - 1);
        cmd_history[HISTORY_SIZE - 1][HISTORY_CMD_SIZE - 1] = '\0';
    }
}

char* history_get(uint8_t index) {
    if (index < history_count) {
        return cmd_history[index];
    }
    return "";
}

uint8_t history_get_count(void) {
    return history_count;
}

void history_navigate_up(char *buffer, uint8_t *buffer_index) {
    if (history_count == 0) return;
    
    if (history_index < history_count - 1) {
        history_index++;
    } else {
        history_index = 0;
    }
    
    strcpy(buffer, cmd_history[history_index]);
    *buffer_index = strlen(cmd_history[history_index]);
}

void history_navigate_down(char *buffer, uint8_t *buffer_index) {
    if (history_count == 0) return;
    
    if (history_index > 0) {
        history_index--;
    } else {
        history_index = history_count - 1;
    }
    
    strcpy(buffer, cmd_history[history_index]);
    *buffer_index = strlen(cmd_history[history_index]);
}

void history_reset_index(void) {
    history_index = history_count;
}
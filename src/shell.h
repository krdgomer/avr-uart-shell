#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

#define BUFFER_LENGTH 128

// Function declarations only
void init_shell(void);
void update_shell(void);
void display_line(const char* str);  

#endif
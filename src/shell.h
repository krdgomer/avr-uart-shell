#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

#define BUFFER_LENGTH 128

void shell_init(void);
void shell_poll(void);
void display_line(const char* str);  

#endif
#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
    const char* name;
    const char* help;
    int (*validate)(int argc, char **argv);
    void (*execute)(int argc, char **argv);
} command_def_t;

// Registry functions
void register_command(const command_def_t *command);
command_def_t *find_command(const char *name);
void list_commands(void);

extern command_def_t command_table[]; 
extern int command_count;              

// For internal use only
typedef struct {
    const command_def_t *commands;
    int count;
    int capacity;
} command_registry_t;

#endif
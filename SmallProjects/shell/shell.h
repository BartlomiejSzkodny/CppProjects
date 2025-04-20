#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>

// Function declarations
char *read_line(void);
char **split_line(char *line);
int number_of_builtins();
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int launch(char **args);
int execute(char **args);
void shell_loop(void);

// Extern declarations for shared variables
extern const char *builtin_str[];
extern int (*builtin_func[])(char **);

#endif // SHELL_H
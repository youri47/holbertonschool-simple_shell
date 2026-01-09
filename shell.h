#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void print_prompt(void);
char *parse_input(char *input);
int parse_arguments(char *input, char **argv);

int execute_builtin(char **argv);
int execute_command(char *input, char *prog, int line_num);

char *get_path_env(void);
char *find_command(char *command);

#endif

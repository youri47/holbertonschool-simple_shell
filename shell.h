#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT 1024

extern char **environ;

void print_prompt(void);
ssize_t read_input(char *buffer, size_t size);
char *parse_input(char *input);
int parse_arguments(char *input, char **argv);

void execute_command(char *input, char *prog, int line_num);
void run_child_process(char *command_path, char **argv, char *prog);

char *find_command(char *command);
char *get_path_env(void);

int execute_builtin(char **argv);
int builtin_exit(char **argv);
int builtin_env(char **argv);

#endif

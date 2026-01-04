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

/* Fonctions principales */
void display_prompt(int interactive);
ssize_t read_command(char **line, size_t *len);
void execute_command(char *input);

/* Fonctions d'exécution */
void run_child_process(char *command_path, char **argv);
int parse_arguments(char *input, char **argv);
int execute_builtin(char **argv);

/* Fonctions PATH */
char *get_path_env(void);
char *find_command(char *command);

#endif /* SHELL_H */

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
void display_prompt(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);

/* Fonctions PATH */
char *get_path_env(void);
char *find_command(char *command);

/* Fonctions utilitaires */
void free_args(char **args);

#endif /* SHELL_H */

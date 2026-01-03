#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

extern char **environ;

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#cisfun$ ", 9);
}
ssize_t read_input(char *buffer, size_t size)
{
    ssize_t n;

    n = getline(&buffer, &size, stdin);
    return (n);
}

char *parse_input(char *input)
{
    size_t len;

    if (input == NULL)
        return (NULL);

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';

    return (input);
}

void execute_command(char *command)
{
    pid_t pid;
    int status;
    char *argv[2];

    if (command == NULL || strlen(command) == 0)
        return;

    argv[0] = command;
    argv[1] = NULL;

    pid = fork();

    if (pid == -1)
    {
        perror("Error");
        return;
    }
    else if (pid == 0)
    {
        if (execve(command, argv, environ) == -1)
        {
            perror("./shell");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        
        wait(&status);
    }
}

int main(void)
{
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    while (1)
    {
        print_prompt();

        nread = getline(&input, &bufsize, stdin);

        if (nread == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        parse_input(input);

        if (strlen(input) == 0)
            continue;

        execute_command(input);
    }

    free(input);
    return (0);
}

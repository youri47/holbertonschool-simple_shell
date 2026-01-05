#include "shell.h"

/**
 * run_child_process - Runs command in child process
 * @command_path: Full path to the command
 * @argv: Array of arguments
 */
void run_child_process(char *command_path, char **argv)
{
	if (execve(command_path, argv, environ) == -1)
	{
		perror("./shell");
		if (command_path != argv[0])
			free(command_path);
		exit(EXIT_FAILURE);
	}
}

/**
 * parse_arguments - Parse input string into arguments array
 * @input: The input string to parse
 * @argv: Array to store arguments
 *
 * Return: Number of arguments parsed
 */
int parse_arguments(char *input, char **argv)
{
	int argc = 0;
	char *token;

	token = strtok(input, " \t\n");
	while (token != NULL && argc < 1023)
	{
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;

	return (argc);
}

/**
 * execute_builtin - Check and execute builtin commands
 * @argv: Array of arguments
 *
 * Return: 1 if exit, 0 if not a builtin, -1 to continue
 */
int execute_builtin(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
		return (1);
	if (strcmp(argv[0], "env") == 0)
	{
		int i = 0;

		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (-1);
	}
	return (0);
}

/**
 * execute_command - Executes a command using execve
 * @input: The input string containing command and arguments
 */
void execute_command(char *input)
{
	pid_t pid;
	int status, builtin_result;
	char *argv[1024];
	char *command_path;
	int argc;

	if (input == NULL || strlen(input) == 0)
		return;

	argc = parse_arguments(input, argv);
	if (argc == 0)
		return;

	builtin_result = execute_builtin(argv);
	if (builtin_result == 1)
		exit(0);
	else if (builtin_result == -1)
		return;

	command_path = find_command(argv[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "./shell: 1: %s: not found\n", argv[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		if (command_path != argv[0])
			free(command_path);
		return;
	}
	else if (pid == 0)
	{
		run_child_process(command_path, argv);
	}
	else
	{
		wait(&status);
		if (command_path != argv[0])
			free(command_path);
	}
}

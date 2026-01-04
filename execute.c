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
	else if (builtin_result == 0)
		return;
	command_path = find_command(argv[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
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
		run_child_process(command_path, argv);
	else
	{
		wait(&status);
		if (command_path != argv[0])
			free(command_path);
	}
}

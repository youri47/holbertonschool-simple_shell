#include "shell.h"

/**
 * free_command_path - Frees command path if allocated
 * @command_path: Path returned by find_command
 * @argv: Arguments array
 */
static void free_command_path(char *command_path, char **argv)
{
	if (command_path != NULL && command_path != argv[0])
		free(command_path);
}

/**
 * run_child_process - Runs command in child process
 * @command_path: Full path to the command
 * @argv: Array of arguments
 * @prog: Program name (argv[0])
 */
void run_child_process(char *command_path, char **argv, char *prog)
{
	if (execve(command_path, argv, environ) == -1)
	{
		perror(prog);
		exit(EXIT_FAILURE);
	}
}

/**
 * fork_and_execute - Forks and executes a command
 * @command_path: Full path to the command
 * @argv: Array of arguments
 * @prog: Program name (argv[0])
 */
static void fork_and_execute(char *command_path, char **argv, char *prog)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return;
	}

	if (pid == 0)
		run_child_process(command_path, argv, prog);

	wait(&status);
}

/**
 * execute_command - Executes a command using execve
 * @input: The input string containing command and arguments
 * @prog: Program name (argv[0])
 * @line_num: Line counter
 */
void execute_command(char *input, char *prog, int line_num)
{
	int builtin_result, argc;
	char *argv[1024];
	char *command_path;

	if (input == NULL || input[0] == '\0')
		return;

	argc = parse_arguments(input, argv);
	if (argc == 0)
		return;

	builtin_result = execute_builtin(argv);
	if (builtin_result == 1)
		exit(0);
	if (builtin_result == 0)
		return;

	command_path = find_command(argv[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, line_num, argv[0]);
		return;
	}

	fork_and_execute(command_path, argv, prog);
	free_command_path(command_path, argv);
}

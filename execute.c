#include "shell.h"

/**
 * run_child - exec command in child
 * @path: full command path
 * @argv: args
 * @prog: program name for perror
 */
static void run_child(char *path, char **argv, char *prog)
{
	execve(path, argv, environ);
	perror(prog);
	exit(EXIT_FAILURE);
}

/**
 * execute_command - parse, builtin, PATH, fork/exec
 * @input: input line (modified by strtok)
 * @prog: argv[0] for error display
 * @line_num: line counter for error display
 *
 * Return: 1 if exit requested, 0 otherwise
 */
int execute_command(char *input, char *prog, int line_num)
{
	char *argv[1024];
	char *path;
	pid_t pid;
	int status, argc, b;

	argc = parse_arguments(input, argv);
	if (argc == 0)
		return (0);

	b = execute_builtin(argv);
	if (b == 1)
		return (1);
	if (b == 0)
		return (0);

	path = find_command(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, line_num, argv[0]);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		if (path != argv[0])
			free(path);
		return (0);
	}

	if (pid == 0)
		run_child(path, argv, prog);

	wait(&status);

	if (path != argv[0])
		free(path);

	return (0);
}

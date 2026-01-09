#include "shell.h"

/**
 * execute_command - parses and executes a command
 * Return: 1 if exit requested, 0 otherwise
 */
int execute_command(char *input, char *prog, int line_num)
{
	char *argv[1024];
	char *path;
	pid_t pid;
	int status, argc;

	argc = parse_arguments(input, argv);
	if (argc == 0)
		return (0);

	/* BUILTINS FIRST */
	if (strcmp(argv[0], "exit") == 0)
		return (1);

	if (strcmp(argv[0], "env") == 0)
	{
		int i;

		for (i = 0; environ[i]; i++)
		{
			write(1, environ[i], strlen(environ[i]));
			write(1, "\n", 1);
		}
		return (0);
	}

	/* PATH RESOLUTION BEFORE FORK */
	path = find_command(argv[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog, line_num, argv[0]);
		return (0);
	}

	/* ONLY NOW WE FORK */
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, environ);
		perror(prog);
		exit(EXIT_FAILURE);
	}
	wait(&status);

	if (path != argv[0])
		free(path);

	return (0);
}

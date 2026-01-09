#include "shell.h"

/**
 * builtin_exit - exits the shell
 * @argv: arguments (unused)
 *
 * Return: 1 to indicate shell should exit
 */
int builtin_exit(char **argv)
{
	(void)argv;
	return (1);
}

/**
 * builtin_env - prints the current environment
 * @argv: arguments (unused)
 *
 * Return: 0 to indicate shell should continue
 */
int builtin_env(char **argv)
{
	int i;

	(void)argv;
	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * execute_builtin - executes a builtin command if it exists
 * @argv: array of arguments
 *
 * Return: 1 if shell should exit, 0 if builtin executed, -1 if not builtin
 */
int execute_builtin(char **argv)
{
	if (argv[0] == NULL)
		return (-1);

	if (strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));

	if (strcmp(argv[0], "env") == 0)
		return (builtin_env(argv));

	return (-1);
}

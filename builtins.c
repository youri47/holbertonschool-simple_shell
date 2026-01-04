#include "shell.h"

/**
 * builtin_exit - Exits the shell
 * @argv: Array of arguments (unused)
 *
 * Return: 1 to indicate shell should exit
 */
int builtin_exit(char **argv)
{
	(void)argv;
	return (1);
}

/**
 * execute_builtin - Executes a builtin command if it exists
 * @argv: Array of arguments
 *
 * Return: 1 if builtin was executed and shell should exit,
 *         0 if builtin was executed and shell should continue,
 *         -1 if not a builtin
 */
int execute_builtin(char **argv)
{
	if (argv[0] == NULL)
		return (-1);

	if (strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));

	return (-1);
}

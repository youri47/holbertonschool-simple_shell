#include "shell.h"

/**
 * execute_builtin - handle built-in commands
 * @argv: arguments array
 *
 * Return: 1 if exit requested, 0 if builtin executed, -1 if not builtin
 */
int execute_builtin(char **argv)
{
	int i;

	if (argv == NULL || argv[0] == NULL)
		return (-1);

	if (strcmp(argv[0], "exit") == 0)
		return (1);

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}

	return (-1);
}

#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 (Success)
 */
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
			/* Handle EOF (Ctrl+D) */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		parse_input(input);

		/* Skip empty lines */
		if (strlen(input) == 0)
			continue;

		execute_command(input);
	}

	free(input);
	return (0);
}

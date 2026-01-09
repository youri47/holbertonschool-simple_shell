#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t nread;
	int line_num = 0;

	(void)ac;

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

		line_num++;
		parse_input(input);

		if (strlen(input) == 0)
			continue;

		execute_command(input, av[0], line_num);
	}

	free(input);
	return (0);
}

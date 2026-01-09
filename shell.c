#include "shell.h"

/**
 * main - simple shell main loop
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t nread;
	int line_num = 0;
	int interactive;

	(void)ac;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		nread = getline(&input, &size, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_num++;
		parse_input(input);

		if (input[0] == '\0')
			continue;

		if (execute_command(input, av[0], line_num) == 1)
			break;
	}

	free(input);
	return (0);
}

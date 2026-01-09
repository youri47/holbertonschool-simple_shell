#include "shell.h"

/**
 * main - shell loop
 */
int main(int ac, char **av)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t nread;
	int line_num = 0;

	(void)ac;

	while (1)
	{
		print_prompt();

		nread = getline(&input, &size, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_num++;
		parse_input(input);

		if (input[0] == '\0')
			continue;

		if (execute_command(input, av[0], line_num))
			break;
	}

	free(input);
	return (0);
}

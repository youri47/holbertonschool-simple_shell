#include "shell.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}
}

/**
 * parse_input - Removes newline character from input
 * @input: The input string to parse
 *
 * Return: Pointer to the parsed string
 */
char *parse_input(char *input)
{
	size_t len;

	if (input == NULL)
		return (NULL);

	len = strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';

	return (input);
}

/**
 * parse_arguments - Parses input into command and arguments
 * @input: The input string to parse
 * @argv: Array to store the parsed arguments
 *
 * Return: Number of arguments parsed
 */
int parse_arguments(char *input, char **argv)
{
	int i = 0;
	char *token;

	if (input == NULL)
		return (0);

	token = strtok(input, " \t");
	while (token != NULL && i < 1023)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}

	argv[i] = NULL;
	return (i);
}

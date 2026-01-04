#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_line - Reads a line from stdin
 *
 * Return: The line read, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	/* Remove trailing newline */
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * parse_line - Parses a line into arguments
 * @line: The line to parse
 *
 * Return: Array of arguments, or NULL on failure
 */
char **parse_line(char *line)
{
	char **args = NULL;
	char *token;
	int count = 0, i = 0;
	char *line_copy;

	if (line == NULL || *line == '\0')
		return (NULL);

	/* First pass: count tokens */
	line_copy = strdup(line);
	if (line_copy == NULL)
		return (NULL);

	token = strtok(line_copy, " \t");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(line_copy);

	if (count == 0)
		return (NULL);

	/* Allocate args array */
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	/* Second pass: fill array */
	token = strtok(line, " \t");
	while (token != NULL)
	{
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			free_args(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	return (args);
}

/**
 * free_args - Frees an array of arguments
 * @args: The array to free
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments (command + args)
 *
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args == NULL || args[0] == NULL)
		return (1);

	/* Handle exit builtin */
	if (strcmp(args[0], "exit") == 0)
		return (0);

	/* Find the command path BEFORE forking */
	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	/* Fork only if command exists */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(args[0]);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}

	free(cmd_path);
	return (1);
}

/**
 * main - Entry point for simple shell
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		display_prompt();
		line = read_line();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (*line == '\0')
		{
			free(line);
			continue;
		}

		args = parse_line(line);
		free(line);

		if (args != NULL)
		{
			status = execute_command(args);
			free_args(args);
		}
	}

	return (0);
}

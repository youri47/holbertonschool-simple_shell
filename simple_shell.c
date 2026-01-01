#include "shell.h"

/**
 * main - Point d'entrée du simple shell
 *
 * Description: Shell basique sans arguments
 *
 * Return: Toujours 0 (succès)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *argv[2];
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
			fflush(stdout);
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror("./shell");
			continue;
		}

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./shell");
				exit(127);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Point d'entrée du simple shell
 *
 * Description: Crée un shell basique qui exécute des commandes simples
 *
 * Return: Toujours 0 (succès)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *argv[2];

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		pid = fork();

		if (pid == -1)
		{
			perror("Error");
			continue;
		}

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, NULL) == -1)
			{
				perror("Error");
				exit(EXIT_FAILURE);
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

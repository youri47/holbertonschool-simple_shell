#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

/**
 * display_prompt - Affiche le prompt du shell
 *
 * Return: void
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * remove_newline - Enlève le caractère newline d'une chaîne
 * @line: La chaîne à modifier
 * @length: La longueur de la chaîne
 *
 * Return: void
 */
void remove_newline(char *line, ssize_t length)
{
	if (line[length - 1] == '\n')
		line[length - 1] = '\0';
}

/**
 * parse_command - Découpe une commande en arguments
 * @line: La ligne de commande à découper
 * @argv: Tableau pour stocker les arguments
 *
 * Return: void
 */
void parse_command(char *line, char **argv)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t");

	while (token != NULL && i < MAX_ARGS - 1)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}

	argv[i] = NULL;
}

/**
 * execute_command - Exécute une commande avec ses arguments
 * @argv: Tableau d'arguments
 *
 * Return: void
 */
void execute_command(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
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

/**
 * main - Point d'entrée du simple shell
 *
 * Description: Shell qui exécute des commandes avec arguments
 *
 * Return: Toujours 0 (succès)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *argv[MAX_ARGS];

	while (1)
	{
		display_prompt();

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}

		remove_newline(line, read);

		if (strlen(line) == 0)
			continue;

		parse_command(line, argv);

		if (argv[0] != NULL)
			execute_command(argv);
	}

	free(line);
	return (0);
}

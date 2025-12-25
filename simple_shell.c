#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
 * execute_command - Exécute une commande
 * @command: La commande à exécuter
 *
 * Return: void
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();

	if (pid == -1)
	{
		perror("Error");
		return;
	}

	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, NULL) == -1)
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
 * Description: Crée un shell basique qui exécute des commandes simples
 *
 * Return: Toujours 0 (succès)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

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

		execute_command(line);
	}

	free(line);
	return (0);
}

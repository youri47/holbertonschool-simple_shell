#include "shell.h"

/**
 * display_prompt - Affiche le prompt du shell
 * @interactive: 1 si mode interactif, 0 sinon
 *
 * Return: void
 */
void display_prompt(int interactive)
{
	if (interactive)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}
}

/**
 * read_command - Lit une commande depuis l'entrée standard
 * @line: Pointeur vers la ligne à lire
 * @len: Pointeur vers la taille du buffer
 *
 * Return: Nombre de caractères lus, -1 en cas d'erreur
 */
ssize_t read_command(char **line, size_t *len)
{
	ssize_t nread;

	nread = getline(line, len, stdin);

	if (nread > 0 && (*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	return (nread);
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
		perror("./shell");
		return;
	}

	if (pid == 0)
	{
		argv[0] = command;
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
	int interactive;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		display_prompt(interactive);

		nread = read_command(&line, &len);

		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (strlen(line) > 0)
			execute_command(line);
	}

	free(line);
	return (0);
}

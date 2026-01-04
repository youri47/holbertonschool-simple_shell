#include "shell.h"

/**
 * get_path_env - Gets the PATH environment variable
 *
 * Return: Pointer to PATH string, or NULL if not found
 */
char *get_path_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_command - Finds the full path of a command
 * @command: The command to find
 *
 * Return: Full path to command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];
	struct stat st;

	if (command == NULL)
		return (NULL);

	/* If command contains '/', it's already a path */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = get_path_env();
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

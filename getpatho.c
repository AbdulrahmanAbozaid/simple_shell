#include "shell.h"

/**
 * _getpath - Get the path
 * @command: The command
 * Return: The
 */

char *_getpath(char *command)
{
	char *e_path, *fCmnd, *folder;
	struct stat st;
	int it = 0;

	for (it = 0; command[it]; it++)
	{
		if (command[it] == '/')
		{
			if (stat(command, &st) == 0)
				return (_strdup(command));
			return (NULL)
				;        }
	}
	e_path = _getenv("PATH");
	if (!e_path)
		return (NULL);
	folder = strtok(e_path, ":");
	while (folder)
	{
		fCmnd = malloc(_strlen(folder) + _strlen(command) + 2);
		if (fCmnd)
		{
			_strcpy(fCmnd, folder);
			_strcat(fCmnd, "/");
			_strcat(fCmnd, command);
			if (stat(fCmnd, &st) == 0)
			{
				free(e_path), e_path = NULL;
				return (fCmnd);
			}
			free(fCmnd), fCmnd = NULL;
			folder = strtok(NULL, ":");
		}
	}
	free(e_path), e_path = NULL;
	return (NULL);
}


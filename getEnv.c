#include "shell.h"

/**
 * _getenv - Get the environment variable
 * @name: The name of the environment variable
 * Return: The value of the environment variable
 */

char *_getenv(char *name)
{
	int i;
	char *tc = NULL, *key, *val, *value;

	for (i = 0; environ[i]; i++)
	{
		tc = _strdup(environ[i]);
		key = strtok(tc, "=");
		if (_strcmp(key, name) == 0)
		{
			val = strtok(NULL, "\n");
			value = _strdup(val);
			free(tc), tc = NULL;
			return (value);
		}
		free(tc), tc = NULL;
	}
	return (NULL);
}

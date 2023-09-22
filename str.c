#include "shell.h"

/**
 * splitto - Convert
 * @ln: line number
 * Return: sf
 */

char **splitto(char *ln)
{
	int ctr = 0;
	char *token = NULL, *tl = NULL;
	char **command = NULL;

	if (!ln)
		return (NULL);
	tl = _strdup(ln);
	token = strtok(tl, DELIMS);
	if (!token)
	{
		free(tl), tl = NULL;
		free(ln), ln = NULL;
		return (NULL);
	}
	while (token)
	{
		ctr++;
		token = strtok(NULL, DELIMS);
	}
	free(tl), tl = NULL;
	command = malloc(sizeof(char *) * (ctr + 1));
	if (!command)
	{
		free(ln), ln = NULL;
		return (NULL);
	}
	token = strtok(ln, DELIMS);
	ctr = 0;
	while (token)
	{
		command[ctr] = _strdup(token);
		token = strtok(NULL, DELIMS);
		ctr++;
	}
	free(ln), ln = NULL;
	command[ctr] = NULL;
	return (command);
}


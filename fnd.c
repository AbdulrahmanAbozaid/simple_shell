#include "shell.h"

/**
 * _strlen - len
 * @s: string
 * Return: int
 */

int _strlen(char *s)
{
	int ctr = 0;
	
	if (!s)
		return (ctr);
	while (*s++)
		ctr++;
	return (ctr);
}

/**
 * _strdup - strdup
 * @src: string
 * Return: string
 */
char *_strdup(const char *src)
{
	int len = 0;
	char *dest;

	if (src == NULL)
		return (NULL);
	while (*src++)
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	for (len++; len--;)
		dest[len] = *--src;
	return (dest);
}


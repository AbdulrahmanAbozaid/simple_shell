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
 * _strcmp - strcmp
 * @s1: string
 * @s2: string
 * Return: string
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s2++;
		s1++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_by - start
 * @src: src
 * @needle: need
 *
 * Return: add
 */

char *start_by(const char *src, const char *needle)
{
	while (*needle)
		if (*needle++ != *src++)
			return (NULL);
	return ((char *)src);
}

/**
 * _strcat - cat
 * @dest: se
 * @src: f
 * Return: char*
 */

char *_strcat(char *dest, char *src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (tmp);
}

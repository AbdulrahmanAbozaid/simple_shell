#include "shell.h"

/**
 * _strncpy - String
 * @dest: Destination
 * @src: Source
 * @n: num
 * Return: String
 */

char *_strncpy(char *dest, char *src, int n)
{
	int index;

	for (index = 0; src[index] != '\0' && index < n; index++)
		dest[index] = src[index];
	while (index < n)
	{
		dest[index] = '\0';
		index++;
	}
	return (dest);
}

/**
 * _strncat - String
 * @dest: Destination
 * @src: Source
 * @n: num to append to destination
 * Return: String
 */

char *_strncat(char *dest, char *src, int n)
{
	int len = 0, append;

	while (dest[len])
		len++;
	for (append = 0; append < n && src[append] != '\0'; ++append)
		dest[len + append] = src[append];
	dest[len + append] = '\0';
	return (dest);
}

/**
 * _strchr - find char
 * @str: str
 * @c: char
 * Return: chra
 */

char *_strchr(char *str, char c)
{
	do
	{
		if (*str == c)
		{
			return (str);
		}
	} while (*str++);
	return (NULL);
}

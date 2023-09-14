#include "shell.h"

/**
 * _strcpy - strcpy
 * @dest: string
 * @src: string
 * Return: string
 */

char *_strcpy(char *dest, char *src)
{
	int ind = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[ind])
	{
		dest[ind] = src[ind];
		ind++;
	}
	dest[ind] = '\0';
	return (dest);
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
	return dest;
}

/**
 * _puts - prints a string
 * @str: str
 * Return: void
 */

void _puts(char *str)
{
	int ind = 0;

	if (!str)
		return;
	while (str[ind] != '\0')
	{
		_putchar(str[ind]);
		ind++;
	}
}

/**
 * _putchar - print char
 * @c: char
 * Return: num
 */

int _putchar(char c)
{
	static int ind = 0;
	static char str[MAX_BUF_SIZE];

	if (c == BUF_FLUSH || ind >= MAX_BUF_SIZE)
	{
		write(STDOUT_FILENO, str, ind);
		ind = 0;
	}
	if (c != BUF_FLUSH)
		str[ind++] = c;
	return (1);
}

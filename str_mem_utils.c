#include "shell.h"

/**
 * isActive - interactive
 * @inf: the current state of the application
 * Return: true if the application
 */

int isActive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - if char is not a delimiter
 * @c: the current state of the application
 * @delimiter: the delimiter
 * Return: true if the
 */

int is_delim(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter++ == c)
			return (1);
	}
	return (0);
}

/**
 * _atoi - if char is not a string literal
 * @str: the string
 * Return: the index of the first occurrence
 */

int _atoi(char *str)
{
	int ind, sign = 1, cont = 0;
	unsigned int num = 0;

	for (ind = 0; str[ind] != '\0' && cont != 2; ind++)
	{
		if (str[ind] == '-')
			sign *= -1;
		if (str[ind] >= '0' && str[ind] <= '9')
		{
			cont = 1;
			num *= 10;
			num += (str[ind] - '0');
		}
		else
			cont = 2;
	}
	if (sign == -1)
		return (-1 * num);
	else
		return (num);
}

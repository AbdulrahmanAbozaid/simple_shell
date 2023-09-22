#include "shell.h"

/**
 * isPos - returns true if
 * @s:  the string
 * Return: true if the string
 */

int isPos(char *s)
{
	int it;

	if (!s)
        return (0);
	for (it = 0; s[it]; it++)
	{
		if (s[it] < '0' || s[it] > '9')
			return (0);
	}
	return (1);
}

/**
 * _atoi_c - returns the number of characters
 * @s: the string
 * Return: the number of characters
 */

int _atoi_c(char *s)
{
	int it, res = 0;

	for (it = 0; s[it]; it++)
	{
		res *= 10;
		res += (s[it] - '0');
	}
	return (res);
}


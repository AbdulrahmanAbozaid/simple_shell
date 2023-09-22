#include "shell.h"

/**
 * readLine - read a line
 * Return:  line number
 */

char *readLine(void)
{
	char *lin = NULL;
	size_t len = 0;
	ssize_t s;

	s = getline(&lin, &len, stdin);
	if (s == -1)
	{
		free(lin);
		return (NULL);
	}
	return (lin);
}

/**
 * putError - put error
 * @name: name of error
 * @cmnd: error code
 * @idx: index of error
 * Return: error code
 */

void putError(char *name, char *cmnd, int idx)
{
	char *indx, msg[] = ": not found\n";

	indx = _itoa_c(idx);
	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, indx, _strlen(indx));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmnd, _strlen(cmnd));
	write(STDERR_FILENO, msg, _strlen(msg));
	free(indx);
}

/**
 * _itoa - convert string to unsigned
 * @num: number of bytes
 * Return: number of bytes
 */

char *_itoa_c(int num)
{
	int i = 0;
	char buf[20];

	if (num == 0)
		buf[i++] = '0';
	else
	{
		while (num > 0)
		{
			buf[i++] = (num % 10) + '0';
			num /= 10;
		}
	}

	buf[i] = '\0';
	revStr(buf, i);
	return (_strdup(buf));
}

/**
 * revStr - convert string to unsigned
 * @s: string
 * @l: number of bytes
 * Return: number of bytes
 */

void revStr(char *s, int l)
{
	char tc;
	int st = 0;
	int en = l - 1;

	while (st < en)
	{
		tc = s[st];
		s[st] = s[en];
		s[en] = tc;

		st++;
		en--;
	}
}


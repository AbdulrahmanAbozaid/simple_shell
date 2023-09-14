#include "shell.h"

/**
 * _eputs - prints a string
 * @str: str
 * Return: void
 */

void _eputs(char *str)
{
	int ind = 0;

	if (!str)
		return;
	while (str[ind] != '\0')
	{
		_eputchar(str[ind]);
		ind++;
	}
}

/**
 * _eputchar - print char
 * @c: char
 * Return: num
 */

int _eputchar(char c)
{
	static int ind;
	static char str[MAX_BUF_SIZE];

	if (c == BUF_FLUSH || ind >= MAX_BUF_SIZE)
	{
		write(STDERR_FILENO, str, ind);
		ind = 0;
	}
	if (c != BUF_FLUSH)
		str[ind++] = c;
	return (1);
}

/**
 * putchFD - put a file descriptor into the buffer
 * @ch: the buffer
 * @fd: the file descriptor
 * Return: the number of bytes written
 */

/* _putfd */
int putchFD(char ch, int fd)
{
	static int ind;
	static char str[MAX_BUF_SIZE];

	if (ch == BUF_FLUSH || ind >= MAX_BUF_SIZE)
	{
		write(fd, str, ind);
		ind = 0;
	}
	if (ch != BUF_FLUSH)
		str[ind++] = ch;
	return (1);
}

/**
 * _putsFD - prints a string
 * @str: str
 * @fd: file    descriptor
 * Return: void
 */

/* _putsfd */
int _putsFD(char *str, int fd)
{
	int ind = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ind += putchFD(*str++, fd);
	}
	return (ind);
}

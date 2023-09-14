#include "shell.h"

/**
 * _erratoi - Convert a string to an integer value
 * @src: the string to convert
 * Return: the integer value
 */

int _erratoi(char *src)
{
	unsigned long int val;
	int num = 0;

	if (*src == '+')
		src++;
	for (num = 0; src[num] != '\0'; num++)
	{
		if (src[num] >= '0' && src[num] <= '9')
		{
			val *= 10;
			val += (src[num] - '0');
			if (val > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (val);
}

/**
 * put_err - print a string
 * @inf: inflate
 * @errstr: inflate
 * Return: 0 if successful
 */

void put_err(info_t *inf, char *errstr)
{
	_eputs(inf->file_path);
	_eputs(": ");
	print_dec(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_dec - print a number
 * @sin: inflate
 * @fdc: inflate
 * Return: 0 if successful
 */

int print_dec(int sin, int fdc)
{
	unsigned int abs_val, curr_val;
	int ctr = 0, it = 0;
	int (*func)(char) = _putchar;

	if (fdc == STDERR_FILENO)
		func = _eputchar;
	if (sin < 0)
	{
		abs_val = -sin;
		func('-');
		ctr++;
	}
	else
		abs_val = sin;
	curr_val = abs_val;
	for (it = 1000000000; it > 1; it /= 10)
	{
		if (abs_val / it)
		{
			func('0' + curr_val / it);
			ctr++;
		}
		curr_val %= it;
	}
	func('0' + curr_val);
	ctr++;
	return (ctr);
}

/**
 * convert_radix - convert radix
 * @num: number
 * @radix: radix
 * @flags: flags
 * Return: the number of
 */

char *convert_radix(long int num, int radix, int flags)
{
	static char *radices;
	static char result[50];
	char sign = 0;
	char *pres = &result[49];
	unsigned long tmp = num;

	if (!(flags & FLAG_UNSIGNED) && num < 0)
	{
		tmp = -num;
		sign = '-';
	}
	radices = flags & FLAG_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	*pres = '\0';
	do {
		*--pres = radices[tmp % radix];
		tmp /= radix;
	} while (tmp);
	if (sign)
		*--pres = sign;
	return (pres);
}

/**
 * rmv_cmnt - rmv_cmnt
 * @str: the name of the
 * Return: 0
 */

void rmv_cmnt(char *str)
{
	int indx;

	for (indx = 0; str[indx] != '\0'; indx++)
		if (str[indx] == '#' && (!indx || str[indx - 1] == ' '))
		{
			str[indx] = '\0';
			break;
		}
}

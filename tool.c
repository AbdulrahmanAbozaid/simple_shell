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


/**
 * replaceString - replace a string with a new string (replace_string)
 * @f: the string to be replaced
 * @s: the string to be replaced
 * Return: s the new string
 */

int replaceString(char **f, char *s)
{
	free(*f), *f = NULL;
	*f = s;
	return (1);
}

/**
 * rep_stpp - rep a string
 * @cmnd: the string to be rep
 * @status: the status
 * Return: success [1], else [0]
 */
int rep_stpp(char **cmnd, int status)
{
	int i = 0;
	char *s = NULL;

	for (i = 0; cmnd[i]; i++)
	{
		if (cmnd[i][0] != '$' || !cmnd[i][1])
			continue;

		if (_strcmp(cmnd[i], "$?") == 0)
		{
			replaceString(&(cmnd[i]), _itoa_c(status));
			return (1);
		}
		else if (_strcmp(cmnd[i], "$$") == 0)
		{
			replaceString(&(cmnd[i]), _itoa_c(getpid()));
			return (1);
		}
		else if (cmnd[i][0] == '$' && cmnd[i][1])
		{
			s = _getenv(cmnd[i] + 1);
			if (!s)
			{
				replaceString(&(cmnd[i]), _strdup(""));
				return (0);
			}
			replaceString(&(cmnd[i]), s);
		}
	}

	return (0);
}


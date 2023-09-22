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


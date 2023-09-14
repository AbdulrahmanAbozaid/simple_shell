#include "shell.h"

/**
 * _memset - Set the value of a variable in memory
 * @s: the string
 * @b: the value
 * @n: the new value
 * Return: the new value
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int ind;

	for (ind = 0; ind < n; ++ind)
	{
		s[ind] = b;
	}
	return (s);
}

/**
 * flushArr - Flush the array from String
 * @arr: the arr string
 */

void flushArr(char **arr)
{
	char **tmp = arr;

	if (!arr)
		return;
	while (*arr)
		free(*arr++);
	free(tmp);
}

/**
 * _realloc - Allocate memory
 * @oldMem: the memory
 * @old_size: the old size
 * @new_size: the new size
 * Return: the new memory
 */

void *_realloc(void *oldMem, unsigned int old_size, unsigned int new_size)
{
	char *newMem;

	if (!oldMem)
		return (malloc(new_size));
	if (!new_size)
		return (free(oldMem), NULL);
	if (new_size == old_size)
		return (oldMem);
	newMem = malloc(new_size);
	if (!newMem)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		newMem[old_size] = ((char *)oldMem)[old_size];
	}
	free(oldMem);
	return (newMem);
}

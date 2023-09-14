#include "shell.h"

/**
 * free_nil - frees
 * @itr: pointer to whome?/
 * Return: 1 | 0
 */

int free_nil(void **itr)
{
	if (itr && *itr)
	{
		free(*itr);
		*itr = NULL;
		return (1);
	}
	return (0);
}

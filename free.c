#include "shell.h"

void freeMatrix(char **mat)
{
	int i = 0;

	if (!mat)
	{
		return;
	}

	for (i = 0; mat[i]; i++)
	{
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat), mat = NULL;
}

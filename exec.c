#include "shell.h"

/**
 * runCmnd - run a command
 * @cmnd: command
 * @argv: arguments
 * Return: command
 */

int runCmnd(char **cmnd, char **argv, int idx)
{
	pid_t chld;
	int status;
	char *cmd;

	cmd = _getpath(cmnd[0]);
	if (!cmd)
	{
		putError(argv[0], cmnd[0], idx);
		freeMatrix(cmnd);
		return (127);
	}
	chld = fork();
	if (chld == 0)
	{
		if (execve(cmd, cmnd, environ) == -1)
		{
			free(cmd), cmd = NULL;
			freeMatrix(cmnd);
		}
	}
	else
	{
		waitpid(chld, &status, 0);
		free(cmd), cmd = NULL;
		freeMatrix(cmnd);
	}
	return (WEXITSTATUS(status));
}

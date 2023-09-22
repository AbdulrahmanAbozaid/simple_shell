#include "shell.h"

/**
 * isInner - check if a string is inside
 * @command: string
 * Return: int
 */

int isInner(char *command)
{
	char *inners[] = {
		"exit",
		"env",
		"setenv",
		"cd",
		NULL};
	int i = 0;

	for (i = 0; inners[i]; i++)
	{
		if (_strcmp(inners[i], command) == 0)
			return (1);
	}
	return (0);
}

/**
 * runInner - check if a string is inside
 * @command: string
 * @argv: argv
 * @status: status
 * @idx: index
 * Return: void
 */

void runInner(char **command, char **argv, int *status, int idx)
{
	if (_strcmp(command[0], "exit") == 0)
		exitHsh(command, argv, status, idx);
	else if (_strcmp(command[0], "env") == 0)
		putEnv(command, status);
}

/**
 * exitHsh - exit the process with the environment
 * @command: string of commands
 * @status: exit status
 * Return: void
 */

void exitHsh(char **command, char **argv, int *status, int idx)
{
	int val = (*status);
	char *indx, msg[] = ": exit: Illegal number: ";

	if (command[1])
	{
		if (isPos(command[1]))
		{
			val = _atoi_c(command[1]);
		}
		else
		{
			indx = _itoa_c(idx);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, indx, _strlen(indx));
			write(STDERR_FILENO, msg, _strlen(msg));
			write(STDERR_FILENO, command[1], _strlen(command[1]));
			write(STDERR_FILENO, "\n", 1);
			free(indx);
			freeMatrix(command);
			(*status) = 2;
			return;
		}
	}
	freeMatrix(command);
	exit(val);
}

/**
 * putEnv - print env
 * @cmnd: command
 * @stato: status
 * Return: fsf
 */

void putEnv(char **cmnd, int *stato)
{
	int it = 0;

	for (it = 0; environ[it]; it++)
	{
		write(STDOUT_FILENO, environ[it], _strlen(environ[it]));
		write(STDOUT_FILENO, "\n", 1);
	}
	freeMatrix(cmnd);
	(*stato) = 0;
}

#include "shell.h"

/**
 * hsh - shell command
 * @info: shell information
 * @argv: arguments
 * Return: shell command
 */

int hsh(info_t *info, char **argv)
{
	int bRes = 0;
	ssize_t i = 0;

	while (i != -1 && bRes != -2)
	{
		clearInfoT(info);
		if (isActive(info))
		{
			_puts("$ ");
		}
		_eputchar(BUF_FLUSH);
		i = readInput(info);
		if (i != -1)
		{
			setInfo(info, argv);
			bRes = findSuit(info);
			if (bRes == -1)
			{
				findCmnd(info);
			}
		}
		else if (isActive(info))
		{
			_putchar('\n');
			_putchar(BUF_FLUSH);
		}
		freeInfoT(info, 0);
	}
	writeHistory(info);
	freeInfoT(info, 1);
	if (!isActive(info) && info->status)
		exit(info->status);
	if (bRes == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bRes);
}

/**
 * findSuit - find a suit in the list of active (find_builtin)
 * @info: the info structure
 * Return: the suit
 */

int findSuit(info_t *info)
{
	int it = 0, bRes = -1;

	builtin_t builtin_path[] = {
		{"exit", mExit},
		{"env", _myenv},
		{"help", mHelp},
		{"history", printHistory},
		{"setenv", msetEnvVar},
		{"unsetenv", munsetEnvVar},
		{"cd", mCD},
		{"alias", printAliasList},
		{NULL, NULL},
	};
	for (it = 0; builtin_path[it].typ; it++)
	{
		if (_strcmp(info->argv[0], builtin_path[it].typ) == 0)
		{
			info->line_count++;
			bRes = builtin_path[it].func(info);
			break;
		}
	}
	return (bRes);
}

/**
 * findCmnd - find a function that matches the given (find_cmd)
 * @info: the information
 * Return: the function
 */

void findCmnd(info_t *info)
{
	int it, jt;
	char *PATH = NULL;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->line_count++;
		info->lineCountFlag = 0;
	}
	for (it = 0, jt = 0; info->arg[it]; it++)
	{
		if (!is_delim(info->arg[it], " \t\n"))
			jt++;
	}
	if (!jt)
		return;
	PATH = findPath(info, getEnv(info, "PATH="), info->argv[0]);
	if (PATH)
	{
		info->path = PATH;
		forkCmd(info);
	}
	else
	{
		if ((isActive(info) || getEnv(info, "PATH=") || info->argv[0][0] == '/')
				&& isExec(info, info->argv[0]))
			forkCmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			/* NOTYET: not found\n */
			put_err(info, "No such file or directory.\n");
		}
	}
}

/**
 * forkCmd - fork a process (fork_cmd)
 * @info: the info structure
 * Return: the status of the
 */

void forkCmd(info_t *info)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Unable to fork");
		return;
		/* NOTYET: Error Handler */
	}
	if (cpid == 0)
	{
		/* Parent Process */
		if (execve(info->path, info->argv, getEnvironment(info)) == -1)
		{
			freeInfoT(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		/* TODO: WIFEXITED */
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				/* NOTYET: Permission denied */
				put_err(info, "Access denied\n");
		}
	}
}

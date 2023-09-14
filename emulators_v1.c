#include "shell.h"

/**
 * mExit - Exit the process
 * @info: the exit status of the process and
 * exit code returned from the process
 * Return: the exit status of the process
 */

int mExit(info_t *info)
{
	int eCheck;

	if (info->argv[1])
	{
		eCheck = _erratoi(info->argv[1]);
		if (eCheck == -1)
		{
			info->status = 2;
			put_err(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * mCD - change Directory (_mycd)
 * @info: Information
 * Return: 0 if successful
 */

int mCD(info_t *info)
{
	char *cwd = NULL, *cdDir = NULL, strData[1024];
	int cdRes = 0;

	cwd = getcwd(strData, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failed here<<\n"); /* getcwd failure emsg here */
	if (!info->argv[1])
	{
		if (!cdDir)
			cdRes = chdir((cdDir = getEnv(info, "PWD=")) ? cdDir : "/");
		else
			cdRes = chdir(cdDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getEnv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(getEnv(info, "OLDPWD=")), _putchar('\n');
		cdRes = chdir((cdDir = getEnv(info, "OLDPWD=")) ? cdDir : "/");
	}
	else
		cdRes = chdir(info->argv[1]);

	if (cdRes == -1)
	{
		put_err(info, "Can't chdir to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		setEnvVar(info, "OLDPWD", getEnv(info, "PWD="));
		setEnvVar(info, "PWD", getcwd(strData, 1024));
	}
	return (0);
}

/**
 * mHelp - display this help message
 * @info: the information
 * Return: 0 if successful
 */

int mHelp(info_t *info)
{
	(void)info;
	_puts("emulators_v1.c:94 mHelp called successfully.\n");
	_putchar(BUF_FLUSH);
	return (0);
}

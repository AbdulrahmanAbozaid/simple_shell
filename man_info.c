#include "shell.h"

/**
 * clearInfoT - clear all information
 * @info: information
 * Return: information flags
 */

void clearInfoT(info_t *info)
{
	info->argC = 0;
	info->argv = NULL;
	info->arg = NULL;
	info->path = NULL;
}

/**
 * setInfo - set information
 * @info: the info structure
 * @argv: the arguments
 * Return: the info structure
 */

void setInfo(struct info *info, char **argv)
{
	int ind = 0;

	info->file_path = argv[0];
	if (info->arg)
	{
		info->argv = split(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (ind = 0; info->argv && info->argv[ind]; ind++)
			;
		info->argC = ind;
		getAliasVal(info);
		getVarVal(info);
	}
}

/**
 * freeInfoT - free information about a given
 * @info: the information
 * @al: the information
 */

void freeInfoT(info_t *info, int al)
{
	flushArr(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (al)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		flushArr(info->environment);
		info->environment = NULL;
		/* NotYet*** */
		free_nil((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

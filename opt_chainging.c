#include "shell.h"

/**
 * isChained - true if the current state is a chained state (is_chain)
 * @info: the current state
 * @cmd: the current command
 * @s: the current state
 * Return: true if the current
 */

int isChained(info_t *info, char *cmd, size_t *s)
{
	size_t ts = *s;

	if (cmd[ts] == '|' && cmd[ts + 1] == '|')
	{
		cmd[ts] = 0;
		ts++;
		info->cmd_buf_type = OR_MODE;
	}
	else if (cmd[ts] == '&' && cmd[ts + 1] == '&')
	{
		cmd[ts] = 0;
		ts++;
		info->cmd_buf_type = AND_MODE;
	}
	else if ((cmd[ts] == ';'))
	{
		cmd[ts] = 0;
		info->cmd_buf_type = CHAIN_MODE;
	}
	else
		return (0);
	*s = ts;
	return (1);
}

/**
 * checkChainMode - check if the command is a chain (check_chain)
 * @info: the command
 * @cmd: the command
 * @curr: the current
 * @i: the index of the
 * @len: the length of the
 * Return: 0 if the command
 */

void checkChainMode(info_t *info, char *cmd,
					size_t *curr, size_t i, size_t len)
{
	size_t jt = *curr;

	if (info->cmd_buf_type == AND_MODE)
	{
		if (info->status)
		{
			cmd[i] = 0;
			jt = len;
		}
	}
	if (info->cmd_buf_type == OR_MODE)
	{
		if (!info->status)
		{
			cmd[i] = 0;
			jt = len;
		}
	}
	*curr = jt;
}

/**
 * getAliasVal - get the alias (replace_alias)
 * @info: the information
 * Return: the alias (replace_alias)
 */

int getAliasVal(info_t *info)
{
	char *str;
	list_t *alias;
	int it;

	for (it = 0; it < 10; it++)
	{
		alias = isNodePrefix(info->alias, info->argv[0], '=');
		if (!alias)
			return (0);
		free(info->argv[0]);
		str = _strchr(alias->str, '=');
		if (!str)
			return (0);
		str = _strdup(str + 1);
		if (!str)
			return (0);
		info->argv[0] = str;
	}
	return (1);
}

/**
 * getVarVal - get a variable value from a string (replace_vars)
 * @info: the info structure
 * Return: the variable value
 */

int getVarVal(info_t *info)
{
	int it = 0;
	list_t *arg;

	for (it = 0; info->argv[it]; it++)
	{
		if (info->argv[it][0] != '$' || !info->argv[it][1])
			continue;
		if (!_strcmp(info->argv[it], "$?"))
		{
			replaceString(&(info->argv[it]),
						  _strdup(convert_radix(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[it], "$$"))
		{
			replaceString(&(info->argv[it]), _strdup(convert_radix(getpid(), 10, 0)));
			continue;
		}
		arg = isNodePrefix(info->env, &info->argv[it][1], '=');
		if (arg)
		{
			replaceString(&(info->argv[it]), _strdup(_strchr(arg->str, '=') + 1));
			continue;
		}
		replaceString(&(info->argv[it]), _strdup(""));
	}
	return (0);
}

/**
 * replaceString - replace a string with a new string (replace_string)
 * @past: the string to be replaced
 * @new: the string to be replaced
 * Return: s the new string
 */

int replaceString(char **past, char *new)
{
	/* **past: by reference to change the original one */
	free(*past);
	*past = new;
	return (1);
}

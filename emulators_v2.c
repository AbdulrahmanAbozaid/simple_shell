#include "shell.h"

/**
 * printHistory - print history
 * @info: information
 * Description: Print history
 * Return: _myhistory
 */

int printHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - remove alias
 * @info: information
 * @alias: alias
 * Return: _myhistory
 */

int unsetAlias(info_t *info, char *alias)
{
	char *pc, ch;
	int res;

	pc = _strchr(alias, '=');
	if (!pc)
		return (1);
	ch = *pc;
	*pc = 0;
	res = delete_node_at_index(&(info->alias), getNodeIndex(info->alias,
															isNodePrefix(info->alias, alias, -1)));
	*pc = ch;
	return (res);
}

/**
 * setAlias - set the alias of the node
 * @info: the node info
 * @alias: the alias of the node
 * Return: 0 if successful
 */

int setAlias(info_t *info, char *alias)
{
	char *pc;

	pc = _strchr(alias, '=');
	if (!pc)
		return (1);
	if (!*++pc)
		return (unsetAlias(info, alias));
	unsetAlias(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * printAlias - print the alias
 * @alias: the information about the
 * Return: 0 on success, -1 on failure
 */

int printAlias(list_t *alias)
{
	char *pc = NULL, *ch = NULL;

	if (alias)
	{
		pc = _strchr(alias->str, '=');
		for (ch = alias->str; ch <= pc; ch++)
			_putchar(*ch);
		_putchar('\'');
		_puts(pc + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * printAliasList - print a list of aliases
 * @info: the alias list information structure to print
 * Return: 0 on success and 1 on failure
 */

int printAliasList(info_t *info)
{
	list_t *alias = NULL;
	char *pc = NULL;
	int it;

	if (info->argC == 1)
	{
		alias = info->alias;
		while (alias)
		{
			printAlias(alias);
			alias = alias->next;
		}
		return (0);
	}
	for (it = 1; info->argv[it]; it++)
	{
		pc = _strchr(info->argv[it], '=');
		if (pc)
			setAlias(info, info->argv[it]);
		else
			printAlias(isNodePrefix(info->alias, info->argv[it], '='));
	}
	return (0);
}

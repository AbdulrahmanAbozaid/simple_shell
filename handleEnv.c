#include "shell.h"

/**
 * _myenv - current environment
 * @info: information
 * Return: current environment
 */

int _myenv(info_t *info)
{
	print_ls(info->env);
	return (0);
}

/**
 * getEnv - get the environment
 * @info: information
 * @name: name of the environment
 * Return: environment
 */

char *getEnv(info_t *info, char *name)
{
	list_t *nod = info->env;
	char *c;

	while (nod)
	{
		c = start_by(nod->str, name);
		if (c && *c)
			return (c);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * msetEnvVar - sets the environment variable
 * @info: the environment variable
 * Return:  the value of the environment variable
 */

int msetEnvVar(info_t *info)
{
	if (info->argC != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (setEnvVar(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * munsetEnvVar - unsets the environment variable
 * @info: the environment variable
 * Return:  the value of the environment variable
 */

int munsetEnvVar(info_t *info)
{
	int ind;

	if (info->argC == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (ind = 1; ind <= info->argC; ind++)
		unsetEnvVar(info, info->argv[ind]);
	return (0);
}

/**
 * populate_env_list - populate the environment list fr
 * @info: the environment
 * Return: 0 if
 */

int populate_env_list(info_t *info)
{
	list_t *env = NULL;
	size_t st;

	for (st = 0; environ[st]; st++)
	{
		add_node_end(&env, environ[st], 0);
	}
	info->env = env;
	return (0);
}

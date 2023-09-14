#include "shell.h"

/**
 * getEnvironment - get the environment (get_environ)
 * @info: the environment
 * Return: the environment
 */

char **getEnvironment(info_t *info)
{
	if (!info->environment || info->envChange)
	{
		info->environment = listStringfy(info->env);
		info->envChange = 0;
	}
	return (info->environment);
}

/**
 * unsetEnvVar - remove the environment
 * @info: the environment
 * @var: the variable
 * Return: 0 if successful
 */

int unsetEnvVar(info_t *info, char *var)
{
	list_t *env = info->env;
	size_t i;
	char *pc;


	if (!env || !var)
		return (0);

	while (env)
	{
		pc = start_by(env->str, var);
		if (pc && *pc == '=')
		{
			info->envChange = delete_node_at_index(&(info->env), i);
			i = 0;
			env = info->env;
			continue;
		}
		env = env->next;
		i++;
	}
	return (info->envChange);
}

/**
 * setEnvVar - set the environment
 * @info: the environment
 * @var: the variable
 * @val: the variable
 * Return: 0 if successful
 */

int setEnvVar(info_t *info, char *var, char *val)
{
	list_t *env;
	char *pc, *buff = NULL;

	if (!var || !var)
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, val);
	env = info->env;
	while (env)
	{
		pc = start_by(env->str, var);
		if (pc && *pc == '=')
		{
			free(env->str);
			env->str = buff;
			info->envChange = 1;
			return (0);
		}
		env = env->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->envChange = 1;
	return (0);
}

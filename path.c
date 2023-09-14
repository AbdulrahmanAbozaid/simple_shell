#include "shell.h"

/**
 * isExec - check if a command is executable (is_cmd)
 * @info: command information
 * @path: command path
 * Return: true if the command is executable
 */

int isExec(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * getSubPath - dup a character (dup_chars)
 * @pathStr: the path to the
 * @begin: the begin of the string
 * @end: the end of the string
 * Return: the character that was duped
 */

char *getSubPath(char *pathStr, int begin, int end)
{
	static char col[1024];
	int it = 0, jt = 0;

	for (it = begin; it < end; it++)
	{
		if (pathStr[it] != ':')
			col[jt++] = pathStr[it];
	}
	col[jt] = 0;
	return (col);
}

/**
 * findPath - find a path (find_path)
 * @info: the info
 * @pathStr: the path
 * @cmd: the command
 * Return: the path
 */

char *findPath(info_t *info, char *pathStr, char *cmd)
{
	int it = 0, curr = 0;
	char *path = NULL;

	if (!pathStr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_by(cmd, "./"))
	{
		if (isExec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathStr[it] || pathStr[it] == ':')
		{
			path = getSubPath(pathStr, curr, it);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isExec(info, path))
				return (path);
			if (!pathStr[it])
			break;
			curr = it;
		}
		it++;
	}
	return (NULL);
}

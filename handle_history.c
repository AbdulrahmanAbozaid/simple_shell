#include "shell.h"

/**
 * getHistoryFile - get the history file
 * @info: the history file
 * Return: the history
 */

char *getHistoryFile(info_t *info)
{
	char *hist, *dir;

	dir = getEnv(info, "HOME=");
	if (!dir)
		return (NULL);
	hist = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!hist)
		return (NULL);
	hist[0] = 0;
	_strcpy(hist, dir);
	_strcat(hist, "/");
	_strcat(hist, HISTORY_FILE);
	return (hist);
}

/**
 * writeHistory - write a history file with history
 * @info: the history
 * Return: the number of bytes written
 */

int writeHistory(info_t *info)
{
	ssize_t fdr;
	char *fn = getHistoryFile(info);
	list_t *hist = NULL;

	if (!fn)
		return (-1);
	fdr = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fdr == -1)
		return (-1);
	for (hist = info->history; hist; hist = hist->next)
	{
		_putsFD(hist->str, fdr);
		putchFD('\n', fdr);
	}
	putchFD(BUF_FLUSH, fdr);
	close(fdr);
	return (1);
}

/**
 * readHistory - read history
 * @info: the history
 * Return: the history
 */

int readHistory(info_t *info)
{
	int ind, lst = 0, lnCtr = 0;
	ssize_t fdr, fSize, fData;
	char *histFile = getHistoryFile(info), *str = NULL;
	struct stat st;

	if (!histFile)
		return (0);
	fdr = open(histFile, O_RDONLY);
	free(histFile);
	if (fdr == -1)
		return (0);
	if (!fstat(fdr, &st))
		fSize = st.st_size;
	if (fSize < 2)
		return (0);
	str = malloc(sizeof(char) * (fSize + 1));
	if (!str)
		return (0);
	fData = read(fdr, str, fSize);
	str[fSize] = 0;
	if (fData <= 0)
		return (free(str), 0);
	close(fdr);
	for (ind = 0; ind < fSize; ind++)
		if (str[ind] == '\n') /* take line by line */
		{
			str[ind] = 0;
			buildHistoryList(info, str + lst, lnCtr++);
			lst = ind + 1;
		}
	if (lst != ind)
		buildHistoryList(info, str + lst, lnCtr++); /*build_history_list*/
	free(str);
	info->historyCount = lnCtr;
	while (info->historyCount-- >= MAX_HISTORY)
		delete_node_at_index(&(info->history), 0);
	/*renumber_history*/
	resetHistoryCount(info);
	return (info->historyCount);
}

/**
 * buildHistoryList - builds a list of history entries
 * @info: the information
 * @data: the data structure
 * @size: the size of the structure in bytes
 * Return: the list of history entries that were created
 */

int buildHistoryList(info_t *info, char *data, int size)
{
	list_t *hist = NULL;

	if (info->history)
		hist = info->history;
	add_node_end(&hist, data, size);
	if (!info->history)
		info->history = hist;
	return (0);
}

/**
 * resetHistoryCount - returns the number of (renumber_history)
 * @info: the history
 * Return: the number of
 */

int resetHistoryCount(info_t *info)
{
	int ind = 0;
	list_t *hist = info->history;

	while (hist)
	{
		hist->num = ind++;
		hist = hist->next;
	}
	return (info->historyCount = ind);
}

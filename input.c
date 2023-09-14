#include "shell.h"

/**
 * readBuffer - read a line (input_buf)
 * @info: the information
 * @buf: the buffer to read
 * @bufLen: the number of bytes to read
 * Return: the number of bytes read
 */

ssize_t readBuffer(info_t *info, char **buf, size_t *bufLen)
{
	ssize_t res = 0;
	size_t len = 0;

	if (!*bufLen)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, ctrlCHandler);
#if GETLINE_MODE
		res = getline(buf, &len, stdin);
#else
		res = getLine(info, buf, &len);
#endif
		if (res > 0)
		{
			if ((*buf)[res - 1] == '\n')
			{
				(*buf)[res - 1] = '\0';
				res--;
			}
			info->lineCountFlag = 1;
			rmv_cmnt(*buf);
			buildHistoryList(info, *buf, info->historyCount++);
			*bufLen = res;
			info->cmd_buf = buf;
		}
	}
	return (res);
}

/**
 * readInput - read input (get_input)
 * @info: Information about
 * Return: Input
 */
ssize_t readInput(info_t *info)
{
	ssize_t res = 0;
	char **tbuf = &(info->arg), *buf_temp;
	static char *buffer;
	static size_t it = 0, j = 0, length = 0;

	if (length)
		length = 0;
	_putchar(BUF_FLUSH);
	res = readBuffer(info, &buffer, &length);
	if (res == -1)
	{
		return (-1);
	}
	if (length)
	{
		j = it;
		buf_temp = _strdup(buffer);
		checkChainMode(info, buffer, &j, it, length);
		while (j < length)
		{
			if (isChained(info, buffer, &j))
				break;
			j++;
		}
		it = j + 1;
		if (it >= length)
		{
			it = length = 0;
			info->cmd_buf_type = NORMAL_MODE;
		}
		*tbuf = buf_temp;
		return (_strlen(buf_temp));
	}
	*tbuf = buffer;
	return (res);
}

/**
 * getInputBuffer - get input buffer (read_buf)
 * @info: Information
 * @buffer: input buffer
 * @len: length of input buffer
 * Return:  input buffer
 */

ssize_t getInputBuffer(info_t *info, char *buffer, size_t *len)
{
	ssize_t ret;

	(void)info;
	if (*len)
		return (0);
	/* NOTYET: info->readfd */
	ret = read(STDIN_FILENO, buffer, MAX_READ_SIZE);
	if (ret >= 0)
		*len = ret;
	return (ret);
}

/**
 * getLine - get line
 * @info: information
 * @dbuf: input buffer
 * @len: length of input buffer
 *
 * Return: input buffer
 */

int getLine(info_t *info, char **dbuf, size_t *len)
{
	size_t sz; /* k */
	ssize_t res = 0, s = 0;
	char *pc = NULL, *nPc = NULL, *c;
	static char buffer[MAX_READ_SIZE];
	static size_t it, length;

	pc = *dbuf;
	if (pc && len)
		s = *len;
	if (it == length)
		length = it = 0;
	res = getInputBuffer(info, buffer, &length);
	if (res == -1 || (res == 0 && length == 0))
	{
		return (-1);
	}
	c = _strchr(buffer + it, '\n');
	sz = c ? (1 + (unsigned int)(c - buffer)) : length;
	nPc = _realloc(pc, s, s ? s + sz : sz + 1);
	if (!nPc)
		return (pc ? free(pc), -1 : -1);
	if (s)
		_strncat(nPc, buffer + it, sz - it);
	else
		_strncpy(nPc, buffer + it, sz - it + 1);
	s += sz - it;
	it = sz;
	pc = nPc;
	if (len)
		*len = s;
	*dbuf = pc;
	return (s);
}

/**
 * ctrlCHandler - control character handling (sigintHandler)
 * @signum: the signal number
 * Return: the signal number
 */

void ctrlCHandler(int signum)
{
	(void)signum;
	_putchar('\n');
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"

/**
 * listLength - returns the length of the list
 * @list: the list
 * Return: the length of the list
 */

size_t listLength(const list_t *list)
{
	size_t len = 0;

	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

/**
 * listStringfy - returns the string
 * @list: the list
 * Return: the string
 */

char **listStringfy(list_t *list)
{
	list_t *plist = list;
	size_t len = listLength(list), it = 0;
	char **result;
	char *str;

	if (!len || !list)
		return (NULL);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	for (len = 0; plist; plist = plist->next, len++)
	{
		str = malloc(_strlen(plist->str) + 1);
		if (!str)
		{
			for (it = 0; it < len; it++)
				free(result[it]);
			free(result);
			return (NULL);
		}
		str = _strcpy(str, plist->str);
		result[it] = str;
	}
	result[it] = NULL;
	return (result);
}

/**
 * print_list - print a list of
 * @head: the head of the list
 * Return: the head of the list
 */

size_t print_list(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(convert_radix(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * isNodePrefix - is the node prefix
 * @list: list of node names
 * @prefix: the node prefix
 * @c: the node character
 * Return: true if the node
 */

list_t *isNodePrefix(list_t *list, char *prefix, char c)
{
	char *tmp = NULL;

	while (list)
	{
		tmp = start_by(list->str, prefix);
		if (tmp && ((c == -1) || (c == *tmp)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - get the node index
 * @head: the head of the list
 * @node: the node
 * Return: s the index of the node
 */

ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t len = 0;

	while (head)
	{
		if (head == node)
		{
			return (len);
		}
		head = head->next;
		len++;
	}
	return (-1);
}

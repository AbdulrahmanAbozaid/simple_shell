#include "shell.h"

/**
 * add_node - add a node to the list of nodes*
 * @head: head*
 * @str: str*
 * @num: number
 * Return: ptr*
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *node = malloc(sizeof(list_t));

	if (node == NULL || !head)
		return (NULL);
	_memset((void *)node, 0, sizeof(list_t));
	node->num = num;
	if (str)
	{
		node->str = _strdup(str);
		if (!node->str)
		{
			free(node);
			return (NULL);
		}
	}

	node->next = *head;
	*head = node;
	return (node);
}

/**
 * add_node_end - add to list
 * @head: head
 * @str: str
 * @num: number
 * Return: ptr
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *tmpNode = *head;

	if (node == NULL)
		return (NULL);
	_memset((void *)node, 0, sizeof(list_t));
	node->num = num;
	if (str)
	{
		node->str = _strdup(str);
		if (!node->str)
		{
			free(node);
			return (NULL);
		}
	}
	if (!(*head))
	{
		*head = node;
		node->next = NULL;
		return (node);
	}
	while (tmpNode->next)
		tmpNode = tmpNode->next;
	node->next = NULL;
	tmpNode->next = node;
	return (node);
}

/**
 * print_ls - print the list of
 * @head: the head of the list
 * Return: the list
 */

size_t print_ls(const list_t *head)
{
	size_t s = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		s++;
	}
	return (s);
}

/**
 * delete_node_at_index - delete a node
 * @head: the head of the list
 * @index: the index of the node
 * Return: the node
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev;
	unsigned int ind = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (ind == index)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		ind++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - listp
 * @head: h
 * Return: void
 */

void free_list(list_t **head)
{
	list_t *node, *tmp, *htmp = *head;

	if (!head || !*head)
		return;
	node = htmp;
	while (node)
	{
		tmp = node->next;
		free(node->str);
		free(node);
		node = tmp;
	}
	*head = NULL;
}

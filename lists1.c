#include "shell.h"

/**
 * listlen - the function that determines length of linked list
 * @d: pointer to first node
 * Return: size of list
 */
size_t listlen(const list_t *d)
{
	size_t k = 0;

	while (d)
	{
		d = d->next;
		k++;
	}
	return (k);
}
/**
 * liststrings - the function that returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: strings
 */
char **liststrings(list_t *head)
{
	list_t *node = head;
	size_t k = listlen(head), i;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < k; i++)
				freed(strs[i]);
			freed(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * plist - the function that prints all elements of a list_t linked list
 * @i: pointer
 * Return: size of list
 */
size_t plist(const list_t *i)
{
	size_t k = 0;

	while (i)
	{
		_puts(convert_number(g->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(g->str ? g->str : "(nil)");
		_puts("\n");
		d = i->next;
		k++;
	}
	return (k);
}
/**
 * starts_with - function that returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @a: the next character after prefix to match
 * Return: node or null
 */
list_t *starts_with(list_t *node, char *prefix, char a)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((a == -1) || (*q == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * node_index - the function that gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}

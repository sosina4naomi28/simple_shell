#include "shell.h"

/**
 * addnode - that functions that adds a node to the start of the list
 * @head: address  pointer head node
 * @str: str
 * @num: node index
 * Return: size
 */
list_t *addnode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
/**
 * addnode_end - function that adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str
 * @num: node index
 * Return: size of list
 */
list_t *addnode_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			freed(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * plist_str - function that prints the str element of a list
 * @d: pointer
 * Return: size of list
 */
size_t plist_str(const list_t *d)
{
	size_t k = 0;

	while (d)
	{
		_puts(d->str ? d->str : "(nil)");
		_puts("\n");
		d = d->next;
		k++;
	}
	return (k);
}
/**
 * deletenode_index - the function that deletes node at given index
 * @head: address of pointer
 * @index: index
 * Return: 1  success,else 0
 */
int deletenode_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		freed(node->str);
		freed(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == index)
		{
			prev_node->next = node->next;
			freed(node->str);
			freed(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
/**
 * freed_list - the function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void freed_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

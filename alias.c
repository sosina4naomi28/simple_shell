#include "shell.h"

/**
 * alias - the function that  mimics the alias builtin
 * @ino: argument
 *  Return: 0 success
 */
int alias(ino_t *ino)
{
	int k = 0;
	char *ptr = NULL;

	list_t *node = NULL;

	if (ino->argc == 1)
	{
		node = ino->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; ino->argv[k]; k++)
	{
		ptr = _strchr(ino->argv[k], '=');
		if (ptr)
			set_alias(ino, ino->argv[k]);
		else
			print_alias(node_starts_with(ino->alias, ino->argv[k], '='));
	}
	return (0);
}
/**
 * zhistory - the function that shows the history list
 * @ino: arguments
 *  Return: 0
 */
int zhistory(ino_t *ino)
{
	print_list(ino->history);
	return (0);
}
/**
 * salias - the function that  sets alias to string
 * @ino: parameter
 * @str: the string
 * Return: 0  success, 1 error
 */
int salias(ino_t *ino, char *str)
{
	char *ptr

		ptr _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
	{
		return (unalias(ino, str));
	}
	unalias(ino, str);
	return (add_node_end(&(ino->alias), str, 0) == NULL);
}
/**
 * palias - the function that prints an alias string
 * @node: alias node
 * Return: Always 0 on success, 1 on error
 */
int palias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * unalias - the function that unsets alias to string
 * @ino: parameter
 * @str:  string
 * Return: 0  success, 1 (error)
 */
int unalias(ino_t *ino, char *str)
{
	char *ptr, a;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	a = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(ino->alias),
			get_node_index(ino->alias, node_starts_with(ino->alias, str, -1)));
	*ptr = a;
	return (ret);
}

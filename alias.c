#include "shell.h"


/**
 * alias - the function that  mimics the alias builtin 
 * @info: argument
 *  Return: 0 success
 */
int alias(info_t *info)
{
        int k = 0;
        char *ptr = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        print_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (k = 1; info->argv[k]; k++)
        {
                ptr = _strchr(info->argv[k], '=');
                if (ptr)
                        set_alias(info, info->argv[k]);
                else
                        print_alias(node_starts_with(info->alias, info->argv[k], '='));
        }

        return (0);
}/**
 * zhistory - the function that shows the history list
 * @info: arguments
 *  Return: 0
 */
int zhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * salias - the function that  sets alias to string
 * @info: parameter 
 * @str: the string 
 * Return: 0  success, 1 error
 */
int salias(info_t *info, char *str)
{
	char *ptr

	ptr _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr
		return (unset_alias(info, str));

	unalias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
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
 * @info: parameter 
 * @str:  string 
 * Return: 0  success, 1 (error)
 */
int unalias(info_t *info, char *str)
{
        char *ptr, a;
        int ret;

        ptr = _strchr(str, '=');
        if (!ptr)
                return (1);
        a = *ptr;
        *ptr = 0;
        ret = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *ptr = a;
        return (ret);
}

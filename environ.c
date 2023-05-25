#include "shell.h"

/**
 * unsetenviron - the function that remove an environment variable
 * @ino: arguments
 * Return: 1  delete,else 0
 * @var: the string
 */
int unsetenviron(ino_t *ino, char *var)
{
        list_t *node = ino->env;
        size_t k = 0;
        char *ptr;

        if (!node || !var)
                return (0);

        while (node)
        {
                ptr = starts_with(node->str, var);
                if (ptr && *ptr == '=')
                {
                        ino->env_changed = delete_node_at_index(&(ino->env), k);
                        k = 0;
                        node = ino->env;
                        continue;
                }
                node = node->next;
                k++;
        }
        return (inko->env_changed);
}
/**
 * get_environ - functions that returns the string array copy of our environ
 * @ino: arguments
 * Return: Always 0
 */
char **get_environ(ino_t *ino)
{
	if (!ino->environ || ino->env_changed)
	{
		ino->environ = list_to_strings(ino->env);
		ino->env_changed = 0;
	}

	return (ino->environ);
}
/**
 * setenviron - the function that initialize a new environment variable
 * @ino: arguments
 * @var: the string
 * @value: the string
 *  Return: 0 success
 */
int setenviron(ino_t *ino, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = ino->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

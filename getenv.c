#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @ino: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0 success
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
 * unsetenviron -the function that remove an environment variable
 * @ino: arguments
 * Return: 1 or 0
 * @var: string
 */
int unsetenviron(ino_t *ino, char *var)
{
	list_t *node = ino->env;
	size_t k = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			ino->env_changed = delete_node_at_index(&(ino->env), k);
			k = 0;
			node = ino->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (ino->env_changed);
}
/**
 * setenviron - the function that initialize a new environment variable
 * @ino: arguments
 * @var: the string
 * @value: string
 * Return:  0
 */
int setenviron(ino_t *ino, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

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
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(ino->env), buf, 0);
	free(buf);
	ino->env_changed = 1;
	return (0);
}

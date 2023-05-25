#include "shell.h"
/**
 * unsetenv -the function that Remove an environment variable
 * @info: arguments
 * Return: Always 0
 */
int unsetenv(ino_t *info)
{
	int k;

	if (ino->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= ino->argc; k++)
		_unsetenv(ino, ino->argv[k]);
	return (0);
}
/**
 * env - the function that prints the current environment
 * @info: arguments
 * Return: 0 success
 */
int env(ino_t *ino)
{
	print_list_str(ino->env);
	return (0);
}
/**
 * genv - the function that gets the value of an environ variable
 * @info: arguments
 * @name: env var name
 *
 * Return: the value
 */
char *genv(ino_t *ino, const char *name)
{
	list_t *node = ino->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * setenv - the function that Initialize a new environment variable
 * @info: arguments
 *  Return: Always 0
 */
int setenv(ino_t *ino)
{
	if (ino->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(ino, ino->argv[1], ino->argv[2]))
		return (0);
	return (1);
}
/**
 * env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_list(ino_t *ino)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&node, environ[k], 0);
	ino->env = node;
	return (0);
}

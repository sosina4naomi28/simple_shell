#include "shell.h"
/**
 * the_unsetenv -the function that Remove an environment variable
 * @info: arguments
 * Return: Always 0
 */
int the_unsetenv(ino_t *info)
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
 * the_env - the function that prints the current environment
 * @ino: arguments
 * Return: 0 success
 */
int the_env(ino_t *ino)
{
	print_list_str(ino->env);
	return (0);
}
/**
 * genv - the function that gets the value of an environ variable
 * @ino: arguments
 * @nam:  name
 * Return: the value
 */
char *genv(ino_t *ino, const char *nam)
{
	list_t *node = ino->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, nam);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}
/**
 * the_setenv - the function that Initialize a new environment variable
 * @ino: arguments
 * Return:  0 success
 */
int the_setenv(ino_t *ino)
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
 * @ino: arguments
 * Return: 0 success
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

#include "shell.h"

/**
 * clear_ino - the function that initializes info_t struct
 * @ino: struct address
 */
void clear_ino(ino_t *ino)
{
	ino->arg = NULL;
	ino->argv = NULL;
	ino->path = NULL;
	ino->argc = 0;
}
/**
 * set_ino -function that initializes info_t struct
 * @ino: struct address
 * @av: argument vector
 */
void set_ino(ino_t *ino, char ***av)
{
	int k = 0;

	ino->fname = av[0];
	if (ino->arg)
	{
		ino->argv = strtow(ino->arg, " \t");
		if (!ino->argv)
		{
			ino->argv = malloc(sizeof(char *) * 2);
			if (ino->argv)
			{
				ino->argv[0] = _strdup(ino->arg);
				ino->argv[1] = NULL;
			}
		}
		for (k = 0; ino->argv && ino->argv[k]; k++)
			;
		ino->argc = k;

		replace_alias(ino);
		replace_vars(ino);
	}
}

/**
 * free_ino - function that frees info_t struct fields
 * @ino: struct address
 * @all: true success
 */
void free_ino(ino_t *ino, int all)
{
	ffree(ino->argv);
	ino->argv = NULL;
	ino->path = NULL;
	if (all)
	{
		if (!ino->cmd_buf)
			free(ino->arg);
		if (ino->env)
			free_list(&(ino->env));
		if (ino->history)
			free_list(&(ino->history));
		if (ino->alias)
			free_list(&(ino->alias));
		ffree(ino->environ);
			ino->environ = NULL;
		bfree((void **)ino->cmd_buf);
		if (ino->readfd > 2)
			close(ino->readfd);
		_putchar(BUF_FLUSH);
	}
}

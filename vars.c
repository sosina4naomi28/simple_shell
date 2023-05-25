#include "shell.h"

/**
 * test_chain -the function that test if current char in buffer is a chain delimeter
 * @ino: struct
 * @buf: the buffer
 * @ptr: current position
 * Return: 1 success,else 0
 */
int test_chain(ino_t *ino, char *buf, size_t *ptr)
{
	size_t i = *ptr;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		ino->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		ino->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		ino->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}
/**
 * checking_the_chain -the function that checks we should continue chaining based on last status
 * @ino: the struct
 * @buf: the
 * @ptr: current address
 * @k: begging position
 * @len: length
 * Return: Void
 */
void checking_the_chain(ino_t *ino, char *buf, size_t *ptr, size_t k, size_t len)
{
	size_t i = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (ino->status)
		{
			buf[k] = 0;
			i = len;
		}
	}
	if (ino->cmd_buf_type == CMD_OR)
	{
		if (!ino->status)
		{
			buf[k] = 0;
			i = len;
		}
	}

	*ptr = i;
}
/**
 * replace_the_alias -the function that replaces an aliases in the tokenized string
 * @ino: the parameter struct
 * Return: 1 success,else 0
 */
int replace_the_alias(ino_t *ino)
{
	int k;
	list_t *node;
	char *Q;

	for (k = 0; k < 10; k++)
	{
		node = starts_with(ino->alias, ino->argv[0], '=');
		if (!node)
			return (0);
		freed(ino->argv[0]);
		Q = _strchr(node->str, '=');
		if (!Q)
			return (0);
		Q = _strdup(Q + 1);
		if (!Q)
			return (0);
		ino->argv[0] = Q;
	}
	return (1);
}
/**
 * replace_the_vars - the fuction that replaces vars in the tokenized string
 * @ino:  struct
 * Return: 1 success,else 0
 */
int replace_the_vars(ino_t *ino)
{
	int k = 0;
	list_t *node;

	for (k = 0; ino->argv[k]; k++)
	{
		if (info->argv[k][0] != '$' || !ino->argv[k][1])
			continue;

		if (!_strcmp(ino->argv[k], "$?"))
		{
			replace_string(&(ino->argv[k]),
					_strdup(convert_number(ino->status, 10, 0)));
			continue;
		}
		if (!_strcmp(ino->argv[k], "$$"))
		{
			replace_string(&(ino->argv[k]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(ino->env, &ino->argv[k][1], '=');
		if (node)
		{
			replace_string(&(ino->argv[k]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&ino->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_the_string - the function that  replaces string
 * @pre: the address of old string
 * @rec: new string
 * Return: 1 success,else 0
 */
int replace_the_string(char **pre, char *rec)
{
	freed(*pre);
	*pre = rec;
	return (1);
}

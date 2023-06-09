#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @ino: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(ino_t *ino, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(ino, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			ino->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(ino, *buf, ino->histcount++);
			{
				*len = r;
				ino->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input - gets a line minus the newline
 * @ino: parameter struct
 * Return: bytes
 */
ssize_t get_input(ino_t *ino)
{
	static char *buf;
	static size_t k, i, len;
	ssize_t r = 0;
	char **buf_p = &(ino->arg), *ptr;

	_putchar(BUF_FLUSH);
	r = input_buf(ino, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		i = k;
		ptr = buf + k;

		checking_the_chain(ino, buf, &i, k, len);
		while (j < len)
		{
			if (test_chain(ino, buf, &i))
				break;
			i++;
		}
		k = i + 1;
		if (k >= len)
		{
			k = len = 0;
			ino->cmd_buf_type = CMD_NORM;
		}
		*buf_p = ptr;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}
/**
 * read_buf - the function that reads a buffer
 * @ino: parameter struct
 * @buf: buffer
 * @k: size
 * Return: r
 */
ssize_t read_buf(ino_t *ino, char *buf, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*k = r;
	return (r);
}
/**
 * _getline - function that gets the next line of input from STDIN
 * @ino: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(ino_t *ino, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

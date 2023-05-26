#include "shell.h"

/**
 * _eputs - the function that prints an input string
 * @str: string
 * Return: no return
 */
void _eputs(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}
/**
 * _eputchar - the function that writes the character c to stderr
 * @a: character
 * Return: 1 success,else -1
 */
int _eputchar(char a)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (a != BUF_FLUSH)
		buf[k++] = a;
	return (1);
}
/**
 * _putfd - the function that writes the character c to given fd
 * @a: character
 * @fd: filedescriptor
 * Return: 1 success, else -1
 */
int _putfd(char a, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (a != BUF_FLUSH)
		buf[k++] = a;
	return (1);
}
/**
 * _putsfd - the function that prints an input string
 * @str: string
 * @fd: filedescriptor
 * Return: count
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}

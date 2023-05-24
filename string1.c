#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}

/**
 * _puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_putchar(string[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @Q: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char Q)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (Q == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (Q != BUF_FLUSH)
		buf[i++] = Q;
	return (1);
}


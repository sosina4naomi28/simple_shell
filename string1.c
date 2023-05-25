i#include "shell.h"

/**
 * _strcpy - the function that copies a string
 * @dest:  destination
 * @src:  source
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}
/**
 * _strdup - the function that  duplicates a string
 * @string: the string
 * Return: pointer
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
 * _puts - the function that prints an input string
 * @string: the string to be printed
 * Return: Nothing
 */
void _puts(char *string)
{
	int k = 0;

	if (!string)
		return;
	while (string[k] != '\0')
	{
		_putchar(string[k]);
		k++;
	}
}
/**
 * _putchar - the function that writes the character c to stdout
 * @Q: character
 * Return: 1 success and error,-1
 */
int _putchar(char Q)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (Q == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		k = 0;
	}
	if (Q != BUF_FLUSH)
		buf[k++] = Q;
	return (1);
}

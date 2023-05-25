#include "shell.h"

/**
 * strnconcat - the function that concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *strnconcat(char *dest, char *src, int n)
{
	int k = 0, i = 0;
	char *s = dest;

	while (dest[k] != '\0')
		k++;
	while (src[i] != '\0' && i < n)
	{
		dest[k] = src[i];
		k++;
		i++;
	}
	if (i < n)
		dest[k] = '\0';
	return (s);
}
/**
 **_strncpy - the function that copies a string
 *@dest: the destination string
 *@src:  source string
 *@n:  amount of characters
 *Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int k, i;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		i = k;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (s);
}
/**
 * strlchr - the function that locates a character in a string
 * @s: the string
 * @a: the character
 * Return: (s)
 */
char *strlchr(char *s, char a)
{
	do {
		if (*s == a)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

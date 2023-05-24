#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @U: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *U)
{
	int i = 0;

	if (!U)
		return (0);

	while (*U++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @U1: the first strang
 * @U2: the second strang
 *
 * Return: negative if U1 < U2, positive if U1 > U2, zero if U1 == U2
 */
int _strcmp(char *U1, char *U2)
{
	while (*U1 && *U2)
	{
		if (*U1 != *U2)
			return (*U1 - *U2);
		U1++;
		U2++;
	}
	if (*U1 == *U2)
		return (0);
	else
		return (*U1 < *U2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}


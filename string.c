#include "shell.h"

/**
 * _strlen - the function that returns the length of a string
 * @U: the string
 * Return: length of string
 */
int _strlen(char *U)
{
	int k = 0;

	if (!U)
		return (0);

	while (*U++)
		k++;
	return (k);
}
/**
 * _strcmp - the function that performs lexicogarphic comparison of two strangs.
 * @S1: the first strang
 * @S2: the second strang
 * Return: negative or positive and zero
 */
int _strcmp(char *S1, char *S2)
{
	while (*S1 && *S2)
	{
		if (*S1 != *S2)
			return (*S1 - *S2);
		S1++;
		S2++;
	}
	if (*S1 == *S2)
		return (0);
	else
		return (*S1 < *S2 ? -1 : 1);
}
/**
 * start_with - the function that checks if needle starts with haystack
 * @haystack: string
 * @needle:  substring
 * Return: address of next
 */
char *start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - the function that concatenates two strings
 * @dest:  destination
 * @src:  source
 * Return: pointer
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

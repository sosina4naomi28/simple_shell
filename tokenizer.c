#include "shell.h"

/**
 * **strtow - the function that splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @Dm: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *Dm)
{
	int k, i, j, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!Dm)
		Dm = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!delimeter(str[k], Dm) && (delimeter(str[k + 1], Dm) || !str[k + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, i = 0; i < nw; i++)
	{
		while (delimeter(str[k], Dm))
			k++;
		j = 0;
		while (!delimeter(str[k + j], Dm) && str[k + j])
			j++;
		s[i] = malloc((j + 1) * sizeof(char));
		if (!s[i])
		{
			for (j = 0; j < i; j++)
				ffreed(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < j; m++)
			s[i][m] = str[k++];
		s[i][m] = 0;
	}
	s[i] = NULL;
	return (s);
}
/**
 * **strtow2 - the function that splits a string into words
 * @str: input string
 * @d:  delimeter
 * Return: a pointer
 */
char **strtow2(char *str, char d)
{
	int k, i, j, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
				    (str[k] != d && !str[k + 1]) || str[k + 1] == d)
			nw++;
	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, i = 0; i < nw; i++)
	{
		while (str[k] == m && str[k] != d)
			k++;
		j = 0;
		while (str[k + j] != d && str[k + j] && str[k + j] != d)
			j++;
		s[i] = malloc((j + 1) * sizeof(char));
		if (!s[i])
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < j; m++)
			s[i][m] = str[k++];
		s[i][m] = 0;
	}
	s[i] = NULL;
	return (s);
}

#include "shell.h"

/**
 * active - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 success , 0 otherwise
 */
int active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delimeter - checks if character is a delimeter
 * @a: the char to check
 * @del: delimeter string
 * Return: 1 success, else 0
 */
int delimeter(char a, char *del)
{
	while (*del)
		if (*del++ == a)
			return (1);
	return (0);
}
/**
 * alpha - checks for alphabetic character
 * @a: input character
 * Return: 1 success, else 0
 */
int alpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * atoi - afunction that change a string to an integer
 * @s: string
 * Return: 0 succuss
 */
int atoi(char *s)
{
	int k, sig = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0; s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
			sig *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sig == -1)
		output = -result;
	else
		output = result;

	return (output);
}

#include "shell.h"

/**
 * bfreed - the function that frees a pointer and NULLs the address
 * @ptr:  pointer to free
 * Return: 1 success, else 0.
 */
int bfreed(void **ptr)
{
	if (ptr && *ptr)
	{
		bfreed(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

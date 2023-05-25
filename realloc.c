#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @W: the pointer to the memory area
 * @X: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *W, char X, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		W[i] = X;
	return (W);
}

/**
 * ffree - frees a string of strings
 * @XX: string of strings
 */
void ffree(char **XX)
{
	char **a = XX;

	if (!XX)
		return;
	while (*XX)
		free(*XX++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *Q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	Q = malloc(new_size);
	if (!Q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		Q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (Q);
}


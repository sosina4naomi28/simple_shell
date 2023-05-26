#include "shell.h"

/**
 * fill_memoset - the function that fills memory with a constant byte
 * @P: pointer to the memory
 * @B: byte
 * @n: amount of bytes
 * Return: a pointer
 */
char *fill_memoset(char *P, char B, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		P[k] = B;
	return (P);
}
/**
 * ffreed - the function that frees a string of strings
 * @str: string
 */
void ffreed(char **str)
{
	char **a = str;

	if (!str)
		return;
	while (*str)
		ffreed(*str++);
	ffreed(a);
}
/**
 * _realloc - the function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size:  size of previous block
 * @new_size: byte size of new block
 * Return: pointer
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

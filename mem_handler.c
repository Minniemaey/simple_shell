#include "shell.h"

/**
 **_memset - fills memory block
 *@s: pointer to memory block
 *@b: value to be set
 *@n: number of bytes set to b
 *Return: ptr to s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
	{
		s[a] = b;
	}
	return (s);
}

/**
 * _realloc - reallocates byte to memory block
 * @ptr: ptr to old block
 * @old_size: byte size of old mem block
 * @new_size: byte size of new mem block
 * Return: ptr new_size or NULL
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *newptr;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	newptr = malloc(new_size);
	if (!newptr)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		newptr[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (newptr);
}

/**
 * _free - frees previously allocated memory block
 * @ptr: pointer to mem block to be freed
 * Return: no value
 */

int _free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_str - frees previously allocated mem to strings
 * @pp: a string of strings
 */

void free_str(char **pp)
{
	char **ptr = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(ptr);
}

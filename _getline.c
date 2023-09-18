#include "shell.h"

/**
 * _getline - reads input from user
 * @ptr: pointer to a char pointer
 * @n: size
 * @str: FILE pointer
 *
 * Return: Number of char
 */

int _getline(char **ptr, size_t *n, FILE *str)
{
	size_t buff = 0;
	ssize_t chars = getline(ptr, &buff, str);

	if (chars == -1 && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return chars;
}

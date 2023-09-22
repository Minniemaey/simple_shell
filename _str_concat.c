#include "shell.h"

/**
 * _str_concat - appends n char to the end of a string
 * @dest: destination string
 * @src: source string
 * @n: string length
 *
 * Return: pointer to dest
 */
char *_str_concat(char *dest, char *src, int n)
{
	int i, j;

	j = _strlen(dest);
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[j + i] = src[i];
	}
	dest[j + i] = '\0';
	return (dest);
}

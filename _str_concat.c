#include "shell.h"

/**
 * _str_concat - function that concatenates two strings
 * @src: source string
 * @dest: destination string
 * @n: string length
 *
 * Return: pointer to dest
 */
char *_str_concat(char *src, char *dest, int n)
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

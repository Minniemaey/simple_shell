#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	int n = 0;

	if ((dest == src) || (src == 0))
	{
		return (dest);
	}
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _strdup - fucntion that duplicates a string
 * @s: string to be duplicated
 * Return: pointer
 */

char *_strdup(const char *s)
{
	char *str;
	int len = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	for (len++; len--;)
	{
		str[len] = *--s;
	}
	return (str);
}

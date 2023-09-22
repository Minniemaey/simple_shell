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
 **_strncpy - copies n char from src to dest string
 *@dest: destination str
 *@src: source str
 *@n: number of char
 *Return: ptr to copied string
 */

char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;
	int i, j;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
	{
		dest[i] = src[i];
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strdup - function that duplicates a string
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

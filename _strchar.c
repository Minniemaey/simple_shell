#include "shell.h"

/**
 * *_strchr - searches for a char in string
 * @s: input string
 * @c: char to search for
 * Return: pointer to null
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (0);
}

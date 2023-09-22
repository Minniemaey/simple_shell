#include "shell.h"

/**
 * *_strchr - searches for a char in string
 * @s: input string
 * @c: char to search for
 * Return: pointer to s
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

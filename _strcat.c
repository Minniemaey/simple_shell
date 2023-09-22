#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: pointer to destination buffer
 * @src: pointer to source buffer
 * Return: dest pointer
 */

char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (ptr);
}

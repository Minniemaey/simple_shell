#include "shell.h"

/**
 * search_prefix - checks if a string begins with a given prefix
 * @haystack: string to search
 * @needle: string to search for
 * Return: ptr to next char in string
 */

char *search_prefix(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	return ((char *)haystack);
	}
}

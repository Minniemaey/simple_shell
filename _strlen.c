#include "shell.h"

/**
  * _strlen - calculates string length
  * @ptr: pointer to string
  * Return: string length
  */

int _strlen(char *ptr)
{
	int str = 0;

	while (*(ptr + str) != '\0')
	{
		str++;
	}
	return (str);
}

#include "shell.h"

/**
 *_isalpha - checks if character passed is alphabet
 *@c: input character
 *Return: on success 1, else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
		return (0);
}

/**
 * _isdelim - checks if a character is a delimiter
 * @c: char to check
 * @del: delimiter
 * Return: 1 if true, else 0
 */

int _isdelim(char c, char *del)
{
	while (*del)
	{
		if (*del++ == c)
			return (1);
	}
	return (0);
}

/**
 *_atoi - converts a string to int data type
 *@s: string to convert
 *Return: converted int, else 0
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -result;
	else
	{
		result = result;
	}
	return (result);
}

/**
 * _itoa - convert int to string data type
 * @num: vaalue to be converted to string
 * @base: number base of num
 * @flags: num args
 * Return: converted string
 */

char *_itoa(long int num, int base, int flags)
{
	static char *arr, buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _atoi_err - converts string error value to int data type
 * @s: string to be converted
 * Return: converted int, else -1
 */
int _atoi_err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

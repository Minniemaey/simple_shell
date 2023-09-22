#include "shell.h"

/**
 * _putchar - writes the char to stdout
 * @c: char to print
 *
 * Return: On success 1 else -1, errno is set appropriately
 */
int _putchar(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int n;

	if ((n >= WRITE_BUF_SIZE) || (c == BUF_FLUSH))
	{
		write(1, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[n++] = c;
	}
	return (1);
}

/**
 *_puts - prints a passed string to stdout
 *@s: string to be printed
 *
 * Return: 0
 */

void _puts(char *s)
{
	int n = 0;

	if (!s)
		return;
	while (s[n] != '\0')
	{
		_putchar(s[n]);
		n++;
	}
}

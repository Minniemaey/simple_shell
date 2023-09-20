#include "shell.h"

/**
 * _putchar_err - writes the char to stderr
 * @c: char to print
 * Return: On success 1 else -1, errno is set appropriately
 */

int _putchar_err(char c)
{
	static char buff[WRITE_BUF_SIZE];
	static int n;

	if ((c == BUF_FLUSH) || (n >= WRITE_BUF_SIZE))
	{
		write(2, buff, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[n++] = c;
	}
	return (1);
}

/**
 *_puts_err - prints a string
 * @s: string to be printed
 * Return: void
 */

void _puts_err(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar_err(s[i]);
		i++;
	}
}
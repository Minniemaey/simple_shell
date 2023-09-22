#include "shell.h"

/**
 * _putchar_fd - writes char to file descriptor
 * @c: char to be printed
 * @fd: filedescriptor
 * Return: On success 1, else -1 and errno is set appropriately
 */

int _putchar_fd(char c, int fd)
{
	static int n;
	static char buff[WRITE_BUF_SIZE];

	if ((c == BUF_FLUSH) || (n >= WRITE_BUF_SIZE))
	{
		write(fd, buff, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
	{
		buff[n++] = c;
	}
	return (1);
}

/**
 *_puts_fd - prints a string to fd
 * @s: string to be printed
 * @fd: filedescriptor
 *
 * Return: the number of chars put
 */
int _puts_fd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putchar_fd(*s++, fd);
	}
	return (i);
}

/**
 * printdec - prints int to base 10
 * @input: input
 * @fd: filedescriptor
 * Return: number of characters printed
 */

int printdec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _putchar_err;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

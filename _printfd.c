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

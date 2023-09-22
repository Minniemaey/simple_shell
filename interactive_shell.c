#include "shell.h"

/**
 * _isatty - checks if fd is associated with terminal(interactive)
 * @data: struct address
 * Return: 1 if true else 0
 */

int _isatty(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->read_fd <= 2);
}

/**
 * main - shell entry point
 * @agc: arg count
 * @agv: arg []
 *
 * Return: 0 on success
 */
int main(int agc, char **agv)
{
	data_t data[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (agc == 2)
	{
		fd = open(agv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts_err(agv[0]);
				_puts_err(": 0: Can't open this ");
				_puts_err(agv[1]);
				_putchar_err('\n');
				_putchar_err(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->read_fd = fd;
	}
	build_envlist(data);
	rd_hist(data);
	exec_cmd(data, agv);
	return (EXIT_SUCCESS);
}

#include "shell.h"

/**
 * exec_cmd - function that executes command
 * @data: data struct
 * @av: arg []
 * Return: Always 0 (on success) else 1
 */

int exec_cmd(data_t *data, char **av)
{
	ssize_t r = 0;
	int built = 0;

	while (r != -1 && built != -2)
	{
		clr_dat(data);
		if (_isatty(data))
			_puts("$ ");
		_putchar_err(BUF_FLUSH);
		r = rd_line(data);
		if (r != -1)
		{
			init_data(data, av);
			built = fd_built(data);
			if (built == -1)
				findcmd(data);
		}
		else if (_isatty(data))
			_putchar('\n');
		free_dat(data, 0);
	}
	wrt_hist(data);
	free_dat(data, 1);
	if (!_isatty(data) && data->status)
		exit(data->status);
	if (built == -2)
	{
		if (data->err_no == -1)
			exit(data->status);
		exit(data->err_no);
	}
	return (built);
}

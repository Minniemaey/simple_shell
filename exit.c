#include "shell.h"

/**
 * _exitshell - implement exit builtin that exits the shell
 * @data: data struct
 * Return: exit status
 */

int _exitshell(data_t *data)
{
	int i;

	if (data->argv[1])
	{
		i = _atoi_err(data->argv[1]);
		if (i == -1)
		{
			data->status = 2;
			_perror(data, "Illegal number: ");
			_puts_err(data->argv[1]);
			_putchar_err('\n');
			return (1);
		}
		data->err_no = _atoi_err(data->argv[1]);
		return (-2);
	}
	data->err_no = -1;
	return (-2);
}

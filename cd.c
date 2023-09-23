#include "shell.h"

/**
 * _cd - implement cd builtin command
 * @data: data struct
 * Return: Always 0
 */

int _cd(data_t *data)
{
	char *s, *dir, buffer[1024];
	int ch_dir;

	s = getcwd(buffer, 1024); /*curr dir*/
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (data->argv[1])
	{
		ch_dir = chdir(data->argv[1]);
	}
	else
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			ch_dir = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}

	if (ch_dir == -1)
	{
		_perror(data, "can't cd to ");
		_puts_err(data->argv[1]), _putchar_err('\n');
	}
	else
	{
		char new_buffer[1024];
		char *newdir = getcwd(new_buffer, 1024);

		__setenv(data, "OLDPWD", s);
		__setenv(data, "PWD", newdir);
	}
	return (0);
}

/**
 * cd_history - displays command history list
 * @data: data struct
 * Return: 0 on success
 */

int cd_history(data_t *data)
{
	print_list(data->hist);
	return (0);
}

/**
 * cd_help - changes the process current directory
 * @data: data struct type
 * Return: Always 0
 */

int cd_help(data_t *data)
{
	char **arg_arr;

	arg_arr = data->argv;
	_puts("Function call works. No implementation \n");
	if (0)
	{
		_puts(*arg_arr);
	}
	return (0);
}

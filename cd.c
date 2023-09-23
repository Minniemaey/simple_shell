#include "shell.h"

/**
 * _cd - Implement cd builtin command
 * @data: data struct
 * Return: Always 0
 */

int _cd(data_t *data)
{
	char *s, *dir, buffer[1024];
	int ch_dir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	if (data->argv[1])
		if (_strcmp(data->argv[1], "-") == 0)
		{
			dir = _getenv(data, "OLDPWD=");
			if (!dir)
				_puts(s), _putchar('\n');
				return (1);
		}
		else
			dir = data->argv[1];
		ch_dir = chdir(dir);
	else
		dir = _getenv(data, "HOME=");
		if (!dir)
		{
			dir = _getenv(data, "PWD=");
			if (!dir)
				dir = "/";
		}
		ch_dir = chdir(dir);
	if (ch_dir == -1)
	{
		_perror(data, "can't cd to ");
		_puts_err(data->argv[1]);
		_putchar_err('\n');
		return (1);
	}
	else
		__setenv(data, "OLDPWD", _getenv(data, "PWD="));
		__setenv(data, "PWD", getcwd(buffer, 1024));
	return (0); // Success
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


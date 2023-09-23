#include "shell.h"

/**
 * _cd - Implement cd builtin command
 * @data: data struct
 * Return: Always 0
 */

int _cd(data_t *data)
{
	char *dir, buffer[1024];
	int ch_dir;
	char *current_dir = getcwd(buffer, 1024);

	if (!current_dir)
		_puts("getcwd failure");
	if (data->argv[1])
	{
		ch_dir = chdir(data->argv[1]);
	}
	else if (data->argv[1] == NULL || _strcmp(data->argv[1], "") == 0)
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			ch_dir = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
		dir = _getenv(data, "OLDPWD=");
		if (dir == NULL)
			_puts("cd: OLDPWD not set\n");
	if (ch_dir == -1)
	{
		_perror(data, "can't cd to ");
		_puts_err(data->argv[1]), _putchar_err('\n');
	}
	else
	{
		char new_buffer[1024];
		char *newdir = getcwd(new_buffer, 1024);

		if (!newdir)
			_puts("getcwd failure");
		__setenv(data, "OLDPWD", current_dir);
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


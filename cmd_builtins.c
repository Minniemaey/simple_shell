#include "shell.h"

/**
 * _cmdfork - forks a pid to run cmd
 * @data: struct
 * Return: void
 */

void _cmdfork(data_t *data)
{
	pid_t _pid;

	_pid = fork();
	if (_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (_pid == 0)
	{
		if (execve(data->path, data->argv, getenviron(data)) == -1)
		{
			free_dat(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				_perror(data, "Permission denied\n");
		}
	}
}

/**
 * findcmd - find command in path
 * @data: data struct
 * Return: void
 */

void findcmd(data_t *data)
{
	char *path = NULL;
	int i, j;

	data->path = data->argv[0];
	if (data->flag == 1)
	{
		data->err_count++;
		data->flag = 0;
	}
	for (i = 0, j = 0; data->arg[i]; i++)
		if (!_isdelim(data->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = findpath(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		_cmdfork(data);
	}
	else
	{
		if ((_isatty(data) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			_cmdfork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			_perror(data, "not found\n");
		}
	}
}

/**
 * fd_built - finds a builtin command
 * @data: data struct
 * Return: on success 0
 */

int fd_built(data_t *data)
{
	int i, built_param = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit},
		{"env", _env},
		{"help", cd_help},
		{"history", cd_hist},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->err_count++;
			built_param = builtintbl[i].func(data);
			break;
		}
	return (built_param);
}

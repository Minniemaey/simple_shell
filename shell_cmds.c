#include "shell.h"

/**
 * fork_cmd - forks a an exec thread to run cmd
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

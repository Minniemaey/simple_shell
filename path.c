#include "shell.h"

/**
 * _getcwd - creates path name
 * @pathstr:PATH str
 * @start: start idx
 * @stop: stop
 * Return: ptr to buffer
 */

char *_getcwd(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (i = 0, j = start; j < stop; j++)
	{
		if (pathstr[j] != ':')
		{
			buff[i++] = pathstr[j];
		}
	}
	buff[i] = 0;
	return (buff);
}

/**
 * is_cmd - checks if input is executable
 * @data: data struct
 * @path: filepath
 * Return: on success 1
 */

int is_cmd(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * findpath - finds command path
 * @data: data struct
 * @pathstr: PATH string
 * @cmd: cmd to search
 * Return: cmd path
 */

char *findpath(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && search_prefix(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _getcwd(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
			{
				return (path);
			}
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

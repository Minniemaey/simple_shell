#include "shell.h"

/**
 * build_histlist - adds entry to a linked list
 * @data: data struct
 * @buff: buffer
 * @line: history count
 * Return: Always 0
 */

int build_histlist(data_t *data, char *buff, int line)
{
	list_t *node = NULL;

	if (data->hist)
		node = data->hist;
	add_node_end(&node, buff, line);

	if (!data->hist)
		data->hist = node;
	return (0);
}

/**
 * _gethist - gets the history
 * @data: data struct
 * Return: hist file
 */

char *_gethist(data_t *data)
{
	char *buff, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * relist - collates history list after env modifications
 * @data: data struct type
 * Return: new list
 */

int relist(data_t *data)
{
	list_t *node = data->hist;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (data->histcount = i);
}

/**
 * wrt_hist - creates a new file or appends to a file
 * @data: data struct
 * Return: Always 1 (on success)
 */

int wrt_hist(data_t *data)
{
	ssize_t fd;
	char *filename = _gethist(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->hist; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_putchar_fd('\n', fd);
	}
	_putchar_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_hist - reads history from history file
 * @data: data struct
 * Return: histcount
 */

int rd_hist(data_t *data)
{
	int i, n = 0, count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = _gethist(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_histlist(data, buff + n, count++);
			n = i + 1;
		}
	if (n != i)
		build_histlist(data, buff + n, count++);
	free(buff);
	data->histcount = count;
	while (data->histcount-- >= HIST_MAX)
		del_nodeidx(&(data->hist), 0);
	relist(data);
	return (data->histcount);
}

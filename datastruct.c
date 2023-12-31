#include "shell.h"

/**
 * init_dat - initializes data_t struct
 * @data: struct address
 * @av: arg vector
 */
void init_dat(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = _strtok(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		rep_alias(data);
		rep_var(data);
	}
}

/**
 * free_dat - frees data_t parameters
 * @data: struct address
 * @n: parameters to free
 */
void free_dat(data_t *data, int n)
{
	free_str(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (n)
	{
		if (!data->cmd_buff)
			free(data->arg);
		if (data->env)
			free_nodes(&(data->env));
		if (data->hist)
			free_nodes(&(data->hist));
		if (data->alias)
			free_nodes(&(data->alias));
		free_str(data->environ);
			data->environ = NULL;
		_free((void **)data->cmd_buff);
		if (data->read_fd > 2)
			close(data->read_fd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clr_dat - clears struct data_t
 * @data: struct address
 */

void clr_dat(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

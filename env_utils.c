#include "shell.h"

/**
 * __setenv - Initialize a new or modifies an existing environment variable
 * @data: data struct
 * @var: environ name
 * @value: environ value
 *  Return: Always 0
 */

int __setenv(data_t *data, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = data->env;
	while (node)
	{
		p = search_prefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			data->n_environ = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buff, 0);
	free(buff);
	data->n_environ = 1;
	return (0);
}

/**
 * _setenv - Initializes a new or modify an existing environment variable
 * @data: data struct
 * Return: Always 0
 */

int _setenv(data_t *data)
{
	if (data->argc != 3)
	{
		_puts_err("Wrong  number of arguments\n");
		return (1);
	}
	if (__setenv(data, data->argv[1], data->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * __unsetenv - deletes an environment variable
 * @data: data struct
 * @var: environ name
 * Return: on success 0
 */
int __unsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = search_prefix(node->str, var);
		if (p && *p == '=')
		{
			data->n_environ = del_nodeidx(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->n_environ);
}

/**
 * _unsetenv - deletes an environment variable
 * @data: data struct
 * Return: on success 0
 */

int _unsetenv(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_puts_err("Too few arguments\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
	{
		__unsetenv(data, data->argv[i]);
	}
	return (0);
}

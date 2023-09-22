#include "shell.h"

/**
 * reset_alias - resets alias
 * @data: data struct
 * @str: str to set
 * Return: Always 0
 */

int reset_alias(data_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (set_alias(data, str));
	}

	set_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * set_alias - set alias
 * @data: data struct
 * @str: str alias
 * Return: Always 0
 */

int set_alias(data_t *data, char *str)
{
	char *p, c;
	int s;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	s = del_nodeidx(&(data->alias),
		find_nodeidx(data->alias, find_node_prefix(data->alias, str, -1)));
	*p = c;
	return (s);
}

/**
 * print_alias - prints an alias str to stdout
 * @node: ptr to node
 * Return: Null
 */

int print_alias(list_t *node)
{
	char *p = NULL, *q = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (q = node->str; q <= p; q++)
			_putchar(*q);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * replace_alias - replaces an alias
 * @data: data struct
 * Return: on success 1
 */

int replace_alias(data_t *data)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = find_node_prefix(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}


/**
 * _alias - implement alias builtin command
 * @data: data struct
 * Return: 0 on success
 */

int _alias(data_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _strchr(data->argv[i], '=');
		if (p)
			reset_alias(data, data->argv[i]);
		else
			print_alias(find_node_prefix(data->alias, data->argv[i], '='));
	}

	return (0);
}

#include "shell.h"

/**
 * _env - builtin prints the current environment
 * @data: data struct
 * Return: Always 0 (success)
 */

int _env(data_t *data)
{
	print_liststr(data->env);
	return (0);
}

/**
 * _getenv - gets the value of environment variables
 * @data: data struct
 * @name: environment  variable name
 * Return: env value, else null
 */

char *_getenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = search_prefix(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * __getenv - gets string value of environment variable
 * @data: data struct type
 * Return: environ
 */

char **__getenv(data_t *data)
{
	if (!data->environ || data->n_environ)
	{
		data->environ = list_str(data->env);
		data->n_environ = 0;
	}

	return (data->environ);
}


/**
 * build_envlist - builds up  env linked list
 * @data: data struct
 * Return: Always 0
 */

int build_envlist(data_t *data)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
	{
		add_node_end(&node, environ[s], 0);
	}
	data->env = node;
	return (0);
}

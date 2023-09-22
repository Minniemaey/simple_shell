#include "shell.h"

/**
 * handle_comments - replaces first instance of '#' with '\0'
 * @buffer: ptr to string
 * Return: Always 0;
 */

void handle_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}

/**
 * replace_str - function that replaces a string
 * @old: double ptr to old str
 * @new: new str
 * Return: 1 on success
 */

int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_var - hadles variable replacement
 * @data: data struct
 * Return: on success 1
 */

int replace_var(data_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			replace_str(&(data->argv[i]),
				_strdup(_itoa(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			replace_str(&(data->argv[i]),
				_strdup(_itoa(getpid(), 10, 0)));
			continue;
		}
		node = find_node_prefix(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_str(&(data->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_str(&data->argv[i], _strdup(""));

	}
	return (0);
}

#include "shell.h"

/**
 * search_prefix - checks if a string begins with a given prefix
 * @haystack: string to search
 * @needle: string to search for
 * Return: ptr to next char in string
 */

char *search_prefix(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * is_chdel - checks for chain delimeter in buffer
 * @data: data struct
 * @buf: buffer
 * @p: ptr to buffer
 * Return: 1 if true
 */

int is_chdel(data_t *data, char *buf, size_t *p)
{
	size_t s = *p;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[s] == ';')
	{
		buf[s] = 0;
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = s;
	return (1);
}

/**
 * chk_buff- checks buffer chains
 * @data: datastruct
 * @buff: buffer
 * @p: ptr to current buff
 * @i: buffer start
 * @len: buffer size
 * Return: void
 */

void chk_buff(data_t *data, char *buff, size_t *p, size_t i, size_t len)
{
	size_t size = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buff[i] = 0;
			size = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buff[i] = 0;
			size = len;
		}
	}

	*p = size;
}

#include "shell.h"

/**
 * _getline - reads input from user
 * @data: struct
 * @ptr: pointer to buffer
 * @size: buffer size
 * Return: size
 */

int _getline(data_t *data, char **ptr, size_t *size)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		s = *size;
	if (i == len)
		i = len = 0;

	r = rd_buff(data, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_str_concat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (size)
		*size = s;
	*ptr = p;
	return (s);
}

/**
 * rd_buff - reads a buffer
 * @data: struct
 * @buff: buffer
 * @s: buffer size
 * Return: size
 */

ssize_t rd_buff(data_t *data, char *buff, size_t *s)
{
	ssize_t i = 0;

	if (*s)
		return (0);
	i = read(data->read_fd, buff, READ_BUF_SIZE);
	if (i >= 0)
		*s = i;
	return (i);
}

/**
 * _getbuff - gets number of bytes in buffer
 * @data: struct
 * @buff: buffer pointer
 * @len: size
 * Return: bytes number
 */

ssize_t _getbuff(data_t *data, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/*bfree((void **)info->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _sigint);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(data, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			data->flag = 1;
			handle_comments(*buff);
			build_histlist(data, *buff, data->histcount++);
			{
				*len = r;
				data->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * rd_line - reads command line
 * @data: struct
 * Return: line
 */

ssize_t rd_line(data_t *data)
{
	static char *buff;
	static size_t s1, s2, len;
	ssize_t r = 0;
	char **buff_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	r = _getbuff(data, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		s2 = s1;
		p = buff + s1;

		chk_buff(data, buff, &s2, s1, len);
		while (s2 < len)
		{
			if (is_chdel(data, buff, &s2))
				break;
			s2++;
		}

		s1 = s2 + 1;
		if (s1 >= len)
		{
			s1 = len = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (r);
}

/**
 * _sigint - handle to blocks ctrl-C prompt
 * @sig: signalhandler
 * Return: void
 */

void _sigint(__attribute__((unused))int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

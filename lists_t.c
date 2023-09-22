#include "shell.h"

/**
 * _listlen - prints the length of a linked list
 * @h: head node ptr
 * Return: size of list_t
 */

size_t _listlen(const list_t *h)
{
	size_t size = 0;

	while (h)
	{
		h = h->next;
		size++;
	}
	return (size);
}

/**
 * list_str - returns an array of strings in linked list
 * @head: head node ptr
 * Return: str []
 */

char **list_str(list_t *head)
{
	list_t *node = head;
	size_t i = _listlen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
	{
		return (NULL);
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
	{
		return (NULL);
	}
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_liststr - prints str element of list_t
 * @h: head node of list_t
 * Return: size
 */

size_t print_liststr(const list_t *h)
{
	size_t size = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		size++;
	}
	return (size);
}

/**
 * print_list - prints all elements of list_t
 * @h: node pointer
 * Return: size
 */

size_t print_list(const list_t *h)
{
	size_t size = 0;

	while (h)
	{
		_puts(_itoa(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		size++;
	}
	return (size);
}

/**
 * free_nodes - frees all nodes of list_t
 * @hptr: double ptr to node
 * Return: void
 */

void free_nodes(list_t **hptr)
{
	list_t *node, *next_node, *head;

	if (!hptr || !*hptr)
	{
		return;
	}
	head = *hptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hptr = NULL;
}

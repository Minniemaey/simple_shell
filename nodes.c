#include "shell.h"

/**
 * add_node - adds a new node at the beginning of a linked list
 * @head: pointer to the head node
 * @str: new str to add in the node
 * @n: node index
 * Return: ptr to new node
 */

list_t *add_node(list_t **head, const char *str, int n)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->n = n;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a new node to the end of a linked list
 * @head: double pointer to head node
 * @str: new element to add
 * @n: node index used by history
 * Return: address of new node or NULL
 */

list_t *add_node_end(list_t **head, const char *str, int n)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->n = n;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * find_node_prefix - returns node whose string starts with prefix
 * @node: ptr to head node
 * @prefix: match to query
 * @c: next char
 * Return: a match  or NULL
 */

list_t *find_node_prefix(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = search_prefix(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * find_nodeidx - gets the index of a node
 * @head: list_t head node
 * @node: ptr to node
 * Return: index else -1
 */

ssize_t find_nodeidx(list_t *head, list_t *node)
{
	size_t size = 0;

	while (head)
	{
		if (head == node)
		{
			return (size);
		}
		head = head->next;
		size++;
	}
	return (-1);
}

/**
 * del_nodeidx - deletes a list_t node at given index
 * @head: head node of list_t
 * @idx: index of node to be deleted
 * Return: 1 on success else 0
 */

int del_nodeidx(list_t **head, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

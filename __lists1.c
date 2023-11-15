#include "shell.h"

/**
 * list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strs - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strs(list_s *h)
{
	list_s *node = h;
	size_t i = list_length(h), j;
	char **strings;
	char *string;

	if (!h || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(jk__strlength(node->str) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		string = jk__strcopy(string, node->str);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * print_lists - prints all elements of a list_s linked list
 * @head: pointer to first node
 *
 * Return: size of linked list
 */
size_t print_lists(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		jk__puts(conv_num(head->num, 10, 0));
		jk__putchar(':');
		jk__putchar(' ');
		jk__puts(head->str ? head->str : "(nil)");
		jk__puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to first node
 * @prefix: string to match
 * @ch: the next character after prefix to match
 *
 * Return: matched node or NULL
 */
list_s *node_starts_with(list_s *node, char *prefix, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = jk__starts_with(node->str, prefix);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_s *h, list_s *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}

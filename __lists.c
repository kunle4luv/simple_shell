#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_s *add_node(list_s **head, const char *string, int n)
{
	list_s *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_s));
	if (!new_head)
		return (NULL);
	__memset((void *)new_head, 0, sizeof(list_s));
	new_head->num = n;
	if (string)
	{
		new_head->str = jk__strduplicate(string);
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
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
list_s *add_node_end(list_s **head, const char *string, int n)
{
	list_s *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);
	__memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = n;
	if (string)
	{
		new_node->str = jk__strduplicate(string);
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
 * str_list_print - prints only the str element of a list_s linked list
 * @head: pointer to head node
 *
 * Return: size of list
 */
size_t str_list_print(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		jk__puts(head->str ? head->str : "(nil)");
		jk__puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @h: address of pointer to head node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_s **h, unsigned int indx)
{
	list_s *node, *prev_node;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!indx)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == indx)
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

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_s **head_ptr)
{
	list_s *node, *next_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	node = h;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

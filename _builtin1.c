#include "shell.h"

/**
 * jk__hist - displays the history list, one command by line, preceeded
 *              with line numbers, starting at 0.
 * @info: structure address
 *  Return: Always 0
 */
int jk__hist(info_s *info)
{
	print_lists(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_s *info, char *s)
{
	char *ptr, chr;
	int _ret;

	ptr = __strchar(s, '=');
	if (!ptr)
		return (1);
	chr = *ptr;
	*ptr = 0;
	_ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*ptr = chr;
	return (_ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_s *info, char *string)
{
	char *ptr;

	ptr = __strchar(string, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, string));

	unset_alias(info, string);
	return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *ptr = NULL, *str = NULL;

	if (node)
	{
		ptr = __strchar(node->str, '=');
		for (str = node->str; str <= ptr; str++)
			jk__putchar(*str);
		jk__putchar('\'');
		jk__puts(ptr + 1);
		jk__puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * jk__alias - mimics the alias builtin (man alias)
 * @info: struct address
 *  Return: Always 0
 */
int jk__alias(info_s *info)
{
	int i = 0;
	char *ptr = NULL;
	list_s *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = __strchar(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

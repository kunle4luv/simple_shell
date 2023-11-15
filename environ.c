#include "shell.h"

/**
 * jk__env - prints the current environment
 * @info: structure address
 * Return: Always 0
 */
int jk__env(info_s *info)
{
	str_list_print(info->env);
	return (0);
}

/**
 * jk__getenv - gets the value of an environ variable
 * @info: structure address
 * @name: environment variable name
 *
 * Return: the value
 */
char *jk__getenv(info_s *info, const char *name)
{
	list_s *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = jk__starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * jk__setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: struct address
 *  Return: Always 0
 */
int jk__setenv(info_s *info)
{
	if (info->argc != 3)
	{
		error_puts("Incorrect number of arguments!\n");
		return (1);
	}
	if (__setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * jk__unsetenv - Remove an environment variable
 * @info: struct with constant prototypes.
 *  Return: Always 0
 */
int jk__unsetenv(info_s *info)
{
	int i;

	if (info->argc == 1)
	{
		error_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		__unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * jk__populate_environ_list - populates environ linked list
 * @info: struct with constant prototypes.
 * Return: Always 0
 */
int jk__populate_environ_list(info_s *info)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}


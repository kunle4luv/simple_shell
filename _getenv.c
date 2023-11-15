#include "shell.h"

/**
 * __get_env - returns the string array copy of our environ
 * @info: infor struct
 * Return: Always 0
 */
char **__get_env(info_s *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = list_to_strs(info->env);
		info->environ_changed = 0;
	}

	return (info->environ);
}

/**
 * __unsetenv - Remove an environment variable
 * @info: struct with constant prototypes
 * @var: the string env variable property
 *
 *  Return: 1 on delete, 0 otherwise
 */
int __unsetenv(info_s *info, char *var)
{
	list_s *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = jk__starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->environ_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->environ_changed);
}

/**
 * __setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: struct with constant prototypes
 * @var: the string env var property
 * @val: the string env var value
 *
 *  Return: Always 0
 */
int __setenv(info_s *info, char *var, char *val)
{
	char *buff = NULL;
	list_s *node;
	char *ptr;

	if (!var || !val)
		return (0);

	buff = malloc(jk__strlength(var) + jk__strlength(val) + 2);
	if (!buff)
		return (1);
	jk__strcopy(buff, var);
	jk___strcatenate(buff, "=");
	jk___strcatenate(buff, val);
	node = info->env;
	while (node)
	{
		ptr = jk__starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buff;
			info->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->environ_changed = 1;
	return (0);
}

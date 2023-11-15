#include "shell.h"

/**
 * is_chain_cmd - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_cmd(info_s *info, char *buff, size_t *ptr)
{
	size_t i = *ptr;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buff[i] == ';') /* found end of this command */
	{
		buff[i] = 0; /* replace semicolon with null */
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * chck_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void chck_chain(info_s *info, char *buff, size_t *ptr, size_t i, size_t length)
{
	size_t j = *ptr;

	if (info->command_buffer_type == CMD_AND)
	{
		if (info->st)
		{
			buff[i] = 0;
			j = length;
		}
	}
	if (info->command_buffer_type == CMD_OR)
	{
		if (!info->st)
		{
			buff[i] = 0;
			j = length;
		}
	}

	*ptr = j;
}

/**
 * jk__replace_aliases - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int jk__replace_aliases(info_s *info)
{
	int i;
	list_s *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = __strchar(node->str, '=');
		if (!ptr)
			return (0);
		ptr = jk__strduplicate(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * jk__replace_variables - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int jk__replace_variables(info_s *info)
{
	int i = 0;
	list_s *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!jk__strcompare(info->argv[i], "$?"))
		{
			jk__replace_str(&(info->argv[i]),
				jk__strduplicate(conv_num(info->st, 10, 0)));
			continue;
		}
		if (!jk__strcompare(info->argv[i], "$$"))
		{
			jk__replace_str(&(info->argv[i]),
				jk__strduplicate(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			jk__replace_str(&(info->argv[i]),
				jk__strduplicate(__strchar(node->str, '=') + 1));
			continue;
		}
		jk__replace_str(&info->argv[i], jk__strduplicate(""));

	}
	return (0);
}

/**
 * jk__replace_str - replaces string
 * @prev: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int jk__replace_str(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}


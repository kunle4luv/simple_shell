#include "shell.h"

/**
 * cl__info - clears info_s struct
 * @info: struct address
 */
void cl__info(info_s *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info__set - initializes info_s struct
 * @info: struct address
 * @argv: argument vector
 */
void info__set(info_s *info, char **argv)
{
	int i = 0;

	info->file_name = argv[0];
	if (info->arg)
	{
		info->argv = _str_delim(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = jk__strduplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		jk__replace_aliases(info);
		jk__replace_variables(info);
	}
}

/**
 * free_info - frees info_s struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_s *info, int all)
{
	_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		_ffree(info->environ);
			info->environ = NULL;
		_bfree((void **)info->command_buffer);
		if (info->read_fd > 2)
			close(info->read_fd);
		jk__putchar(BUFFER_FLUSH);
	}
}

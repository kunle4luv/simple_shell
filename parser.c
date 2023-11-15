#include "shell.h"

/**
 * check_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_cmd(info_s *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @path_str: the PATH string
 * @st: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *path_str, int st, int stop)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = st; i < stop; i++)
		if (path_str[i] != ':')
			buff[j++] = path_str[i];
	buff[j] = 0;
	return (buff);
}

/**
 * path_finder - finds cmd in the PATH string
 * @info: info struct containing constant prototypes
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *path_finder(info_s *info, char *path_str, char *command)
{
	int i = 0, pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((jk__strlength(command) > 2) && jk__starts_with(command, "./"))
	{
		if (check_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = duplicate_chars(path_str, pos, i);
			if (!*path)
				jk___strcatenate(path, command);
			else
			{
				jk___strcatenate(path, "/");
				jk___strcatenate(path, command);
			}
			if (check_cmd(info, path))
				return (path);
			if (!path_str[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}


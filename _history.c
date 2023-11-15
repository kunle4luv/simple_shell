#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_s *info)
{
	char *buff, *directory;

	directory = jk__getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) * (jk__strlength(directory) +
	 jk__strlength(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	jk__strcopy(buff, directory);
	jk___strcatenate(buff, "/");
	jk___strcatenate(buff, HISTORY_FILE);
	return (buff);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_s *info)
{
	ssize_t fd;
	char *file_name = get_hist_file(info);
	list_s *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		jk__puts_fd(node->str, fd);
		jk__put_fd('\n', fd);
	}
	jk__put_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @info: the parameter struct
 *
 * Return: hist_count on success, 0 otherwise
 */
int read_hist(info_s *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, read_len, file_size = 0;
	struct stat st;
	char *buff = NULL, *file_name = get_hist_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (file_size + 1));
	if (!buff)
		return (0);
	read_len = read(fd, buff, file_size);
	buff[file_size] = 0;
	if (read_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < file_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_hist_list(info, buff + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buff + last, line_count++);
	free(buff);
	info->hist_count = line_count;
	while (info->hist_count-- >= HISTORY_MAX)
		delete_node_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->hist_count);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @info: struct containing constant prototypes
 * @buff: buffer
 * @linecount: the history linecount, hist_count
 *
 * Return: Always 0
 */
int build_hist_list(info_s *info, char *buff, int linecount)
{
	list_s *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @info: struct containing constant prototypes
 *
 * Return: the new hist_count
 */
int renum_hist(info_s *info)
{
	list_s *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}

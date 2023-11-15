#include "shell.h"

/**
 * input_buf - buffer chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_s *info, char **buff, size_t *length)
{
	ssize_t ret = 0;
	size_t len_ptr = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*_bfree((void **)info->command_buffer);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _sigIntHandler);
#if USE_GETLINE
		ret = getline(buff, &len_ptr, stdin);
#else
		ret = __getline(info, buff, &len_ptr);
#endif
		if (ret > 0)
		{
			if ((*buff)[ret - 1] == '\n')
			{
				(*buff)[ret - 1] = '\0'; /* remove trailing newline */
				ret--;
			}
			info->linecount_flag = 1;
			rmv_comment(*buff);
			build_hist_list(info, *buff, info->hist_count++);
			/* if (__strchar(*buff, ';')) is this a command chain? */
			{
				*length = ret;
				info->command_buffer = buff;
			}
		}
	}
	return (ret);
}

/**
 * get__input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get__input(info_s *info)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t ret = 0;
	char **buff_p = &(info->arg), *ptr;

	jk__putchar(BUFFER_FLUSH);
	ret = input_buf(info, &buff, &length);
	if (ret == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		ptr = buff + i; /* get pointer for return */

		chck_chain(info, buff, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain_cmd(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->command_buffer_type = CMD_NORM;
		}

		*buff_p = ptr; /* pass back pointer to current command position */
		return (jk__strlength(ptr)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from __getline() */
	return (ret); /* return length of buffer from __getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: number of bytes read from the buffer
 */
ssize_t read_buf(info_s *info, char *buff, size_t *i)
{
	ssize_t ret = 0;

	if (*i)
		return (0);
	ret = read(info->read_fd, buff, READ_BUFFER);
	if (ret >= 0)
		*i = ret;
	return (ret);
}

/**
 * __getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int __getline(info_s *info, char **pointer, size_t *length)
{
	static char buff[READ_BUFFER];
	static size_t i, len;
	size_t j;
	ssize_t ret = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *ch;

	ptr = *pointer;
	if (ptr && length)
		s = *length;
	if (i == len)
		i = len = 0;

	ret = read_buf(info, buff, &len);
	if (ret == -1 || (ret == 0 && len == 0))
		return (-1);

	ch = __strchar(buff + i, '\n');
	j = ch ? 1 + (unsigned int)(ch - buff) : len;
	new_ptr = __realloc(ptr, s, s ? s + j : j + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		__strncat(new_ptr, buff + i, j - i);
	else
		__strncpy(new_ptr, buff + i, j - i + 1);

	s += j - i;
	i = j;
	ptr = new_ptr;

	if (length)
		*length = s;
	*pointer = ptr;
	return (s);
}

/**
 * _sigIntHandler - blocks Ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void _sigIntHandler(__attribute__((unused))int sig_num)
{
	jk__puts("\n");
	jk__puts("$ ");
	jk__putchar(BUFFER_FLUSH);
}

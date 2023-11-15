#include "shell.h"

/**
 *error_puts - prints an input string to stderr
 * @string: the string
 *
 * Return: Nothing
 */
void error_puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		error_putchar(string[i]);
		i++;
	}
}

/**
 * error_putchar - writes the character ch to stderr
 * @ch: The character
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_putchar(char ch)
{
	static int i;
	static char buff[WRITE_BUFFER];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER)
	{
		write(2, buff, i);
		i = 0;
	}
	if (ch != BUFFER_FLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 * jk__put_fd - writes the character ch to the given fd
 * @ch: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int jk__put_fd(char ch, int fd)
{
	static int i;
	static char buff[WRITE_BUFFER];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (ch != BUFFER_FLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 *jk__puts_fd - prints an input string to fd
 * @string: the string
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int jk__puts_fd(char *string, int fd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += jk__put_fd(*string++, fd);
	}
	return (i);
}

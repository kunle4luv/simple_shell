#include "shell.h"

/**
 * jk__strcopy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *jk__strcopy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * jk__strduplicate - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *jk__strduplicate(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
}

/**
 *jk__puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void jk__puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		jk__putchar(s[i]);
		i++;
	}
}

/**
 * jk__putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int jk__putchar(char ch)
{
	static int i;
	static char buff[WRITE_BUFFER];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER)
	{
		write(1, buff, i);
		i = 0;
	}
	if (ch != BUFFER_FLUSH)
		buff[i++] = ch;
	return (1);
}


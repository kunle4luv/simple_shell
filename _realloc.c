#include "shell.h"

/**
 *__memset - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@ch: the byte to fill *str with
 *@num: the amount of bytes to be filled
 *Return: (ch) a pointer to the memory area str
 */
char *__memset(char *str, char ch, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		str[i] = ch;
	return (str);
}

/**
 * _ffree - frees a string of strings
 * @ptr_str: string of strings
 */
void _ffree(char **ptr_str)
{
	char **str = ptr_str;

	if (!ptr_str)
		return;
	while (*ptr_str)
		free(*ptr_str++);
	free(str);
}

/**
 * __realloc - reallocates a block of memory
 * @p: pointer to previous malloc'd block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *__realloc(void *p, unsigned int prev_size, unsigned int new_size)
{
	char *pp;

	if (!p)
		return (malloc(new_size));
	if (!new_size)
		return (free(p), NULL);
	if (new_size == prev_size)
		return (p);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		pp[prev_size] = ((char *)p)[prev_size];
	free(p);
	return (pp);
}

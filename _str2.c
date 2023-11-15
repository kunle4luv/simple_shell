#include "shell.h"

/**
 *__strncpy - copies a string
 *@dst: the destination string to be copied to
 *@src: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *__strncpy(char *dst, char *src, int num)
{
	int i, j;
	char *str = dst;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dst[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 *__strncat - concatenates two strings
 *@dst: the first string
 *@src: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *__strncat(char *dst, char *src, int num)
{
	int i, j;
	char *str = dst;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dst[i] = '\0';
	return (str);
}

/**
 *__strchar - locates a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *__strchar(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}


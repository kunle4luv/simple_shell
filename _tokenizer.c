#include "shell.h"

/**
 *_str_delim - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_str_delim(char *s, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **ss;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is__delimeter(s[i], delim) &&
		(is__delimeter(s[i + 1], delim) || !s[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	ss = malloc((1 + num_words) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is__delimeter(s[i], delim))
			i++;
		k = 0;
		while (!is__delimeter(s[i + k], delim) && s[i + k])
			k++;
		ss[j] = malloc((k + 1) * sizeof(char));
		if (!ss[j])
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ss[j][m] = s[i++];
		ss[j][m] = 0;
	}
	ss[j] = NULL;
	return (ss);
}

/**
 * **_str_delim1 - splits a string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_str_delim1(char *str, char delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


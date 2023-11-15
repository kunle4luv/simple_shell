#include "shell.h"


/**
 * interactive_shell - returns true if shell is in interactive shell mode
 * @info: struct address
 *
 * Return: 1 if interactive shell mode, 0 otherwise
 */
int interactive_shell(info_s *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is__delimeter - checks if character is a delimeter
 * @ch: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is__delimeter(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}

/**
 *__isalphabet - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int __isalphabet(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *__atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int __atoi(char *str)
{
	int i, sign = 1, _flag = 0, out;
	unsigned int res = 0;

	for (i = 0;  str[i] != '\0' && _flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			_flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (sign == -1)
		out = -res;
	else
		out = res;

	return (out);
}


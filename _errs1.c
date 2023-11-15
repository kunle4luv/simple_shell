#include "shell.h"

/**
 * __err_atoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int __err_atoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * jk_print_err - prints an error message
 * @info: info struct
 * @err_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void jk_print_err(info_s *info, char *err_str)
{
	error_puts(info->file_name);
	error_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(info->argv[0]);
	error_puts(": ");
	error_puts(err_str);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = jk__putchar;
	int i, count = 0;
	unsigned int abs, curr;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		count++;
	}
	else
		abs = input;
	curr = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * conv_num - converts number to string
 * @num: number to be converted
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *p;
	unsigned long no = num;

	if (!(flags & CONVERT_TO_UNSIGNED) && num < 0)
	{
		no = -num;
		sign = '-';

	}
	arr = flags & CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[no % base];
		no /= base;
	} while (no != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * rmv_comment - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void rmv_comment(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}


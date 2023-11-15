#include "shell.h"

/**
 * jk__exit - exits the shell
 * @info: structure address
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int jk__exit(info_s *info)
{
	int check_exit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		check_exit = __err_atoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->st = 2;
			jk_print_err(info, "Illegal number: ");
			error_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->error_num = __err_atoi(info->argv[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * jk__cd - changes the current directory of the process
 * @info: structure address
 *  Return: Always 0
 */
int jk__cd(info_s *info)
{
	char *s, *directory, buff[READ_BUFFER];
	int chdir_return;

	s = getcwd(buff, READ_BUFFER);
	if (!s)
		jk__puts("getcwd failure\n");
	if (!info->argv[1])
	{
		directory = jk__getenv(info, "HOME=");
		if (!directory)
			chdir_return =
				chdir((directory = jk__getenv(info, "PWD=")) ? directory : "/");
		else
			chdir_return = chdir(directory);
	}
	else if (jk__strcompare(info->argv[1], "-") == 0)
	{
		if (!jk__getenv(info, "OLDPWD="))
		{
			jk__puts(s);
			jk__putchar('\n');
			return (1);
		}
		jk__puts(jk__getenv(info, "OLDPWD=")), jk__putchar('\n');
		chdir_return =
			chdir((directory = jk__getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		jk_print_err(info, "can't cd into ");
		error_puts(info->argv[1]), error_putchar('\n');
	}
	else
	{
		__setenv(info, "OLDPWD", jk__getenv(info, "PWD="));
		__setenv(info, "PWD", getcwd(buff, READ_BUFFER));
	}
	return (0);
}

/**
 * jk__help - changes the current directory of the process
 * @info: structure address
 *  Return: Always 0
 */
int jk__help(info_s *info)
{
	char **arg_array;

	arg_array = info->argv;
	jk__puts("Welcome to the help menu. No functions included yet! \n");
	if (0)
		jk__puts(*arg_array);
	return (0);
}

#include "shell.h"

/**
 * shell_prompt - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_prompt(info_s *info, char **argv)
{
	ssize_t ret = 0;
	int builtin_ret = 0;

	while (ret != -1 && builtin_ret != -2)
	{
		cl__info(info);
		if (interactive_shell(info))
			jk__puts("$ ");
		error_putchar(BUFFER_FLUSH);
		ret = get__input(info);
		if (ret != -1)
		{
			info__set(info, argv);
			builtin_ret = built_in_find(info);
			if (builtin_ret == -1)
				command_find(info);
		}
		else if (interactive_shell(info))
			jk__putchar('\n');
		free_info(info, 0);
	}
	write_hist(info);
	free_info(info, 1);
	if (!interactive_shell(info) && info->st)
		exit(info->st);
	if (builtin_ret == -2)
	{
		if (info->error_num == -1)
			exit(info->st);
		exit(info->error_num);
	}
	return (builtin_ret);
}

/**
 * built_in_find - finds a builtin command
 * @info: info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int built_in_find(info_s *info)
{
	int i, builtin_ret = -1;
	builtinTable builtin_Tbl[] = {
		{"exit", jk__exit},
		{"env", jk__env},
		{"help", jk__help},
		{"history", jk__hist},
		{"setenv", jk__setenv},
		{"unsetenv", jk__unsetenv},
		{"cd", jk__cd},
		{"alias", jk__alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_Tbl[i].type; i++)
		if (jk__strcompare(info->argv[0], builtin_Tbl[i].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtin_Tbl[i].func(info);
			break;
		}
	return (builtin_ret);
}

/**
 * command_find - finds a command in PATH
 * @info: info struct
 *
 * Return: void
 */
void command_find(info_s *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is__delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = path_finder(info, jk__getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmd_for_fork(info);
	}
	else
	{
		if ((interactive_shell(info) || jk__getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && check_cmd(info, info->argv[0]))
			cmd_for_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->st = 127;
			jk_print_err(info, "not found\n");
		}
	}
}

/**
 * cmd_for_fork - forks an exec thread to run cmd
 * @info: info struct
 *
 * Return: void
 */
void cmd_for_fork(info_s *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* Execute command if child process created*/
		if (execve(info->path, info->argv, __get_env(info)) == -1)
		{
			/* Free info struct if child not created with exit status*/
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		/*Wait for child process to be done*/
		wait(&(info->st));
		if (WIFEXITED(info->st))
		{
			info->st = WEXITSTATUS(info->st);
			if (info->st == 126)
				jk_print_err(info, "Permission denied\n");
		}
	}
}


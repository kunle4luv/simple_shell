#include "shell.h"

/**
 * main - entry point of code
 * @argc: argument count
 * @argv: argumen vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_s info[] = { INFO_INIT };
	int fd = 2;

	/* Assemby code for optimization,(adds 3 to fd)*/
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(argv[0]);
				error_puts(": 0: Can't open ");
				error_puts(argv[1]);
				error_putchar('\n');
				error_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = fd;
	}
	jk__populate_environ_list(info);
	read_hist(info);
	shell_prompt(info, argv);
	return (EXIT_SUCCESS);
}


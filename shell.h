#ifndef _SHELL_H_
#define _SHELL_H_

/*Standard header imports*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Check command chaining*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Buffer MACROS*/
#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define BUFFER_FLUSH -1

/* History file formating*/
#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;

/*Functions for convertion */
#define CONVERT_TO_LOWERCASE	1
#define CONVERT_TO_UNSIGNED	2

/* 1 if using system getline() and standard strtok*/
#define USE_GETLINE 0
#define USE_STRTOK 0

/**
 * struct liststring - singly linked list
 * @num: the num
 * @str: a string
 * @next: pointer to next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_s;

/**
 *struct infopass - contains args in for constant prototypes
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from argc
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the line error count
 *@error_num: the error code for exit()s
 *@linecount_flag: if set to on, count this line of input
 *@file_name: the program's filename
 *@env: linked list local copy of environ variables
 *@environ: custom modified copy of environ from local copy of environ
 *@history: the history node
 *@alias: the alias node
 *@environ_changed: set to on, if environ was changed
 *@st: the return status of the last executed command
 *@command_buffer: address of pointer to command_buffer, on if chaining
 *@command_buffer_type: Command type e.g. ||, &&, ;
 *@read_fd: the fd from which to read line input
 *@hist_count: the history line number count
 */
typedef struct infopass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int linecount_flag;
	char *file_name;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int environ_changed;
	int st;

	char **command_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buffer_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int hist_count;
} info_s;

/* Initialization of Info struct*/
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related functions
 *@type: the builtin type command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_s *);
} builtinTable;

/* _history.c */
char *get_hist_file(info_s *info);
int write_hist(info_s *info);
int read_hist(info_s *info);
int build_hist_list(info_s *info, char *buf, int linecount);
int renum_hist(info_s *info);

/* sh_loop.c */
int shell_prompt(info_s *, char **);
int built_in_find(info_s *);
void command_find(info_s *);
void cmd_for_fork(info_s *);

/* parser.c */
int check_cmd(info_s *, char *);
char *duplicate_chars(char *, int, int);
char *path_finder(info_s *, char *, char *);

/*_getline.c */
ssize_t get__input(info_s *);
int __getline(info_s *, char **, size_t *);
void _sigIntHandler(int);

/* _getinfo.c */
void cl__info(info_s *);
void info__set(info_s *, char **);
void free_info(info_s *, int);

/* errs.c */
void error_puts(char *);
int error_putchar(char);
int jk__put_fd(char c, int fd);
int jk__puts_fd(char *str, int fd);

/* _str.c */
int jk__strlength(char *);
int jk__strcompare(char *, char *);
char *jk__starts_with(const char *, const char *);
char *jk___strcatenate(char *, char *);

/* _str1.c */
char *jk__strcopy(char *, char *);
char *jk__strduplicate(const char *);
void jk__puts(char *);
int jk__putchar(char);

/* _str2.c */
char *__strncpy(char *, char *, int);
char *__strncat(char *, char *, int);
char *__strchar(char *, char);

/* environ.c */
char *jk__getenv(info_s *, const char *);
int jk__env(info_s *);
int jk__setenv(info_s *);
int jk__unsetenv(info_s *);
int jk__populate_environ_list(info_s *);

/*_tokenizer.c */
char **_str_delim(char *, char *);
char **_str_delim1(char *, char);

/* _realloc.c */
char *__memset(char *, char, unsigned int);
void _ffree(char **);
void *__realloc(void *, unsigned int, unsigned int);

/* mem.c */
int _bfree(void **);

/* errs1.c */
int __err_atoi(char *);
void jk_print_err(info_s *, char *);
int print_decimal(int, int);
char *conv_num(long int, int, int);
void rmv_comment(char *);

/* _builtin.c */
int jk__exit(info_s *);
int jk__cd(info_s *);
int jk__help(info_s *);

/* _builtin1.c */
int jk__hist(info_s *);
int jk__alias(info_s *);

/* _getenv.c */
char **__get_env(info_s *);
int __unsetenv(info_s *, char *);
int __setenv(info_s *, char *, char *);

/* __lists.c */
list_s *add_node(list_s **, const char *, int);
list_s *add_node_end(list_s **, const char *, int);
size_t str_list_print(const list_s *);
int delete_node_at_index(list_s **, unsigned int);
void free_list(list_s **);

/* __lists1.c */
size_t list_length(const list_s *);
char **list_to_strs(list_s *);
size_t print_lists(const list_s *);
list_s *node_starts_with(list_s *, char *, char);
ssize_t get_node_index(list_s *, list_s *);

/* atoi.c */
int interactive_shell(info_s *);
int is__delimeter(char, char *);
int __isalphabet(int);
int __atoi(char *);

/* variables.c */
int is_chain_cmd(info_s *, char *, size_t *);
void chck_chain(info_s *, char *, size_t *, size_t, size_t);
int jk__replace_aliases(info_s *);
int jk__replace_variables(info_s *);
int jk__replace_str(char **, char *);

#endif


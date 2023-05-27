#ifndef _SHELL_H_
#define _SHELL_H_

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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/* env.c */
char *genv(ino_t *, const char *);
int the_env(ino_t*);
int the_setenv(ino_t *);
int the_unsetenv(ino_t *);
int env_list(ino_t*);

/* environ.c */
char **get_environ(ino_t *);
int unsetenviron(ino_t *, char *);
int setenvron(ino_t *, char *, char *);

/* history.c */
char *ghistoryf(ino_t *ino);
int wrhistory(ino_t *ino);
int rdhistory(ino_t *ino);
int buhistory_list(ino_t *ino, char *buf, int linecount);
int renhistory(ino_t *ino);

/* lists.c */
list_t *addnode(list_t **, const char *, int);
list_t *addnode_end(list_t **, const char *, int);
size_t plist_str(const list_t *);
int deletenode_index(list_t **, unsigned int);
void freed_list(list_t **);

/* lists1.c */
size_t listlen(const list_t *);
char **liststrings(list_t *);
size_t plist(const list_t *);
list_t *starts_with(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* vars.c */
int test_chain(ino_t *, char *, size_t *);
void checking_the_chain(ino_t *, char *, size_t *, size_t, size_t);
int replace_the_alias(ino_t *);
int replace_the_vars(ino_t *);
int replace_the_string(char **, char *);

/**
 * struct liststr - the function that prints singly linked list
 * @num:  number
 * @str:  string
 * @next:  next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passino - the function that contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 */

typedef struct passino
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type;
	int readfd;
	int histcount;
} ino_t;

#define INO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(ino_t *);
} builtin_table;


/* shell_loop.c */
int hsh(ino_t *, char **);
int find_builtin(ino_t *);
void find_cmd(ino_t *);
void fork_cmd(ino_t *);

/* parser.c */
int iscmd(ino_t *, char *);
char *dupchars(char *, int, int);
char *find_cmd_path(ino_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *strnconcat(char *, char *, int);
char *strlchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *fill_memset(char *, char, unsigned int);
void ffreed(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfreed(void **);

/* integer.c */
int active(ino_t *);
int delimeter(char, char *);
int alpha(int);
int atoi(char *);

/* errors1.c */
int _erratoi(char *);
void print_error(ino_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* cdir.c */
int the_exit(ino_t *);
int the_cd(ino_t *);
int the_help(ino_t *);

/* alias.c */
int the_history(ino_t *);
int the_alias(ino_t *);

/* getline.c */
ssize_t get_input(ino_t *);
int _getline(ino_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_ino(ino_t *);
void set_ino(ino_t *, char **);
void free_ino(ino_t *, int);
#endif

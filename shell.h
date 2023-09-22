#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define MAX_BUFFER_SIZE 1024
#define MAX_ARGUMENTS 100

#define USE_GETLINE 0
#define USE_STRKOK 0

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

extern char **environ;

#define HIST_FILE	".simple_shell_"
#define HIST_MAX	4096

/**
 * struct liststr - a singly linked list
 * @n: number
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int n;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct datast - data struct
 *@arg: string from getline
 *@argv: arg vector
 *@path: command path
 *@argc: arg count
 *@err_count: error count
 *@err_no: exit error codes
 *@flag: line counter
 *@fname: program filename
 *@env: linked list of local environ
 *@environ: custom modified copy of environ from LL env
 *@hist: history node
 *@alias: alias node
 *@n_environ: changed environ
 *@status: return status of cmd executed
 *@cmd_buff: address of pointer to cmd_buff
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@read_fd: fd to read line input
 *@histcount: history line number count
 */

typedef struct datast
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int err_count;
	int err_no;
	int flag;
	char *fname;
	list_t *env;
	list_t *hist;
	list_t *alias;
	char **environ;
	int n_environ;
	int status;
	char **cmd_buff;
	int cmd_buf_type;
	int read_fd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builttab - command builtin
 *@type: command flag
 *@func: function
 */

typedef struct builttab
{
	char *type;
	int (*func)(data_t *);
} builtin_table;

/*data struct prototypes*/
void init_dat(data_t *data, char **av);
void free_dat(data_t *data, int n);
void clr_dat(data_t *data);

/*write functions*/
int _putchar(char c);
void _puts(char *s);
int _putchar_fd(char c, int fd);
int _puts_fd(char *s, int fd);
int printdec(int input, int fd);

/*memory handling prototypes*/
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _free(void **);
void free_str(char **);

/*read line functions*/
int _getline(data_t *data, char **ptr, size_t *size);
ssize_t rd_buff(data_t *data, char *buff, size_t *s);
ssize_t _getbuff(data_t *data, char **buff, size_t *len);
ssize_t rd_line(data_t *data);
void _sigint(__attribute__((unused))int sig);

/*error handling functions*/
int _putchar_err(char c);
void _puts_err(char *s);
void _perror(data_t *data, char *err);

/*command execution functions*/
int _isatty(data_t *data);
int main(int agc, char **agv);
int exec_cmd(data_t *data, char **av);
void _cmdfork(data_t *data);
void findcmd(data_t *data);
int fd_built(data_t *data);
int _alias(data_t *data);
int _cd(data_t *data);
int _env(data_t *data);
int _exitshell(data_t *data);

/*custom string functions*/
int _strlen(char *ptr);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);
char *_str_concat(char *dest, char *src, int n);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(const char *s);
char **_strtok(char *str, char *d);
char **tokenizer(char *str, char d);

/*builtin utilities*/
int _isalpha(int c);
int _isdelim(char c, char *del);
int _atoi(char *s);
char *_itoa(long int num, int base, int flags);
int _atoi_err(char *s);
char *search_prefix(const char *haystack, const char *needle);
int is_chdel(data_t *data, char *buf, size_t *p);
void chk_buff(data_t *data, char *buff, size_t *p, size_t i, size_t len);

/*linked list prototypes*/
list_t *add_node(list_t **head, const char *str, int n);
list_t *add_node_end(list_t **head, const char *str, int n);
list_t *find_node_prefix(list_t *node, char *prefix, char c);
ssize_t find_nodeidx(list_t *head, list_t *node);
int del_nodeidx(list_t **head, unsigned int idx);
size_t _listlen(const list_t *h);
char **list_str(list_t *head);
size_t print_liststr(const list_t *h);
size_t print_list(const list_t *h);
void free_nodes(list_t **hptr);

/*path/directory prototypes*/
char *_getcwd(char *pathstr, int start, int stop);
int is_cmd(data_t *data, char *path);
char *findpath(data_t *data, char *pathstr, char *cmd);
int build_histlist(data_t *data, char *buff, int line);
char *_gethist(data_t *data);
int relist(data_t *data);
int wrt_hist(data_t *data);
int rd_hist(data_t *data);

/*alias builtins*/
int reset_alias(data_t *data, char *str);
int set_alias(data_t *data, char *str);
int print_alias(list_t *node);
int rep_alias(data_t *data);

/*cd builtins*/
int cd_history(data_t *data);
int cd_help(data_t *data);

/*env builtins*/
char *_getenv(data_t *data, const char *name);
char **__getenv(data_t *data);
int build_envlist(data_t *data);
int __setenv(data_t *data, char *var, char *value);
int _setenv(data_t *data);
int __unsetenv(data_t *data, char *var);
int _unsetenv(data_t *data);

/*handler functions*/
void handle_comments(char *buffer);
int replace_str(char **old, char *new);
int rep_var(data_t *data);

#endif

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
 * struct liststr - a singly linked list
 * @num: number
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int n;
	char *str;
	struct liststr *next;
} list_t;

/*data struct prototypes*/
void init_dat(data_t *data, char **av);
void free_dat(data_t *data, int n);
void clr_dat(data_t *data);

/*write functions*/
int _putchar(char c);
int _putchar_fd(char c, int fd);
int _puts_fd(char *s, int fd);

/*memory handling prototypes*/
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _free(void **ptr);
void free_str(char **pp);

/*read line functions*/
int _getline(data_t *data, char **ptr, size_t *size);
ssize_t rd_buff(data_t *data, char *buff, size_t *s);
ssize_t _getbuff(data_t *data, char **buff, size_t *len);
ssize_t rd_line(data_t *data);
void _sigint(__attribute__((unused))int sig);

/*error handling functions*/
int _putchar_err(char c);
void _puts_err(char *s);

/*command execution functions*/
void _cmdfork(data_t *data);

/*custom string functions*/
int _strlen(char *ptr);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);
char *_str_concat(char *src, char *dest, int n);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);




#endif

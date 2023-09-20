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
#define MAX_BUFFER_SIZE 1024
#define MAX_ARGUMENTS 100

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

int _getline(char **ptr, size_t *n, FILE *str);

#endif

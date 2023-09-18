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

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGUMENTS 100
extern char **environ;

int _getline(char **ptr, size_t *n, FILE *str);

#endif

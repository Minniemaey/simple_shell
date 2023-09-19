#include "shell.h"

/**
  * **parser - splits the input string
  * @str: string to be split
  *
  * Return: splitted string
  */
char **parser(char *str)
{
	int x;
	char **cmd = NULL, *token, *del = " \n";

	cmd = malloc(sizeof(char *) * 1024);
	if (cmd == NULL)
	{
		perror("Memory Allocation Error");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, del);
	x = 0;
	while (token != NULL)
	{
		cmd[x] = token;
		token = strtok(NULL, del);
		x++;
	}
	cmd[x] = NULL;
	return (cmd);
}

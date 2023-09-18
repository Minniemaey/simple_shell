#include "shell.h"

/**
 * path_dir - link directories in path environment
 * @cmd: pointer to path command
 *
 * Return: directory path
 */

char *path_dir(char *cmd)
{
	int n;
	char *drc[1024], del = '/';
	char *pathname = NULL, *token = NULL;
	char *wd = getcwd(NULL, 0);
	struct stat sb;

	pathname = getenv("PATH");
	token = strtok(pathname, ":");

	if (drc == NULL)
	{
		n = 0;
	}
	while (drc[n] != NULL)
	{
		chdir(drc[n]);
		if (stat(cmd, &sb) == 0)
		{
			drc[n] = _str_concat(drc[n], &del, 1);
			cmd = _strcat(drc[n], cmd);
			break;
		}
		n++;
	}
	chdir(wd);
	return (cmd);
}

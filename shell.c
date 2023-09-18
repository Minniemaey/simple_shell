#include "shell.h"

/**
 * main - entry point to shell program
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment pointer
 *
 * Return: Always 0 on success
 */

int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
int status;
char *buffer = NULL;
size_t buff_size = 0;
pid_t _pid;

signal(SIGINT, SIG_IGN);

while (1)
{
	if (isatty(STDIN_FILENO))
		const char prompt[] = "~$ ";

		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
	if (_getline(&buffer, &buff_size, stdin) == -1)
		break;
	if (buffer == NULL)
		exit(0);
	argv = parser(buffer);
	if (!argv[0])
	{
		free(argv);
		continue;
	}
	_pid = fork();
	if (_pid == 0)
	{
		if (execve(argv[0], argv, envp))
			perror("execve"), exit(EXIT_FAILURE);
			break;
	}
	wait(&status), free(argv);
}
free(buffer);
return (0);
}

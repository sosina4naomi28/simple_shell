#include "shell.h"

/**
 * find_builtin - the function that finds a builtin command
 * @ino: the parameter & return info struct
 * Return: -1,0,1 and 2
 */
int find_builtin(ino_t *ino)
{
	int i, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", exit},
		{"env", zenv},
		{"help", help},
		{"history", zhistory},
		{"setenv", zsetenv},
		{"unsetenv", zunsetenv},
		{"cd", cd},
		{"alias", alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(ino->argv[0], builtintbl[i].type) == 0)
		{
			ino->line_count++;
			built_in_ret = builtintbl[i].func(ino);
			break;
		}
	return (built_in_ret);
}
/**
 * hsh - the function which is main shell loop
 * @ino: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error
 */
int hsh(ino_t *ino, char **av)
{
	ssize_t R = 0;
	int builtin_ret = 0;

	while (R != -1 && builtin_ret != -2)
	{
		clear_ino(ino);
		if (active(ino))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		R = get_input(ino);
		if (R != -1)
		{
			set_ino(ino, av);
			builtin_ret = find_builtin(ino);
			if (builtin_ret == -1)
				find_cmd(ino);
		}
		else if (active(ino))
			_putchar('\n');
		free_ino(ino, 0);
	}
	wrhistory(ino);
	free_ino(ino, 1);
	if (!active(ino) && ino->status)
		exit(ino->status);
	if (builtin_ret == -2)
	{
		if (ino->err_num == -1)
			exit(ino->status);
		exit(ino->err_num);
	}
	return (builtin_ret);
}
/**
 * find_cmd - the function that finds a command in PATH
 * @ino: the parameter
 * Return: void
 */
void find_cmd(ino_t *ino)
{
	char *path = NULL;
	int i, k;

	ino->path = ino->argv[0];
	if (ino->linecount_flag == 1)
	{
		ino->line_count++;
		ino->linecount_flag = 0;
	}
	for (i = 0, k = 0; ino->arg[i]; i++)
		if (!delimeter(ino->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_cmd_path(ino, genv(ino, "PATH="), ino->argv[0]);
	if (path)
	{
		ino->path = path;
		fork_cmd(ino);
	}
	else
	{
		if ((active(ino) || genv(ino, "PATH=")
					|| ino->argv[0][0] == '/') && iscmd(ino, ino->argv[0]))
			fork_cmd(ino);
		else if (*(ino->arg) != '\n')
		{
			ino->status = 127;
			print_error(ino, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks
 * @ino: parameter & return info struct
 * Return: void
 */
void fork_cmd(ino_t *ino)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(ino->path, ino->argv, get_environ(ino)) == -1)
		{
			free_ino(ino, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(ino->status));
		if (WIFEXITED(ino->status))
		{
			ino->status = WEXITSTATUS(ino->status);
			if (ino->status == 126)
				print_error(ino, "Permission denied\n");
		}
	}
}

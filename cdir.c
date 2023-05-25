#include "shell.h"

/**
 * help -the function that changes the current directory of the process
 * @ino: argument
 * Return: Always 0
 */
int help(ino_t *ino)
{
	char **ptr;

	ptr = ino->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ptr);
	return (0);
}
/**
 * exit - the function that exits the shell
 * @ino: argument
 * Return: exits (0) else,argv[0] != "exit"
 */
int exit(ino_t *ino)
{
	int ex;

	if (ino->argv[1])
	{
		ex = _erratoi(ino->argv[1]);
		if (ex == -1)
		{
			ino->status = 2;
			print_error(ino, "Illegal number: ");
			_eputs(ino->argv[1]);
			_eputchar('\n');
			return (1);
		}
		ino->err_num = _erratoi(ino->argv[1]);
		return (-2);
	}
	ino->err_num = -1;
	return (-2);
}
/**
 * cd - the function that changes the current directory of the process
 * @ino: argument
 * Return: Always 0
 */
int cd(ino_t *ino)
{
	char *s, *dir, buffer[1024];
	int cdiret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!ino->argv[1])
	{
		dir = genv(ino, "HOME=");
		if (!dir)
			cdiret = chdir((dir = genv(ino, "PWD=")) ? dir : "/");
		else
			cdiret = chdir(dir);
	}
	else if (_strcmp(ino->argv[1], "-") == 0)
	{
		if (!genv(ino, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(genv(ino, "OLDPWD=")), _putchar('\n');
		cdiret = chdir((dir = genv(ino, "OLDPWD=")) ? dir : "/");
	}
	else
		cdiret = chdir(ino->argv[1]);
	if (cdiret == -1)
	{
		print_error(ino, "can't cd to ");
		_eputs(ino->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(ino, "OLDPWD", genv(ino, "PWD="));
		_setenv(ino, "PWD", getcwd(buffer, 1024));
	}
	return (0);

}

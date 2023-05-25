#include "shell.h"

/**
 * help -the function that changes the current directory of the process
 * @info: argument
 * Return: Always 0
 */
int help(info_t *info)
{
	char **ptr;

	ptr = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ptr);
	return (0);
}
/**
 * exit - exits the shell
 * @info: argument
 * Return: exits (0) if argv[0] != "exit"
 */
int exit(info_t *info)
{
	int ex;

	if (info->argv[1])
	{
		ex = _erratoi(info->argv[1]);
		if (ex == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * cd - the function that changes the current directory of the process
 * @info: argument
 * Return: Always 0
 */
int cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int cdiret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cdiret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cdiret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cdiret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cdiret = chdir(info->argv[1]);
	if (cdiret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


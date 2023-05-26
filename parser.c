#include "shell.h"

/**
 * iscmd - the function that determines if a file is an executable command
 * @ino: info struct
 * @path: to the file
 * Return: 1 success, else 0
 */
int iscmd(ino_t *ino, char *path)
{
	struct stat st;

	(void)ino;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dupchars - the function that duplicates characters
 * @pathstr: the PATH string
 * @start: begging index
 * @stop: ending index
 * Return: pointer to new buffer
 */
char *dupchars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0, j = 0;

	for (j = 0, k = start; k < stop; k++)
		if (pathstr[k] != ':')
			buf[j++] = pathstr[k];
	buf[j] = 0;
	return (buf);
}
/**
 * find_cmd_path - the function that finds this cmd in the PATH string
 * @ino: the info
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_cmd_path(ino_t *ino, char *pathstr, char *cmd)
{
	int k = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (iscmd(ino, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[k] || pathstr[k] == ':')
		{
			path = dupchars(pathstr, curr_pos, k);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (iscmd(ino, path))
				return (path);
			if (!pathstr[k])
				break;
			curr_pos = k;
		}
		k++;
	}
	return (NULL);
}

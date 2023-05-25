#include "shell.h"

/**
 * ghistoryf - on that history file
 * @ino: parameter struct
 * Return: allocated string
 */
char *ghistoryf(ino_t *ino)
{
	char *buf, *dir;

	dir = genv(ino, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * wrhistory - creates a file, or appends to an existing file
 * @ino: the parameter struct
 * Return: 1 success, else -1
 */
int wrhistory(ino_t *ino)
{
	ssize_t fd;
	char *filename = ghistoryf(ino);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	freed(filename);
	if (fd == -1)
		return (-1);
	for (node = ino->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * buhistory_list - functions that adds entry to a history linked list
 * @ino: arguments
 * @buf: buffer
 * @linecount: linecount, histcount
 * Return: 0 success
 */
int buhistory_list(ino_t *ino, char *buf, int linecount)
{
	list_t *Node = NULL;

	if (ino->history)
		Node = ino->history;
	add_Node_end(&Node, buf, linecount);

	if (!ino->history)
		ino->history = Node;
	return (0);
}
/**
 * renhistory - renumbers the history linked list after changes
 * @ino: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */
int renhistory(ino_t *ino)
{
	list_t *Node = ino->history;
	int k = 0;

	while (Node)
	{
		Node->num = k++;
		Node = Node->next;
	}
	return (ino->histcount = k);
}
/**
 * rdhistory -function that reads history from file
 * @ino: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int rdhistory(ino_t *ino)
{
	int k, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = ghistoryf(ino);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (k = 0; k < fsize; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			buhistory_list(ino, buf + last, linecount++);
			last = k + 1;
		}
	if (last != k)
		bulist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (ino->histcount-- >= HIST_MAX)
		deletenode_index(&(ino->history), 0);
	renhistory(ino);
	return (ino->histcount);
}

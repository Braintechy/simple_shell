#include "simple_shell.h"

/**
 * scanhistoryfile - ...
 * @info: ...
 *
 * Return: ...
 */

char *scanhistoryfile(infot *info)
{
	char *buff, *dir;

	dir = _scanenvironment(info, "HOME=");
	if (!dir)
	return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTFILE) + 2));
	if (!buff)
	return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HISTFILE);
	return (buff);
}

/**
 * writehistory - ...
 * @info: ...
 *
 * Return: ...
 */
int writehistory(infot *info)
{
	ssize_t ft;
	char *filename = scanhistoryfile(info);
	listt *node = NULL;

	if (!filename)
	return (-1);

	ft = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (ft == -1)
	return (-1);
	for (node = info->history; node; node = node->follow)
	{
		_putfd(node->str, ft);
		_printfd('\n', ft);
	}
	_printfd(BUFFFLUSH, ft);
	close(ft);
	return (1);
}

/**
 * readhistory - ...
 * @info: ...
 *
 * Return: ...
 */
int readhistory(infot *info)
{
	int j, lasts = 0, linecounts = 0;
	ssize_t ft, rdlength, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = scanhistoryfile(info);

	if (!filename)
	return (0);

	ft = open(filename, O_RDONLY);
	free(filename);
	if (ft == -1)
	return (0);
	if (!fstat(ft, &st))
	fsize = st.st_size;
	if (fsize < 2)
	return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
	return (0);
	rdlength = read(ft, buff, fsize);
	buff[fsize] = 0;
	if (rdlength <= 0)
	return (free(buff), 0);
	close(ft);
	for (j = 0; j < fsize; j++)
	if (buff[j] == '\n')
	{
	buff[j] = 0;
	buildhistorylist(info, buff + lasts, linecounts++);
	lasts = j + 1;
	}
	if (lasts != j)
	buildhistorylist(info, buff + lasts, linecounts++);
	free(buff);
	info->histcount = linecounts;
	while (info->histcount-- >= HIST_MAXIMUM)
	deletenodeatindex(&(info->history), 0);
	renumberhistory(info);
	return (info->histcount);
}

/**
 * buildhistorylist - ...
 * @info: ...
 * @buff: ...
 * @linecounts: ...
 *
 * Return: ...
 */
int buildhistorylist(infot *info, char *buff, int linecounts)
{
	listt *node = NULL;

	if (info->history)
	node = info->history;
	addnodeend(&node, buff, linecounts);

	if (!info->history)
	info->history = node;
	return (0);
}

/**
 * renumberhistory - ...
 * @info: ...
 *
 * Return: ...
 */
int renumberhistory(infot *info)
{
	listt *node = info->history;
	int j = 0;

	while (node)
	{
	node->number = j++;
	node = node->follow;
	}
	return (info->histcount = j);
}

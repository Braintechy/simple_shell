#include "simple_shell.h"

/**
 * iscmd - ...
 * @info: ...
 * @part: ...
 *
 * Return: ...
 */
int iscmd(infot *info, char *part)
{
	struct stat st;

	(void)info;
	if (!part || stat(part, &st))
	return (0);

	if (st.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
}

/**
 * dupchar - ...
 * @partstr: ...
 * @begin: ...
 * @end: ...
 *
 * Return: ...
 */
char *dupchar(char *partstr, int begin, int end)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = begin; j < end; j++)
	if (partstr[j] != ':')
	buf[l++] = partstr[j];
	buf[j] = 0;
	return (buf);
}

/**
 * findpart - ...
 * @info: ...
 * @partstr: ...
 * @cmd: ...
 *
 * Return: ...
 */
char *findpart(infot *info, char *partstr, char *cmd)
{
	int j = 0, currpos = 0;
	char *part;

	if (!partstr)
	return (NULL);
	if ((_strlen(cmd) > 2) && startwith(cmd, "./"))
	{
	if (iscmd(info, cmd))
	return (cmd);
	}
	while (1)
	{
	if (!partstr[j] || partstr[j] == ':')
	{
	part = dupchar(partstr, currpos, j);
	if (!*part)
	_strcat(part, cmd);
	else
	{
	_strcat(part, "/");
	_strcat(part, cmd);
	}
	if (iscmd(info, part))
	return (part);
	if (!partstr[j])
	break;
	currpos = j;
	}
	j++;
	}
	return (NULL);
}

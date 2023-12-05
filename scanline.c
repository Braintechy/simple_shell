#include "simple_shell.h"

/**
 * inputbuf - ...
 * @info: ...
 * @buff: ...
 * @length: ...
 *
 * Return: ...
 */
ssize_t inputbuf(infot *info, char **buff, size_t *length)
{
	ssize_t p = 0;
	size_t lenp = 0;

	if (!*length)
	{
	free(*buff);
	*buff = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	p = getline(buff, &lenp, stdin);
#else
	p = _scanline(info, buff, &lenp);
#endif
	if (p > 0)
	{
	if ((*buff)[p - 1] == '\n')
	{
	(*buff)[p - 1] = '\0';
	p--;
	}
	info->linecountflag = 1;
	removecomment(*buff);
	buildhistorylist(info, *buff, info->histcount++);
	{
	*length = p;
	info->cmdbuff = buff;
	}
	}
	}
	return (p);
}

/**
 * scaninput - ...
 * @info: ...
 *
 * Return: ...
 */
ssize_t scaninput(infot *info)
{
	static char *buff;
	static size_t j, l, length;
	ssize_t p = 0;
	char **bufp = &(info->arg), *r;

	_putchar(BUFFFLUSH);
	p = inputbuf(info, &buff, &length);
	if (p == -1)
	return (-1);
	if (length)
	{
	l = j;
	r = buff + j;

	checkchain(info, buff, &l, j, length);
	while (l < length)
	{
	if (ischain(info, buff, &l))
	break;
	l++;
	}

	j = l + 1;
	if (j >= length)
	{
	j = length = 0;
	info->cmdbufftype = CMDNORMAL;
	}

	*bufp = r;
	return (_strlen(r));
	}

	*bufp = buff;
	return (p);
}

/**
 * readbuf - ...
 * @info: ...
 * @buff: ...
 * @j: ...
 *
 * Return: ...
 */
ssize_t readbuf(infot *info, char *buff, size_t *j)
{
	ssize_t p = 0;

	if (*j)
	return (0);
	p = read(info->readfd, buff, READBUFFSIZE);
	if (p >= 0)
	*j = p;
	return (p);
}

/**
 * _scanline - ...
 * @info: ...
 * @ptrs: ...
 * @len: ...
 *
 * Return: ...
 */
int _scanline(infot *info, char **ptrs, size_t *len)
{
	static char buff[READBUFFSIZE];
	static size_t j, length;
	size_t l;
	ssize_t p = 0, t = 0;
	char *q = NULL, *presentp = NULL, *a;

	q = *ptrs;
	if (q && len)
	t = *len;
	if (j == length)
	j = length = 0;

	p = readbuf(info, buff, &length);
	if (p == -1 || (p == 0 && length == 0))
	return (-1);

	a = _strchr(buff + j, '\n');
	l = a ? 1 + (unsigned int) (a - buff) : length;
	presentp = _alloc(q, t, t ? t + l : l + 1);
	if (!presentp)
	return (q ? free(q), -1 : -1);

	if (t)
	_strncat(presentp, buff + j, l - j);
	else
	_strncpy(presentp, buff + j, l - j + 1);

	t += l - j;
	j = l;
	q = presentp;

	if (len)
	*len = t;
	*ptrs = q;
	return (t);
}

/**
 * sigintHandler - ...
 * @sig_num: ...
 *
 * Return: ...
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_put("\n");
	_put("$ ");
	_putchar(BUFFFLUSH);
}

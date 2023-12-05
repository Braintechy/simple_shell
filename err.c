#include "simple_shell.h"

/**
 * _eprint - ...
 * @str: ...
 *
 * Return: ...
 */
void _eprint(char *str)
{
	int j = 0;

	if (!str)
	return;
	while (str[j] != '\0')
	{
	_eputchar(str[j]);
	j++;
	}
}

/**
 * _eputchar - ...
 * @a: ...
 *
 * Return: ...
 */
int _eputchar(char a)
{
	static int j;
	static char buff[WRITEBUFFSIZE];

	if (a == BUFFFLUSH || j >= WRITEBUFFSIZE)
	{
	write(2, buff, j);
	j = 0;
	}
	if (a != BUFFFLUSH)
	buff[j++] = a;
	return (1);
}

/**
 * _printfd - ...
 * @c: ...
 * @fd: ...
 *
 * Return: ...
 */
int _printfd(char c, int fd)
{
	static int j;
	static char buff[WRITEBUFFSIZE];

	if (c == BUFFFLUSH || j >= WRITEBUFFSIZE)
	{
	write(fd, buff, j);
	j = 0;
	}
	if (c != BUFFFLUSH)
	buff[j++] = c;
	return (1);
}

/**
 * _putfd - ...
 * @str: ...
 * @fd: ...
 *
 * Return: ...
 */
int _putfd(char *str, int fd)
{
	int j = 0;

	if (!str)
	return (0);
	while (*str)
	{
	j += _printfd(*str++, fd);
	}
	return (j);
}

#include "simple_shell.h"

/**
 * _erratoi - ...
 * @t: ...
 * Return: ...
 */
int _erratoi(char *t)
{
	int j = 0;
	unsigned long int results = 0;

	if (*t == '+')
	t++;
	for (j = 0; t[j] != '\0'; j++)
	{
	if (t[j] >= '0' && t[j] <= '9')
	{
	results *= 10;
	results += (t[j] - '0');
	if (results > INT_MAX)
	return (-1);
	}
	else
	return (-1);
	}
	return (results);
}

/**
 * printerror - ...
 * @info: ...
 * @estr: ...
 * Return: ...
 */
void printerror(infot *info, char *estr)
{
	_eprint(info->fname);
	_eprint(": ");
	printd(info->linecount, STDERR_FILENO);
	_eprint(": ");
	_eprint(info->argv[0]);
	_eprint(": ");
	_eprint(estr);
}

/**
 * printd - ...
 * @input: ...
 * @fd: ...
 *
 * Return: ...
 */
int printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, counts = 0;
	unsigned int _abs_, currents;

	if (fd == STDERR_FILENO)
	__putchar = _eputchar;
	if (input < 0)
	{
	_abs_ = -input;
	__putchar('-');
	counts++;
	}
	else
	_abs_ = input;
	currents = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
	if (_abs_ / j)
	{
	__putchar('0' + currents / j);
	counts++;
	}
	currents %= j;
	}
	__putchar('0' + currents);
	counts++;

	return (counts);
}

/**
 * changenumber - ...
 * @number: ...
 * @bases: ...
 * @flag: ...
 *
 * Return: ...
 */
char *changenumber(long int number, int bases, int flag)
{
	static char *arrays;
	static char buffer[50];
	char signs = 0;
	char *ptrs;
	unsigned long m = number;

	if (!(flag & CHANGEUNSIGNED) && number < 0)
	{
	m = -number;
	signs = '-';

	}
	arrays = flag & CHANGELOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';

	do{
	*--ptrs = arrays[m % bases];
	m /= bases;
	} while (m != 0);

	if (signs)
	*--ptrs = signs;
	return (ptrs);
}

/**
 * removecomment - ...
 * @buff: ...
 *
 * Return: ...
 */
void removecomment(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
	if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
	{
	buff[j] = '\0';
	break;
	}
}

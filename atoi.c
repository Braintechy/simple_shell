#include "simple_shell.h"

/**
 * interactive - ..
 * @info: ..
 *
 * Return: ..
 */
int interactive(infot *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isdelim - ..
 * @a: ..
 * @del: ..
 * Return: ..
 */
int isdelim(char a, char *del)
{
	while (*del)
	if (*del++ == a)
	return (1);
	return (0);
}

/**
 * _isalpha - ...
 * @a: ...
 * Return: ...
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 * _atoi - ....
 * @t: ...
 * Return: ...
 */

int _atoi(char *t)
{
	int j, signs = 1, flags = 0, outputs;
	unsigned int results = 0;

	for (j = 0;  t[j] != '\0' && flags != 2; j++)
	{
	if (t[j] == '-')
	signs *= -1;

	if (t[j] >= '0' && t[j] <= '9')
	{
	flags = 1;
	results *= 10;
	results += (t[j] - '0');
	}
	else if (flags == 1)
	flags = 2;
	}

	if (signs == -1)
	outputs = -results;
	else
	outputs = results;

	return (outputs);
}

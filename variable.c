#include "simple_shell.h"

/**
 * ischain - ...
 * @info: ...
 * @buff: ...
 * @r: ...
 *
 * Return: ...
 */
int ischain(infot *info, char *buff, size_t *r)
{
	size_t i = *r;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
	buff[i] = 0;
	i++;
	info->cmdbufftype = CMDIF;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
	buff[i] = 0;
	i++;
	info->cmdbufftype = CMDBUT;
	}
	else if (buff[i] == ';')
	{
	buff[i] = 0;
	info->cmdbufftype = CMDSTRING;
	}
	else
	return (0);
	*r = i;
	return (1);
}

/**
 * checkchain - ...
 * @info: ...
 * @buff: ...
 * @r: ...
 * @j: starting position in buf
 * @length: ...
 *
 * Return: ...
 */
void checkchain(infot *info, char *buff, size_t *r, size_t j, size_t length)
{
	size_t l = *r;

	if (info->cmdbufftype == CMDBUT)
	{
	if (info->status)
	{
	buff[j] = 0;
	l = length;
	}
	}
	if (info->cmdbufftype == CMDIF)
	{
	if (!info->status)
	{
	buff[j] = 0;
	l = length;
	}
	}

	*r = l;
}

/**
 * replacealias - ...
 * @info: ...
 *
 * Return: ...
 */
int replacealias(infot *info)
{
	int j;
	listt *node;
	char *r;

	for (j = 0; j < 10; j++)
	{
	node = nodestartwith(info->alias, info->argv[0], '=');
	if (!node)
	return (0);
	free(info->argv[0]);
	r = _strchr(node->str, '=');
	if (!r)
	return (0);
	r = _strdup(r + 1);
	if (!r)
	return (0);
	info->argv[0] = r;
	}
	return (1);
}

/**
 * replacevar - ...
 * @info: ...
 *
 * Return: ...
 */
int replacevar(infot *info)
{
	int j = 0;
	listt *node;

	for (j = 0; info->argv[j]; j++)
	{
	if (info->argv[j][0] != '$' || !info->argv[j][1])
	continue;

	if (!_strcmp(info->argv[j], "$?"))
	{
	replacestring(&(info->argv[j]),
	_strdup(changenumber(info->status, 10, 0)));
	continue;
	}
	if (!_strcmp(info->argv[j], "$$"))
	{
	replacestring(&(info->argv[j]),
	_strdup(changenumber(getpid(), 10, 0)));
	continue;
	}
	node = nodestartwith(info->environment, &info->argv[j][1], '=');
	if (node)
	{
	replacestring(&(info->argv[j]),
	_strdup(_strchr(node->str, '=') + 1));
	continue;
	}
	replacestring(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replacestring - ...
 * @past: ...
 * @present: ...
 *
 * Return: ...
 */
int replacestring(char **past, char *present)
{
	free(*past);
	*past = present;
	return (1);
}

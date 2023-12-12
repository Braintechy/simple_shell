#include "simple_shell.h"

/**
 * _myhistory - ..
 * @info: ..
 * Return: ..
 */
int _myhistory(infot *info)
{
	printlist(info->history);
	return (0);
}

/**
 * unsetalias - ..
 * @info: ..
 * @str: ..
 *
 * Return: ...
 */
int unsetalias(infot *info, char *str)
{
	char *r, a;
	int ret;

	r = _strchr(str, '=');
	if (!r)
	return (1);
	a = *r;
	*r = 0;
	ret = deletenodeatindex(&(info->alias),
	scannodeindex(info->alias, nodestartwith(info->alias, str, -1)));
	*r = a;
	return (ret);
}

/**
 * setalias - ...
 * @info: ...
 * @str: ...
 *
 * Return: ...
 */
int setalias(infot *info, char *str)
{
	char *r;

	r = _strchr(str, '=');
	if (!r)
	return (1);
	if (!*++r)
	return (unsetalias(info, str));

	unsetalias(info, str);
	return (addnodeend(&(info->alias), str, 0) == NULL);
}

/**
 * printalias - ...
 * @node: ...
 *
 * Return: ...
 */
int printalias(listt *node)
{
	char *r = NULL, *c = NULL;

	if (node)
	{
	r = _strchr(node->str, '=');
	for (c = node->str; c <= r; c++)
	_putchar(*c);
	_putchar('\'');
	_put(r + 1);
	_put("'\n");
	return (0);
	}
	return (1);
}

/**
 * _myalias - ...
 * @info: ...
 * Return: ...
 */
int _myalias(infot *info)
{
	int j = 0;
	char *r = NULL;
	listt *node = NULL;

	if (info->argc == 1)
	{
	node = info->alias;
	while (node)
	{
	printalias(node);
	node = node->follow;
	}
	return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
	r = _strchr(info->argv[j], '=');
	if (r)
	setalias(info, info->argv[j]);
	else
	printalias(nodestartwith(info->alias, info->argv[j], '='));
	}

	return (0);
}

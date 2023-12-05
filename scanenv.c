#include "simple_shell.h"

/**
 * scanenviron - ...
 * @info: ...
 * Return: ...
 */
char **scanenviron(infot *info)
{
	if (!info->environ || info->environmentchanged)
	{
	info->environ = listtostring(info->environment);
	info->environmentchanged = 0;
	}

	return (info->environ);
}

/**
 * _unsetenvironment - ...
 * @info: ...
 * @var: ...
 * Return: ...
 */
int _unsetenvironment(infot *info, char *var)
{
	listt *node = info->environment;
	size_t j = 0;
	char *r;

	if (!node || !var)
	return (0);

	while (node)
	{
	r = startwith(node->str, var);
	if (r && *r == '=')
	{
	info->environmentchanged = deletenodeatindex(&(info->environment), j);
	j = 0;
	node = info->environment;
	continue;
	}
	node = node->follow;
	j++;
	}
	return (info->environmentchanged);
}

/**
 * _setenvironment - ...
 * @info: ...
 * @var: ...
 * @value: ...
 * Return: ...
 */
int _setenvironment(infot *info, char *var, char *value)
{
	char *buff = NULL;
	listt *node;
	char *r;

	if (!var || !value)
	return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
	return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->environment;
	while (node)
	{
	r = startwith(node->str, var);
	if (r && *r == '=')
	{
	free(node->str);
	node->str = buff;
	info->environmentchanged = 1;
	return (0);
	}
	node = node->follow;
	}
	addnodeend(&(info->environment), buff, 0);
	free(buff);
	info->environmentchanged = 1;
	return (0);
}

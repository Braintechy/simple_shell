#include "simple_shell.h"

/**
 * _myenvironment -...
 * @info: ...
 * Return: ...
 */
int _myenvironment(infot *info)
{
	printliststr(info->environment);
	return (0);
}

/**
 * _scanenvironment - ...
 * @info: ...
 * @name: ...
 *
 * Return: ...
 */
char *_scanenvironment(infot *info, const char *name)
{
	listt *node = info->environment;
	char *r;

	while (node)
	{
	r = startwith(node->str, name);
	if (r && *r)
	return (r);
	node = node->follow;
	}
	return (NULL);
}

/**
 * _mysetenvironment - ...
 * @info: ...
 * Return: ...
 */
int _mysetenvironment(infot *info)
{
	if (info->argc != 3)
	{
	_eprint("Incorrect number of arguements\n");
	return (1);
	}
	if (_setenvironment(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}

/**
 * _myunsetenvironment - ...
 * @info: ...
 * Return: ...
 */
int _myunsetenvironment(infot *info)
{
	int j;

	if (info->argc == 1)
	{
	_eprint("Too few arguements.\n");
	return (1);
	}
	for (j = 1; j <= info->argc; j++)
	_unsetenvironment(info, info->argv[j]);

	return (0);
}

/**
 * populateenvironmentlist - ...
 * @info: ...
 * Return: ...
 */
int populateenvironmentlist(infot *info)
{
	listt *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
	addnodeend(&node, environ[j], 0);
	info->environment = node;
	return (0);
}

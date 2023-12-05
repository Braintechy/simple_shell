#include "simple_shell.h"

/**
 * clearinfo - ...
 * @info: ...
 */
void clearinfo(infot *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->part = NULL;
	info->argc = 0;
}

/**
 * setinfo - ...
 * @info: ...
 * @av: ...
 */
void setinfo(infot *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
	info->argv = strtow(info->arg, " \t");
	if (!info->argv)
	{

	info->argv = malloc(sizeof(char *) * 2);
	if (info->argv)
	{
	info->argv[0] = _strdup(info->arg);
	info->argv[1] = NULL;
	}
	}
	for (j = 0; info->argv && info->argv[j]; j++)
	;
	info->argc = j;

	replacealias(info);
	replacevar(info);
	}
}

/**
 * freeinfo - ...
 * @info: ...
 * @al: ...
 */
void freeinfo(infot *info, int al)
{
	ffree(info->argv);
	info->argv = NULL;
	info->part = NULL;
	if (al)
	{
	if (!info->cmdbuff)
	free(info->arg);
	if (info->environment)
	freelist(&(info->environment));
	if (info->history)
	freelist(&(info->history));
	if (info->alias)
	freelist(&(info->alias));
	ffree(info->environ);
	info->environ = NULL;
	bfree((void **)info->cmdbuff);
	if (info->readfd > 2)
	close(info->readfd);
	_putchar(BUFFFLUSH);
	}
}

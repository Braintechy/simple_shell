#include "simple_shell.h"

/**
 * hsh - ...
 * @info: ...
 * @av: ...
 *
 * Return: ...
 */
int hsh(infot *info, char **av)
{
	ssize_t p = 0;
	int buildinret = 0;

	while (p != -1 && buildinret != -2)
	{
	clearinfo(info);
	if (interactive(info))
	_put("$ ");
	_eputchar(BUFFFLUSH);
	p = scaninput(info);
	if (p != -1)
	{
	setinfo(info, av);
	buildinret = findbuildin(info);
	if (buildinret == -1)
	findcmd(info);
	}
	else if (interactive(info))
	_putchar('\n');
	freeinfo(info, 0);
	}
	writehistory(info);
	freeinfo(info, 1);
	if (!interactive(info) && info->status)
	exit(info->status);
	if (buildinret == -2)
	{
	if (info->errnumber == -1)
	exit(info->status);
	exit(info->errnumber);
	}
	return (buildinret);
}

/**
 * findbuildin - ...
 * @info: ...
 *
 * Return: ...
 */
int findbuildin(infot *info)
{
	int j, buildinret = -1;
	buildintable buildintbl[] = {
	{"exit", _myexit},
	{"environment", _myenvironment},
	{"help", _myhelp},
	{"history", _myhistory},
	{"setenvironment", _mysetenvironment},
	{"unsetenvironment", _myunsetenvironment},
	{"cd", _mycd},
	{"alias", _myalias},
	{NULL, NULL}
	};

	for (j = 0; buildintbl[j].type; j++)
	if (_strcmp(info->argv[0], buildintbl[j].type) == 0)
	{
	info->linecount++;
	buildinret = buildintbl[j].function(info);
	break;
	}
	return (buildinret);
}

/**
 * findcmd - ...
 * @info: ...
 *
 * Return: ...
 */
void findcmd(infot *info)
{
	char *part = NULL;
	int j, l;

	info->part = info->argv[0];
	if (info->linecountflag == 1)
	{
	info->linecount++;
	info->linecountflag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
	if (!isdelim(info->arg[j], " \t\n"))
	l++;
	if (!l)
	return;

	part = findpart(info, _scanenvironment(info, "PATH="), info->argv[0]);
	if (part)
	{
	info->part = part;
	forkcmd(info);
	}
	else
	{
	if ((interactive(info) || _scanenvironment(info, "PATH=")
	|| info->argv[0][0] == '/') && iscmd(info, info->argv[0]))
	forkcmd(info);
	else if (*(info->arg) != '\n')
	{
	info->status = 127;
	printerror(info, "not found\n");
	}
	}
}

/**
 * forkcmd - ...
 * @info: ...
 *
 * Return: ...
 */
void forkcmd(infot *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
	
	perror("Error:");
	return;
	}
	if (child_pid == 0)
	{
	if (execve(info->part, info->argv, scanenviron(info)) == -1)
	{
	freeinfo(info, 1);
	if (errno == EACCES)
	exit(126);
	exit(1);
	}
	}
	else
	{
	wait(&(info->status));
	if (WIFEXITED(info->status))
	{
	info->status = WEXITSTATUS(info->status);
	if (info->status == 126)
	printerror(info, "Permission denied\n");
	}
	}
}

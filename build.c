#include "simple_shell.h"

/**
 * _myexit - ..
 * @info: ..
 * Return: ..
 */
int _myexit(infot *info)
{
	int exitcheck;

	if (info->argv[1])
	{
	exitcheck = _erratoi(info->argv[1]);
	if (exitcheck == -1)
	{
	info->status = 2;
	printerror(info, "Illegal number: ");
	_eprint(info->argv[1]);
	_eputchar('\n');
	return (1);
	}
	info->errnumber = _erratoi(info->argv[1]);
	return (-2);
	}
	info->errnumber = -1;
	return (-2);
}

/**
 * _mycd - ...
 * @info: ...
 * Return: ...
 */
int _mycd(infot *info)
{
	char *t, *dir, buffer[1024];
	int chdirret;

	t = getcwd(buffer, 1024);
	if (!t)
	_put("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
	dir = _scanenvironment(info, "HOME=");
	if (!dir)
	chdirret = chdir((dir = _scanenvironment(info, "PWD=")) ? dir : "/");
	else
	chdirret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!_scanenvironment(info, "OLDPWD="))
	{
	_put(t);
	_putchar('\n');
	return (1);
	}
	_put(_scanenvironment(info, "OLDPWD=")), _putchar('\n');
	chdirret = chdir((dir = _scanenvironment(info, "OLDPWD=")) ? dir : "/");
	}
	else
	chdirret = chdir(info->argv[1]);
	if (chdirret == -1)
	{
	printerror(info, "can't cd to ");
	_eprint(info->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenvironment(info, "OLDPWD", _scanenvironment(info, "PWD="));
	_setenvironment(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - ...
 * @info: ...
 *  Return: ...
 */
int _myhelp(infot *info)
{
	char **argarray;

	argarray = info->argv;
	_put("help call works. Function not yet implemented \n");
	if (0)
	_put(*argarray);
	return (0);
}

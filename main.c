#include "simple_shell.h"

/**
 * main - ...
 * @ac: ...
 * @av: ...
 *
 * Return: ...
 */
int main(int ac, char **av)
{
	infot info[] = { INFOINIT };
	int ft = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (ft)
	: "r" (ft));

	if (ac == 2)
	{
	ft = open(av[1], O_RDONLY);
	if (ft == -1)
	{
	if (errno == EACCES)
	exit(126);
	if (errno == ENOENT)
	{
	_eprint(av[0]);
	_eprint(": 0: Can't open ");
	_eprint(av[1]);
	_eputchar('\n');
	_eputchar(BUFFFLUSH);
	exit(127);
	}
	return (EXIT_FAILURE);
	}
	info->readfd = ft;
	}
	populateenvironmentlist(info);
	readhistory(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

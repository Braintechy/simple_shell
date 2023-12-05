#include "simple_shell.h"

/**
 * bfree - ...
 * @ptrs: ...
 *
 * Return: ...
 */
int bfree(void **ptrs)
{
	if (ptrs && *ptrs)
	{
	free(*ptrs);
	*ptrs = NULL;
	return (1);
	}
	return (0);
}

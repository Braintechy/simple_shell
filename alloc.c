#include "simple_shell.h"

/**
 *_memset - .. 
 *@t: ..
 *@d: ..
 *@m: ..
 *Return: ...
 */
char *_memset(char *t, char d, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
	t[j] = d;
	return (t);
}

/**
 * ffree - ...
 * @rr: ...
 */
void ffree(char **rr)
{
	char **c = rr;

	if (!rr)
	return;
	while (*rr)
	free(*rr++);
	free(c);
}

/**
 * _alloc - ...
 * @ptr: ...
 * @pastsize: ...
 * @presentsize: ...
 *
 * Return: ...
 */
void *_alloc(void *ptr, unsigned int pastsize, unsigned int presentsize)
{
	char *r;

	if (!ptr)
	return (malloc(presentsize));
	if (!presentsize)
	return (free(ptr), NULL);
	if (presentsize == pastsize)
	return (ptr);

	r = malloc(presentsize);
	if (!r)
	return (NULL);

	pastsize = pastsize < presentsize ? pastsize : presentsize;
	while (pastsize--)
	r[pastsize] = ((char *)ptr)[pastsize];
	free(ptr);
	return (r);
}

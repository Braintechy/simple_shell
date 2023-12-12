#include "simple_shell.h"

/**
 * _strlen - ..
 * @t: ..
 *
 * Return: ..
 */
int _strlen(char *t)
{
	int j = 0;

	if (!t)
	return (0);

	while (*t++)
	j++;
	return (j);
}

/**
 * _strcmp - ..
 * @t1: ..
 * @t2: ..
 *
 * Return: ..
 */
int _strcmp(char *t1, char *t2)
{
	while (*t1 && *t2)
	{
	if (*t1 != *t2)
	return (*t1 - *t2);
	t1++;
	t2++;
	}
	if (*t1 == *t2)
	return (0);
	else
	return (*t1 < *t2 ? -1 : 1);
}

/**
 * startwith - ...
 * @stack: ...
 * @needle: ...
 *
 * Return: ...
 */
char *startwith(const char *stack, const char *needle)
{
	while (*needle)
	if (*needle++ != *stack++)
	return (NULL);
	return ((char *)stack);
}

/**
 * _strcat - ...
 * @destination: ...
 * @src: ...
 *
 * Return: ...
 */
char *_strcat(char *destination, char *src)
{
	char *rets = destination;

	while (*destination)
	destination++;
	while (*src)
	*destination++ = *src++;
	*destination = *src;
	return (rets);
}

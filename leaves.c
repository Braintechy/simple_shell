#include "simple_shell.h"

/**
 * _strncpy - ...
 * @destination: ...
 * @src: ...
 * @m: ...
 * Return: ...
 */
char *_strncpy(char *destination, char *src, int m)
{
	int j, l;
	char *t = destination;

	j = 0;
	while (src[j] != '\0' && j < m - 1)
	{
	destination[j] = src[j];
	j++;
	}
	if (j < m)
	{
	l = j;
	while (l < m)
	{
	destination[l] = '\0';
	l++;
	}
	}
	return (t);
}

/**
 * _strncat - ...
 * @destination: ...
 * @src: ...
 * @m: ...
 * Return: ...
 */
char *_strncat(char *destination, char *src, int m)
{
	int j, l;
	char *t = destination;

	j = 0;
	l = 0;
	while (destination[j] != '\0')
	j++;
	while (src[l] != '\0' && l < m)
	{
	destination[j] = src[l];
	j++;
	l++;
	}
	if (l < m)
	destination[j] = '\0';
	return (t);
}

/**
 * _strchr - ...
 * @t: ...
 * @a: ...
 * Return: ...
 */
char *_strchr(char *t, char a)
{
	do {
	if (*t == a)
	return (t);
	} while (*t++ != '\0');

	return (NULL);
}

#include "simple_shell.h"

/**
 * _strcpy - ...
 * @destination: ...
 * @src: ...
 *
 * Return: ...
 */
char *_strcpy(char *destination, char *src)
{
	int j = 0;

	if (destination == src || src == 0)
	return (destination);
	while (src[j])
	{
	destination[j] = src[j];
	j++;
	}
	destination[j] = 0;
	return (destination);
}

/**
 * _strdup - ...
 * @str: ...
 *
 * Return: ...
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *rets;

	if (str == NULL)
	return (NULL);
	while (*str++)
	len++;
	rets = malloc(sizeof(char) * (len + 1));
	if (!rets)
	return (NULL);
	for (len++; len--;)
	rets[len] = *--str;
	return (rets);
}

/**
 * _put - ...
 * @str: ...
 *
 * Return: ...
 */
void _put(char *str)
{
	int j = 0;

	if (!str)
	return;
	while (str[j] != '\0')
	{
	_putchar(str[j]);
	j++;
	}
}

/**
 * _putchar - ...
 * @a: ...
 *
 * Return: ...
 */
int _putchar(char a)
{
	static int j;
	static char buff[WRITEBUFFSIZE];

	if (a == BUFFFLUSH || j >= WRITEBUFFSIZE)
	{
	write(1, buff, j);
	j = 0;
	}
	if (a != BUFFFLUSH)
	buff[j++] = a;
	return (1);
}

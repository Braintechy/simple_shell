#include "simple_shell.h"

/**
 * strtow - ...
 * @str: ...
 * @b: ...
 * Return: ...
 */

char **strtow(char *str, char *b)
{
	int p, q, r, s, numberword = 0;
	char **m;

	if (str == NULL || str[0] == 0)
	return (NULL);
	if (!b)
	b = " ";
	for (p = 0; str[p] != '\0'; p++)
	if (!isdelim(str[p], b) && (isdelim(str[p + 1], b) || !str[p + 1]))
	numberword++;

	if (numberword == 0)
	return (NULL);
	m = malloc((1 + numberword) * sizeof(char *));
	if (!m)
	return (NULL);
	for (p = 0, q = 0; q < numberword; q++)
	{
	while (isdelim(str[p], b))
	p++;
	r = 0;
	while (!isdelim(str[p + r], b) && str[p + r])
	r++;
	m[q] = malloc((r + 1) * sizeof(char));
	if (!m[q])
	{
	for (r = 0; r < q; r++)
	free(m[r]);
	free(m);
	return (NULL);
	}
	for (s = 0; s < r; s++)
	m[q][s] = str[p++];
	m[q][s] = 0;
	}
	m[q] = NULL;
	return (m);
}

/**
 * strtow2 - ...
 * @str: ...
 * @b: ...
 * Return: ...
 */
char **strtow2(char *str, char b)
{
	int p, q, r, s, numberword = 0;
	char **m;

	if (str == NULL || str[0] == 0)
	return (NULL);
	for (p = 0; str[p] != '\0'; p++)
	if ((str[p] != b && str[p + 1] == b) ||
	(str[p] != b && !str[p + 1]) || str[p + 1] == b)
	numberword++;
	if (numberword == 0)
	return (NULL);
	m = malloc((1 + numberword) * sizeof(char *));
	if (!m)
	return (NULL);
	for (p = 0, q = 0; q < numberword; q++)
	{
	while (str[p] == b && str[p] != b)
	p++;
	r = 0;
	while (str[p + r] != b && str[p + r] && str[p + r] != b)
	r++;
	m[q] = malloc((r + 1) * sizeof(char));
	if (!m[q])
	{
	for (r = 0; r < q; r++)
	free(m[r]);
	free(m);
	return (NULL);
	}
	for (s = 0; s < r; s++)
	m[q][s] = str[p++];
	m[q][s] = 0;
	}
	m[q] = NULL;
	return (m);
}

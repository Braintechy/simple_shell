#include "simple_shell.h"

/**
 * listlen - ...
 * @g: ...
 *
 * Return: ...
 */
size_t listlen(const listt *g)
{
	size_t j = 0;

	while (g)
	{
	g = g->follow;
	j++;
	}
	return (j);
}

/**
 * listtostring - ...
 * @front: ...
 *
 * Return: ...
 */
char **listtostring(listt *front)
{
	listt *node = front;
	size_t j = listlen(front), l;
	char **strs;
	char *str;

	if (!front || !j)
	return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
	return (NULL);
	for (j = 0; node; node = node->follow, j++)
	{
	str = malloc(_strlen(node->str) + 1);
	if (!str)
	{
	for (l = 0; l < j; l++)
	free(strs[l]);
	free(strs);
	return (NULL);
	}

	str = _strcpy(str, node->str);
	strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * printlist - ...
 * @g: ...
 *
 * Return: ...
 */
size_t printlist(const listt *g)
{
	size_t j = 0;

	while (g)
	{
	_put(changenumber(g->number, 10, 0));
	_putchar(':');
	_putchar(' ');
	_put(g->str ? g->str : "(nil)");
	_put("\n");
	g = g->follow;
	j++;
	}
	return (j);
}

/**
 * nodestartwith - ...
 * @node: ...
 * @pre: ...
 * @a: ...
 *
 * Return: ...
 */
listt *nodestartwith(listt *node, char *pre, char a)
{
	char *r = NULL;

	while (node)
	{
	r = startwith(node->str, pre);
	if (r && ((a == -1) || (*r == a)))
	return (node);
	node = node->follow;
	}
	return (NULL);
}

/**
 * scannodeindex - ...
 * @front: ...
 * @node: ...
 *
 * Return: ...
 */
ssize_t scannodeindex(listt *front, listt *node)
{
	size_t j = 0;

	while (front)
	{
	if (front == node)
	return (j);
	front = front->follow;
	j++;
	}
	return (-1);
}

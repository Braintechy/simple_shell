#include "simple_shell.h"

/**
 * addnode - ...
 * @head: ....
 * @str: ...
 * @number: ...
 *
 * Return: ...
 */
listt *addnode(listt **head, const char *str, int number)
{
	listt *presenthead;

	if (!head)
	return (NULL);
	presenthead = malloc(sizeof(listt));
	if (!presenthead)
	return (NULL);
	_memset((void *)presenthead, 0, sizeof(listt));
	presenthead->number = number;
	if (str)
	{
	presenthead->str = _strdup(str);
	if (!presenthead->str)
	{
	free(presenthead);
	return (NULL);
	}
	}
	presenthead->follow = *head;
	*head = presenthead;
	return (presenthead);
}

/**
 * addnodeend - ...
 * @head: ...
 * @str: ...
 * @number: ...
 *
 * Return: ...
 */
listt *addnodeend(listt **head, const char *str, int number)
{
	listt *presentnode, *node;

	if (!head)
	return (NULL);

	node = *head;
	presentnode = malloc(sizeof(listt));
	if (!presentnode)
	return (NULL);
	_memset((void *)presentnode, 0, sizeof(listt));
	presentnode->number = number;
	if (str)
	{
	presentnode->str = _strdup(str);
	if (!presentnode->str)
	{
	free(presentnode);
	return (NULL);
	}
	}
	if (node)
	{
	while (node->follow)
	node = node->follow;
	node->follow = presentnode;
	}
	else
	*head = presentnode;
	return (presentnode);
}

/**
 * printliststr - ...
 * @g: ...
 *
 * Return: ...
 */
size_t printliststr(const listt *g)
{
	size_t j = 0;

	while (g)
	{
	_put(g->str ? g->str : "(nil)");
	_put("\n");
	g = g->follow;
	j++;
	}
	return (j);
}

/**
 * deletenodeatindex - ...
 * @head: ...
 * @index: ...
 *
 * Return: ...
 */
int deletenodeatindex(listt **head, unsigned int index)
{
	listt *node, *prenode;
	unsigned int j = 0;

	if (!head || !*head)
	return (0);

	if (!index)
	{
	node = *head;
	*head = (*head)->follow;
	free(node->str);
	free(node);
	return (1);
	}
	node = *head;
	while (node)
	{
	if (j == index)
	{
	prenode->follow = node->follow;
	free(node->str);
	free(node);
	return (1);
	}
	j++;
	prenode = node;
	node = node->follow;
	}
	return (0);
}

/**
 * freelist - ...
 * @headptr: ...
 *
 * Return: ...
 */
void freelist(listt **headptr)
{
	listt *node, *follownode, *head;

	if (!headptr || !*headptr)
	return;
	head = *headptr;
	node = head;
	while (node)
	{
	follownode = node->follow;
	free(node->str);
	free(node);
	node = follownode;
	}
	*headptr = NULL;
}

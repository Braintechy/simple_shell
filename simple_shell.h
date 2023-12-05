#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READBUFFSIZE 1024
#define WRITEBUFFSIZE 1024
#define BUFFFLUSH -1

#define CMDNORMAL 0
#define CMDIF 1
#define CMDBUT 2
#define CMDSTRING 3

#define CHANGELOWERCASE	1
#define CHANGEUNSIGNED	2

#define USESCANLINE 0
#define USESTRTOK 0

#define HISTFILE ".simple_shell_history"
#define HIST_MAXIMUM 4096

extern char **environ;


/**
 * struct liststr - ...
 * @number: ...
 * @str: ...
 * @follow: ...
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *follow;
} listt;

/**
 *struct pastinfo - ...
 *@arg: ...
 *@argv: ...
 *@part: ...
 *@argc: ...
 *@linecount: ...
 *@errnumber: ...
 *@linecountflag: ...
 *@fname: ...
 *@environment: ...
 *@environ: ...
 *@history: ...
 *@alias: ...
 *@environmentchanged: ...
 *@status: ...
 *@cmdbuff: ...
 *@cmdbufftype: ...
 *@readfd: ...
 *@histcount: ...
 */
typedef struct pastinfo
{
	char *arg;
	char **argv;
	char *part;
	int argc;
	unsigned int linecount;
	int errnumber;
	int linecountflag;
	char *fname;
	listt *environment;
	listt *history;
	listt *alias;
	char **environ;
	int environmentchanged;
	int status;

	char **cmdbuff;
	int cmdbufftype;
	int readfd;
	int histcount;
} infot;

#define INFOINIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct buildin - ...
 *@type: ...
 *@function: ...
 */
typedef struct buildin
{
	char *type;
	int (*function)(infot *);
} buildintable;

int hsh(infot *, char **);
int findbuildin(infot *);
void findcmd(infot *);
void forkcmd(infot *);

int iscmd(infot *, char *);
char *dupchar(char *, int, int);
char *findpart(infot *, char *, char *);


int loophsh(char **);

void _eprint(char *);
int _eputchar(char);
int _printfd(char c, int fd);
int _putfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *startwith(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _put(char *);
int _putchar(char);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_alloc(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(infot *);
int isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void printerror(infot *, char *);
int printd(int, int);
char *changenumber(long int, int, int);
void removecomment(char *);

int _myexit(infot *);
int _mycd(infot *);
int _myhelp(infot *);

int _myhistory(infot *);
int _myalias(infot *);

ssize_t scaninput(infot *);
int _scanline(infot *, char **, size_t *);
void sigintHandler(int);

void clearinfo(infot *);
void setinfo(infot *, char **);
void freeinfo(infot *, int);


char *_scanenvironment(infot *, const char *);
int _myenvironment(infot *);
int _mysetenvironment(infot *);
int _myunsetenvironment(infot *);
int populateenvironmentlist(infot *);

char **scanenviron(infot *);
int _unsetenvironment(infot *, char *);
int _setenvironment(infot *, char *, char *);

char *scanhistoryfile(infot *info);
int writehistory(infot *info);
int readhistory(infot *info);
int buildhistorylist(infot *info, char *buff, int linecount);
int renumberhistory(infot *info);

listt *addnode(listt **, const char *, int);
listt *addnodeend(listt **, const char *, int);
size_t printliststr(const listt *);
int deletenodeatindex(listt **, unsigned int);
void freelist(listt **);

size_t listlen(const listt *);
char **listtostring(listt *);
size_t printlist(const listt *);
listt *nodestartwith(listt *, char *, char);
ssize_t scannodeindex(listt *, listt *);

int ischain(infot *, char *, size_t *);
void checkchain(infot *, char *, size_t *, size_t, size_t);
int replacealias(infot *);
int replacevar(infot *);
int replacestring(char **, char *);

#endif

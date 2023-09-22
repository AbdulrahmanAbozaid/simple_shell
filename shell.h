#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

#define UNUSED(x) ((void)x)
#define MAX_READ_SIZE 1024
#define MAX_WRITE_SIZE 1024
#define BUF_FLUSH -1
#define DELIMS " \t\n"

extern char **environ;
char *readLine(void);
int _strlen(char *s);
char *_strdup(const char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char **splitto(char *ln);
void freeMatrix(char **mat);
int runCmnd(char **cmnd, char **argv, int idx);
char *_getenv(char *name);
char *_strcpy(char *dest, char *src);
char *_getpath(char *command);
char *_itoa_c(int num);
void revStr(char *s, int l);
void putError(char *name, char *cmnd, int idx);

int isInner(char *command);
void runInner(char **command, char **argv, int *status, int idx);
void exitHsh(char **command, char **argv, int *status, int idx);
void putEnv(char **cmnd, int *stato);
int isPos(char *s);
int _atoi_c(char *s);
void rmv_cmnt(char *str);

#endif /* _SHELL_H */

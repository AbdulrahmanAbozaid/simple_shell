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

#define MAX_BUF_SIZE 1024
#define MAX_READ_SIZE 1024
#define BUF_FLUSH -1
#define FLAG_UNSIGNED 2
#define FLAG_LOWERCASE 1
#define NORMAL_MODE 0
#define OR_MODE 1
#define AND_MODE 2
#define CHAIN_MODE 3
#define GETLINE_MODE 0
#define STRTOK_MODE 0
#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY 4096
extern char **environ;
/**
 * struct list - singly linked lst
 * @str: string - (malloc'ed string)
 * @num: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
struct list
{
	char *str;
	int num;
	struct list *next;
};
typedef struct list list_t;
/**
 * struct info - structure
 * @readfd: desc T
 * @line_count: desc T
 * @file_path: desc T
 * @argv: desc T
 * @arg: desc T
 * @path: desc T
 * @argC: desc T
 * @lineCountFlag: desc T
 * @env: desc T
 * @history: desc T
 * @alias: desc T
 * @environment: desc T
 * @envChange: desc T
 * @status: desc T
 * @cmd_buf: desc T
 * @cmd_buf_type: desc T
 * @historyCount: desc T
 * @err_num: desc T
 */
typedef struct info
{
	int readfd;
	unsigned int line_count;
	int err_num;
	char *file_path;
	char **argv;
	char *arg;
	char *path;
	int argC;
	int lineCountFlag;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environment;
	int envChange;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int historyCount;
} info_t;
#define INIT_INFO \
{ \
	0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, NULL,\
		NULL, NULL, NULL, 0, 0, NULL, 0, 0\
}
/**
 * struct builtIn - built-in
 * @typ: string
 * @func: function
 * Description: built-in function
 */
typedef struct builtIn
{
	char *typ;
	int (*func)(info_t *);
} builtin_t;
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *start_by(const char *src, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
void _puts(char *str);
int _putchar(char c);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *str, char c);
char **split(char *src, char *delimiter);
char **split_ch(char *src, char delimiter);
char *_memset(char *s, char b, unsigned int n);
void flushArr(char **arr);
void *_realloc(void *oldMem, unsigned int old_size, unsigned int new_size);
int isActive(info_t *inf);
int is_delim(char c, char *delimiter);
int _atoi(char *str);
int _erratoi(char *src);
void put_err(info_t *inf, char *errstr);
int print_dec(int sin, int fdc);
char *convert_radix(long int num, int radix, int flags);
void rmv_cmnt(char *str);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_ls(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head);
size_t listLength(const list_t *list);
char **listStringfy(list_t *list);
size_t print_list(const list_t *head);
list_t *isNodePrefix(list_t *list, char *prefix, char c);
ssize_t getNodeIndex(list_t *head, list_t *node);
void _eputs(char *str);
int _eputchar(char c);
int putchFD(char ch, int fd);
int _putsFD(char *str, int fd);
void freeInfoT(info_t *info, int al);
void setInfo(struct info *info, char **argv);
void clearInfoT(info_t *info);
int free_nil(void **itr);
int _myenv(info_t *info);
char *getEnv(info_t *info, char *name);
int msetEnvVar(info_t *info);
int munsetEnvVar(info_t *info);
int populate_env_list(info_t *info);
char **getEnvironment(info_t *info);
int unsetEnvVar(info_t *info, char *var);
int setEnvVar(info_t *info, char *var, char *val);
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *data, int size);
int resetHistoryCount(info_t *info);
int mExit(info_t *info);
int mCD(info_t *info);
int mHelp(info_t *info);
int printHistory(info_t *info);
int unsetAlias(info_t *info, char *alias);
int setAlias(info_t *info, char *alias);
int printAlias(list_t *alias);
int printAliasList(info_t *info);
int isExec(info_t *info, char *path);
char *getSubPath(char *pathStr, int begin, int end);
char *findPath(info_t *info, char *pathStr, char *cmd);
int isChained(info_t *info, char *cmd, size_t *s);
void checkChainMode(info_t *info, char *cmd, size_t *curr,
		size_t i, size_t len);
int getAliasVal(info_t *info);
int getVarVal(info_t *info);
int replaceString(char **past, char *new);
ssize_t readBuffer(info_t *info, char **buf, size_t *bufLen);
ssize_t readInput(info_t *info);
ssize_t getInputBuffer(info_t *info, char *buffer, size_t *len);
int getLine(info_t *info, char **dbuf, size_t *len);
void ctrlCHandler(int signum);
int findSuit(info_t *info);
void findCmnd(info_t *info);
void forkCmd(info_t *info);
int hsh(info_t *info, char **argv);

#endif /* _SHELL_H */

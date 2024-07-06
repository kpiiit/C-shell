#ifndef HEADERS_H_
#define HEADERS_H_
#define PROMPT_TEMPLATE "<%s@%s:~%s>"
#define OMPT_TEMPLATE1 "<%s@%s:~>"
#define OMPT_TEMPLATE2 "<%s@%s:~ %s : %d%s>"
#define MAX_TOKENS 32
#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 32
#define MAX_TOKEN_LENGTH 256
#define MAX_SIZE 1024
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
struct ProcessInfo {
    char name[256];
    int pid;
    int q;
    char* kl;
};
typedef struct direc {
    char present[256];
    char homed[256];
} direc;
extern struct ProcessInfo processArray[256];
extern int numProcesses;
extern int flagy;
extern int argc;
extern char* argv1[1024];
extern int stdin_fileno;
extern int stdout_fileno;
extern int flag1;
extern int flag1;
extern int flag5;
extern int flag;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <regex.h>
#include <signal.h>
#include <fcntl.h>  
#include<stdbool.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#endif
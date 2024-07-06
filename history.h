#ifndef __HISTORY_H
#define __HISTORY_H

void addHistory(char*, char*);
char* getHistory(char* , char**,int);
int getHistory1(char*, char**);
int getHistory2(char*, char**);
void purge(char* );
char* ex(char* ,int);
#endif
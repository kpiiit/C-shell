#include "headers.h"
#include "execute.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#define MAX_SIZE 1024

int main4(char *command) {
    int count_pipes = 0;
    for (int j = 0; j < strlen(command); j++) {
        if (command[j] == '|') {
            count_pipes++;
        }
    }

    int count_pipe_commands = 0;
    char *pipe_commands[MAX_SIZE];

    char *tokenize = strtok(command, "|");
    while (tokenize != NULL) {
        pipe_commands[count_pipe_commands++] = tokenize;
        tokenize = strtok(NULL, "|");
    }

    if (count_pipe_commands != count_pipes + 1) {
        perror("Error: pipe: invalid syntax for piping\n");
        return -1;
    }

    int pipe_tube[count_pipe_commands - 1][2]; // One less pipe than commands

    for (int i = 0; i < count_pipe_commands - 1; i++) {
        if (pipe(pipe_tube[i]) == -1) {
            perror("Error: pipe");
            return -1;
        }
    }

    int stdout_fileno = dup(STDOUT_FILENO);
    int stdin_fileno = dup(STDIN_FILENO);

    if (dup2(pipe_tube[0][1], STDOUT_FILENO) < 0) {
        perror("Error: pipe");
        return -1;
    }
    int i=0;
    int flag=0;
    while(i<strlen(pipe_commands[0])){
        //printf("%d",strlen(command));
        if(pipe_commands[0][i]=='>'){
           flag=1;
           //printf("%d",flag);
           break;
        }
        else if(pipe_commands[0][i]=='<'){
            flag=1;
            break;
        }
        else if(pipe_commands[0][i]=='>'&&pipe_commands[0][i+1]=='>'&&(i+1)<strlen(pipe_commands[0])){
          flag=1;
          break;
        }
        i++;
    }
    if(flag==1){
        main3(pipe_commands[0],0);
    }
    else{
    execute(pipe_commands[0]);}
    i=0;
    flag=0;
    close(pipe_tube[0][1]);

    for (int i = 1; i < count_pipe_commands - 1; i++) {
        if (dup2(pipe_tube[i - 1][0], STDIN_FILENO) < 0) {
            perror("Error: pipe");
            return -1;
        }

        if (dup2(pipe_tube[i][1], STDOUT_FILENO) < 0) {
            perror("Error: pipe");
            return -1;
        }

        execute(pipe_commands[i]);
        close(pipe_tube[i][1]);
        close(pipe_tube[i - 1][0]);
    }

    if (dup2(pipe_tube[count_pipe_commands - 2][0], STDIN_FILENO) < 0) {
        perror("Error: pipe");
        return -1;
    }

    if (dup2(stdout_fileno, STDOUT_FILENO) < 0) {
        perror("Error: pipe");
        return -1;
    }
     while(i<strlen(pipe_commands[count_pipe_commands-1])){
        //printf("%d",strlen(command));
        if(pipe_commands[count_pipe_commands-1][i]=='>'){
           flag=1;
           //printf("%d",flag);
           break;
        }
        else if(pipe_commands[count_pipe_commands-1][i]=='<'){
            flag=1;
            break;
        }
        else if(pipe_commands[count_pipe_commands-1][i]=='>'&&pipe_commands[count_pipe_commands-1][i+1]=='>'&&(i+1)<strlen(pipe_commands[count_pipe_commands-1])){
          flag=1;
          break;
        }
        i++;
    }
    if(flag==1){
        main3(pipe_commands[count_pipe_commands-1],0);
    }
    else{
    execute(pipe_commands[count_pipe_commands - 1]);}
    close(pipe_tube[count_pipe_commands - 2][0]);

    if (dup2(stdin_fileno, STDIN_FILENO) < 0) {
        perror("Error: pipe");
        return -1;
    }

    if (dup2(stdout_fileno, STDOUT_FILENO) < 0) {
        perror("Error: pipe");
        return -1;
    }

    return 1;
}

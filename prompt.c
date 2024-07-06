

#include "prompt.h"
#include "headers.h"
void remove_common_prefix(char *str1, char *str2) {
    int length1 = strlen(str1);
    int length2 = strlen(str2);

    int min_length = (length1 < length2) ? length1 : length2;

    int common_length = 0;
    for (int i = 0; i < min_length; i++) {
        if (str1[i] == str2[i]) {
            common_length++;
        } else {
            break;
        }
    }

    if (common_length > 0) {
        memmove(str2, str2 + common_length, length2 - common_length + 1);
    }
}
void prompt(char* cwd,char* username,char* hostname,int flag,char* args,int time){
    char cwd1[PATH_MAX];
        getcwd(cwd1, PATH_MAX);
        if (strcmp(cwd, cwd1) == 0&&flag==3) {
            printf(OMPT_TEMPLATE1, username, hostname);
        } else if(strcmp(cwd, cwd1) != 0&&flag==3){
            remove_common_prefix(cwd,cwd1); 
            //rintf("%s",cwd1);
            printf(PROMPT_TEMPLATE, username, hostname, cwd1);
        }
        else if(flag==4){
            printf(OMPT_TEMPLATE2, username, hostname,args,time,"s");
        }
        
}


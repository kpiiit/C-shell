#include "headers.h"
#include "warp.h"
void warp_to_directory(char *dir,int flag) {
    if (chdir(dir) == -1) {
        perror("chdir");
    } else {
        char cwd[PATH_MAX];
        getcwd(cwd, PATH_MAX);
        if(flag==1){
        printf("%s\n", cwd);}
    }
}

void warp(char* command,char *cwd1,char* cwd2,char** prev,int flag){
                char cwd[1024];
                char *args[MAX_TOKENS];
                int arg_count = 0;
                cwd2=getcwd(cwd,1024);
                int i=0;
                while(prev[i]!=NULL){
                    //printf("%s\n",prev[i]);
                    i++;
                }
                prev[i]=strdup(cwd2);
                
                char *token = strtok(command + 4, " \t");
                if(token==NULL){
                    chdir(cwd1);
                    return;
                }
                

                while (token != NULL) {
                    args[arg_count] = token;
                    arg_count++;
                    token = strtok(NULL, " \t");
                }
                args[arg_count] = NULL;
                
                                //printf("%s",args[0]);
                // Handle different warp cases
                for (int i = 0; i < arg_count; i++) {
                    if(args[i][0]=='~'&&args[i][1]=='/'){
                      int k=0;
                      while(prev[k]!=NULL){
                    //printf("%s\n",prev[i]);
                        k++;
                        }
                        //printf("%d%s\n",k,prev[k-2]);
                        int o=chdir(prev[k-3]);
                        //printf("%d\n",o);
                         getcwd(cwd,1024);
                         prev[k-1]=NULL;
                         prev[k-2]=NULL;
                         prev[k-3]=NULL;
                        //getcwd(cwd,1024);
                        //printf("%s%d\n",cwd,k);
                        
                       
                        int p=2;
                        char we[1024];
                        int l=0;
                        while(args[i][p]!='\0'){
                          we[l]=args[i][p];
                          l++;
                          p++;
                        }
                        we[l]='\0';
                        //printf("1");
                        warp_to_directory(we,flag);
                    }
                    else if (strcmp(args[i], "-") == 0) {
                        // Handle "-" flag
                        // Go back to the previous directory
                        //printf("%s",prev[i-1]);
                        int k=0;
                      while(prev[k]!=NULL){
                    //printf("%s\n",prev[i]);
                        k++;
                        }
                        //printf("%d%s\n",k,prev[k-2]);
                        int o=chdir(prev[k-2]);
                        //printf("%d\n",o);
                         getcwd(cwd,1024);
                         prev[k-1]=NULL;
                         prev[k-2]=NULL;
                         if(flag==1){
                        printf("%s\n",cwd);}
                        
                    } else if (strcmp(args[i], "~") == 0) {
                        // Handle "~" flag
                        // Go to the home directory
                        chdir(cwd1);
                        getcwd(cwd,1024);
                         if(flag==1){
                        printf("%s\n",cwd);}
                    } else if (strcmp(args[i], "..") == 0) {
                        // Handle ".." flag
                        // Go to the parent directory
                        char cwd[PATH_MAX];
                        getcwd(cwd, PATH_MAX);
                        char *cwd_end = strrchr(cwd, '/');
                        if (cwd_end != NULL) {
                            *cwd_end = '\0';
                        }
                        chdir(cwd);
                        getcwd(cwd,1024);
                        if(flag==1){
                        printf("%s\n",cwd);}
                    } else {
                        // Handle regular directory paths
                        warp_to_directory(args[i],flag);
                    }
                }
}
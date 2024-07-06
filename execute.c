#include "headers.h"
#include "prompt.h"
#include "warp.h"
#include "peek.h"
#include "history.h"
#include "pinfo.h"
#include "runner.h"
#include "seek.h"
#include "print.h"
#include "activities.h"
#include "fg.h"
#include "bg.h"
#include "neonate.h"

int fg1=0;
int stdin_fileno;
int stdout_fileno;
void  removeSubstring2(char *str,  char *substr) {
    char *match;
    size_t len = strlen(substr);

    while ((match = strstr(str, substr)) != NULL) {
        memmove(match, match + len, strlen(match + len) + 1);
    }
    //printf("%s\n",str);
}
char cwd1[PATH_MAX];
char username1[LOGIN_NAME_MAX];
char hostname1[HOST_NAME_MAX];
char* prevdir1[1024];
void execute(char* command){
         int dlo=0;
         addHistory(cwd1,command);
         int o;
         int is_background=0;
         char* e;
         int count=0;
         int count3=0;
         char* cwd2=cwd1;
         char* com=strdup(command);
         char* k=getcwd(cwd1,1024);
          while (command[0] == ' ' || command[0] == '\t') {
                command++;
                count3++;
            }
            size_t len = strlen(command);
            char* yu=strdup(command);

            //redirection(command);
         
            //printf("%s",command);

            //if (strncmp(command, "seek", 4) == 0){
          //printf("1");
        
            while (len > 0 && (command[len - 1] == ' ' || command[len - 1] == '\t' || command[len - 1] == '\n')) {
                //printf("%s",command);
                command[len - 1] = '\0';
                len--;
                count3++;
                //printf("%c",command[2]);
                //l--;
            }  
         while(count<strlen(command)){
                //printf("%c",com[count]);
                if(com[count]==';'){
                    is_background=0;
                    count++;
                    //count1++;
                    break;
                    //printf("1");

                }
                else if(com[count]=='&'){
                    is_background=1;
                    count++;
                    char* y=strtok(command,"&");
                    //count1++;
                    break;

                }
                count++;
                //count1++;
            }
               //printf("%s",command);
         if (!strncmp(command, "exit",4)) {
          exit(0);

        }
        else if(!strncmp(command,"neonate",7)){
               //printf("%s",command);
               rip(command);
        }
            else if(!strncmp(command,"fg",2)){
                 char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command + 2, " \t");
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " \t");
            }
            args[arg_count] = NULL;
             if (arg_count < 1) {
            printf("Error: Too few arguments\n");
          } else {
            //int jobNo = 0;
            //sscanf(args[1], "%d", &jobNo);

            //if (jobNo < 1 || jobNo > 99 || bgPid[jobNo] <= 1) {
              //printf("Error: Invalid Job\n");
            //} 
            
              int pid = tichnas_fg(atoi(args[0]));
              if(pid<0){
                 printf("No such process found\n");
              }
              
              //removeBg(pid > 0 ? pid : -pid);

              //if (pid <= 0) error = 1;
          }

        }
         else if (strncmp(command, "seek", 4) == 0){
                //printf("1");
                struct direc* Dir=(struct direc*)malloc(sizeof(struct direc));
                strcpy(Dir->present,".");
                strcpy(Dir->homed,".");
                //printf("1");
                printf("%s",command);
               seek_call(Dir,command);
            }
        else if(!strncmp(command,"bg",2)){
                 char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command + 2, " \t");
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " \t");
            }
            args[arg_count] = NULL;
             if (arg_count < 1) {
            printf("Error: Too few arguments\n");
          } else {
            //int jobNo = 0;
            //sscanf(args[1], "%d", &jobNo);

            //if (jobNo < 1 || jobNo > 99 || bgPid[jobNo] <= 1) {
              //printf("Error: Invalid Job\n");
            //} 
            
              
              int jk=tichnas_bg(atoi(args[0]));
              //removeBg(pid > 0 ? pid : -pid);
              //printf("%d",jk);
              //if (pid <= 0) error = 1;
          }

        }
            else if (strncmp(command, "warp", 4) == 0) {
                //printf("d0ne");
                warp(command,cwd1,cwd2,prevdir1,1);

            }
            else if(strncmp(command, "activities", 10) == 0) {
                //printf("d0ne");
                main1();

            }
            else if (strncmp(command, "proclore", 8) == 0){
                char *token = strtok(command + 8, " \t");
                    tichnas_pinfo(k,token);
            }
             else if (strncmp(command, "iMan", 4) == 0) {
            // Parse the arguments for the peek command
                
            // Parse the arguments for the peek command

            char* t=strdup(command);
            char arg[1024];
            int z=0,f=0;
            while(z<strlen(command)){
                if(z>3){
                    arg[f]=command[z];
                    //printf("%c",arg[f]);
                    f++;
                }
                z++;
            }
          
            arg[f]='\0';
            flag5=1;               
                   
    print_man_page(arg);

}           
                                           
            else if (strncmp(command, "peek", 4) == 0) {
            //char *ol=strdup(command);
            // Parse the arguments for the peek command
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command + 4, " \t");
    
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " \t");
            }
            args[arg_count] = NULL;
                //printf("1");
                //printf("%s",args[0]);
            
            char* path=args[arg_count-1];
            tichnas_ls(args[arg_count-1],args);}
        else if (strncmp(command, "ping", 4) == 0) {
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command + 4, " \t");
    
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " \t");
            }
            args[arg_count] = NULL;
            int pid1 = atoi(args[0]);
            int signal_number1= atoi(args[1]);
            int w;
            signal_number1 = signal_number1 % 32;
            
    // Calculate the actual signal number by taking modulo 32
            

            printf("Sent signal %d to process with pid %d\n",signal_number1,pid1);
            w=deleteProcessByPID(pid1);
            if(w==0){
                printf("No such process found\n");
            }
            else{
            kill(pid1,signal_number1);}
        }
        else if (strncmp(command, "pastevents", 10) == 0) {
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command + 10, " \t");

            if (token != NULL && strcmp(token, "execute") == 0) {
                // Extract the command index
                token = strtok(NULL, " \t");
                if (token != NULL) {
                    int cmd_index = atoi(token);
                    if (cmd_index > 0) {
                        cmd_index=cmd_index-1;
                        char *exec_command = getHistory(k, args, cmd_index);
                        if (exec_command != NULL) {
                            //printf("%s",exec_command);
                           strncpy(com, exec_command, sizeof(com) - 1);
                           com[sizeof(com - 1)] = '\0';
                            flag = 1;
                            return;
                        

                        } else {
                            printf("Error: Command not found in history\n");
                        }
                    }}}
                    else if(token==NULL){
            if(getHistory2(k,args)<0){
               printf("error");
            }}
            
            
            }
         else if (strlen(command) > 0) {
                 //printf("1");
                char* p=strdup(command);
                 e= strtok(p, " \t");
                 //printf("%d",is_background);
                o=runCommand(is_background,command);

                if(o>2&&!is_background){
                    flag1=4;
                    
                }
                
                //continue;
            }  // Check if the file was opened successfully
   
}
int main3(char* command,int l){
    int dlo=0;
    //printf("%s",command);
    int t=0;
    getlogin_r(username1, LOGIN_NAME_MAX);
    gethostname(hostname1, HOST_NAME_MAX);
    getcwd(cwd1,PATH_MAX);
          int argc1 = 0;
    char *argv1[1024];
    bool input = false;
    bool output = false;
    bool append = false;
    char input_file[1024];
    char output_file[1024];
    //printf("%s",command);
    int k=0;
    while(k<l){
        if(command[k]==';'){
           t=1;
           break;
        }
        k++;
    }
    int o=0;
     char *args[1024];
            int arg_count = 0;
            if(t==1){
            char *token = strtok(command, ";");
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, ";");
            }
            args[arg_count] = NULL;
            for(int u=0;u<arg_count;u++){
                if(strstr(args[u],">")){
                    o=u;
                    break;
                }
                else if(strstr(args[u],">>")){
                    o=u;
                    break;
                }
                else if(strstr(args[u],"<")){
                    o=u;
                    break;
                }
                execute(args[u]);
            }
            }
            char* tokenize;
    if(t==1){
    tokenize = strtok(args[o], " ");}
    else{
    tokenize = strtok(command, " ");
    }
    while (tokenize != NULL) {
        argv1[argc1++] = tokenize;
        //printf("%s",tokenize);
        if (strcmp(tokenize, ">") == 0) {
            input = true;
            argv1[--argc1] = NULL; // Remove "<" from argv1
            tokenize = strtok(NULL, " ");
            
            if (tokenize != NULL) {
                strcpy(input_file, tokenize);
                char y[1024];
                //printf("%d",argc1);
                strcpy(y," ");
                for(int p=0;p<argc1;p++){
                   strcat(y,argv1[p]);
                   strcat(y," ");
                }
                //printf("%s",y);
                //printf("%s",y);
                //strcat(y,"\0");
                //stdout = fopen(input_file, "w");
                //FILE* sr=strdup(input_file);
                //freopen(input_file, "w", stdout);
                //fclose(input_file);
                 int fd = open(input_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
               if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect the file descriptor (e.g., stdout) to the file
             if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting file descriptor");
        close(fd);
        return 1;
    }

    // Close the original file descriptor (e.g., stdout)
    close(fd);

    // Now, anything printed to stdout will be written to "output.txt"
    //printf("Hello, world!\n");
               // printf("%s",y);
                execute(y);
                //fclose(sr);
            
                //tokenize = strtok(NULL, " ");
            }

        } else if (strcmp(tokenize, "<") == 0) {
            output = true;
            argv1[--argc1] = NULL; // Remove ">" from argv1
            tokenize = strtok(NULL, " ");
            //printf("%s",tokenize);
            if(tokenize != NULL) {
                char y[1024];
                strcpy(y," ");
                for(int p=0;p<argc1;p++){
                   strcat(y,argv1[p]);
                   strcat(y," ");
                }
                
                strcat(y, tokenize);
                //printf("%s",y);
                tokenize = strtok(NULL, " ");
                if(tokenize==NULL){
                execute(y);}

                else if(strcmp(tokenize,">")==0){
                    tokenize = strtok(NULL, " ");
                   if (tokenize != NULL) {
                strcpy(input_file, tokenize);
                
                 int fd = open(input_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
               if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect the file descriptor (e.g., stdout) to the file
             if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting file descriptor");
        close(fd);
        return 1;
    }

    // Close the original file descriptor (e.g., stdout)
    close(fd);

    // Now, anything printed to stdout will be written to "output.txt"
    //printf("Hello, world!\n");
               // printf("%s",y);
                execute(y);
                //fclose(sr);
            
                //tokenize = strtok(NULL, " ");
            }
                }
                else if (strcmp(tokenize, ">>") == 0) {
                  tokenize = strtok(NULL, " ");
                     dlo=1;
            if (tokenize != NULL) {
               
                strcpy(output_file, tokenize);

                 int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect the file descriptor (e.g., stdout) to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting file descriptor");
        close(fd);
        return 1;
    }

    // Close the original file descriptor (e.g., stdout)
    close(fd);
                execute(y);
                //tokenize = strtok(NULL, " ");

            }
                }
                //tokenize = strtok(NULL, " ");
                 //printf("%s",tokenize);
            }
           
        } else if (strcmp(tokenize, ">>") == 0) {
            append = true;
            output = true;
            argv1[--argc1] = NULL; // Remove ">>" from argv1
            tokenize = strtok(NULL, " ");
            dlo=1;
            if (tokenize != NULL) {
                char y[1024];
                //printf("%d",argc1);
                strcpy(y," ");
                for(int p=0;p<argc1;p++){
                   strcat(y,argv1[p]);
                   strcat(y," ");
                }
                strcpy(output_file, tokenize);

                 int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect the file descriptor (e.g., stdout) to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting file descriptor");
        close(fd);
        return 1;
    }

    // Close the original file descriptor (e.g., stdout)
    close(fd);
                execute(y);
                //tokenize = strtok(NULL, " ");

            }
        } 

         tokenize = strtok(NULL, " ");
        // printf("%s",tokenize);
    } 

    argv1[argc1] = NULL;
  
    
   
  
    dup2(stdin_fileno, STDIN_FILENO);
    dup2(stdout_fileno, STDOUT_FILENO);
    if(dlo==1){
        FILE *file;

    // Open the file for reading
    file = fopen(output_file, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and print the contents of the file line by line
    char line[100];  // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);

    return 1;
}
for(int u=o+1;u<arg_count;u++){
    execute(args[u]);
}
    
    return 1;
}

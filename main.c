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
#include "execute.h"

#include "pipe.h"


int flagy=0;
int fgRunning=0;
char cwd[PATH_MAX];
char username[LOGIN_NAME_MAX];
char hostname[HOST_NAME_MAX];
char* prevdir[1024];
int flag1;
int flag5=0;
int flag=0;
void removeSubstring(char *str,  char *substr) {
    char *match;
    size_t len = strlen(substr);

    while ((match = strstr(str, substr)) != NULL) {
        memmove(match, match + len, strlen(match + len) + 1);
    }
    //printf("%s\n",str);
}
void execute_command(char *command, int is_background) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        char *args[MAX_TOKENS];
        int arg_count = 0;

        // Tokenize the command[lk]
        char *token = strtok(command, " \t");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " \t");
        }
        args[arg_count] = NULL;

        execvp(args[0], args);

        perror("execvp"); // Execvp only returns if there's an error
        exit(EXIT_FAILURE);
    } else { // Parent process
        if (is_background) {
            printf("%d\n", pid);
        } else {
            int status;
            waitpid(pid, &status, 0); // Wait for the child to finish
        }
    }
}
void ctrlCZhandler() {
  if (!fgRunning) {
    printf("\n");
    prompt(cwd, username, hostname,3,NULL,1);
  } else {
    fgRunning = 0;
  }
}
//void handleCtrlZ(int signal) {
    //flagy=1;
    // You can perform actions here in response to Ctrl+Z.
//}

void start(){
    
    char* cwd2=cwd;
    flag1=3;
    //struct sigaction sa;
    //sa.sa_handler = handleCtrlZ;
    //sigaction(SIGTSTP, &sa, NULL);

    for(int i=0;i<1024;i++){
    prevdir[i]=NULL;}
    
    while (1) {
        
        int ioMode=-1;
        int inputFd = 0;
        int outputFd = 0;
        char k[PATH_MAX];
        getcwd(k,PATH_MAX);
        //printf("%s\n",k);
        char* q;
        char* v=username;
        char* y=hostname;
        int o;
        char* e;
        char input_line[4096];
        //if(flag==0){
            if(flag1==3){
            prompt(cwd,v,y,3,NULL,o);
            }
            else
            {
                prompt(cwd,v,y,4,e,o);
                flag1=3;
            }
        fgets(input_line, 4096, stdin);
        if(feof(stdin)) {
        // Process the input character here
        
        printf("\n");
        exit(0);
    }

        //}
        //else{
            //flag=0;
        //}
        
           //q=strdup(input_line);
           //const char *substring_to_remove = "pastevents";

    //printf("Original string: %s\n", input_string);
       
       //removeSubstring(q, substring_to_remove);
        //printf("%s",q);
        //char* u=strdup(q);
        //char* s=strtok(q,"\t");
          //int ch;
                  //if((ch = getc(stdin)) == EOF) {
        // Process the input character
        //exit(0);
    //} 
        
          int l=strlen(input_line);
          //char* comm=strp(input_line);
          // printf("%d",l);
        char* com=strdup(input_line);
        char* hu=strdup(input_line);
        int flag=0;
    int i=0;
    //printf("%s",command[lk]);
    while(i<l){
        //printf("%d",strlen(command[lk]));
        if(input_line[i]=='|'){
           flag=1;
           //printf("%d",flag);
           break;
        }
      
        i++;
    }
    if(flag==1){
        //printf("1");
        main4(hu);
        dup2(stdin_fileno, STDIN_FILENO);
        dup2(stdout_fileno, STDOUT_FILENO);
        continue;
    }
    i=0;
    flag=0;
    while(i<l){
        //printf("%d",strlen(command[lk]));
        if(input_line[i]=='>'){
           flag=1;
           //printf("%d",flag);
           break;
        }
        else if(input_line[i]=='<'){
            flag=1;
            break;
        }
        else if(input_line[i]=='>'&&input_line[i+1]=='>'&&(i+1)<l){
          flag=1;
          break;
        }
        i++;
    }
    if(flag==1){
        //printf("1");
        main3(hu,l);
        continue;
    }
        i=0;
        //printf("%s",com);
        int count=0;
        int count1=0;
        int count3=0;
        //printf("1");
        char *command[MAX_TOKENS];
            int gh = 0;
            char *token4 = strtok(hu, ";");
            while (token4 != NULL) {
                command[gh] = token4;
                gh++;
                token4 = strtok(NULL, ";");
            }
            command[gh] = NULL;
        //char *command[lk] = strtok(hu, ";");
        //main3(input_line);
        //printf("%s",command[lk]);
        int lk=0;
        //printf("%d",gh);
     
        lk=0;
        //printf("%s",command[lk]);
        while (command[lk] != NULL) {
            flag5=0;
             if(!strstr(command[lk],"pastevents")){
            //printf("1");
        addHistory(cwd,command[lk]);}
            //printf("%s",command[lk]); 
            //char *command[lk] = strtok(input_line, ";&");
            while (command[lk][0] == ' ' || command[lk][0] == '\t') {
                command[lk]++;
                count3++;
            }
            size_t len = strlen(command[lk]);
            char* yu=strdup(command[lk]);

            //redirection(command[lk]);
         
            //printf("%s",command[lk]);

            //if (strncmp(command[lk], "seek", 4) == 0){
          //printf("1");
        
            while (len > 0 && (command[lk][len - 1] == ' ' || command[lk][len - 1] == '\t' || command[lk][len - 1] == '\n')) {
                //printf("%s",command[lk]);
                command[lk][len - 1] = '\0';
                len--;
                count3++;
                //printf("%c",command[lk][2]);
                //l--;
            }               //q=strdup(command[lk]);
           //printf("%s",command[lk]);
            int is_background = 0;
            count1=0;
            count=0;
            while(count<strlen(command[lk])){
                //printf("%c",com[count]);
                if(com[count]==';'){
                    is_background=0;
                    count++;
                    count1++;
                    break;
                    //printf("1");

                }
                else if(com[count]=='&'){
                    is_background=1;
                    char* hj=strtok(command[lk],"&");
                    count++;
                    count1++;
                    break;

                }
                count++;
                count1++;
            }
            if(is_background){
                fgRunning=1;
            }
            else{
                fgRunning=0;
            }
            count1=count1-count3;
            count3=0;
            //printf("%s",command[lk]);
            //printf("%d",count3);
            
            //printf("%d",count1);
            if (!strncmp(command[lk], "exit",4)) {
          exit(0);

        }
        else if(!strncmp(command[lk],"neonate",7)){
                
               rip(command[lk]);
        }
            else if(!strncmp(command[lk],"fg",2)){
                 char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command[lk] + 2, " \t");
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
        else if(!strncmp(command[lk],"bg",2)){
                 char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command[lk] + 2, " \t");
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
            else if (strncmp(command[lk], "warp", 4) == 0) {
                //printf("d0ne");
                warp(command[lk],cwd,cwd2,prevdir,1);

            }
            else if(strncmp(command[lk], "activities", 10) == 0) {
                //printf("d0ne");
                main1();

            }
            else if (strncmp(command[lk], "proclore", 8) == 0){
                char *token = strtok(command[lk] + 8, " \t");
                    tichnas_pinfo(k,token);
            }
            else if (strncmp(command[lk], "seek", 4) == 0){
                //printf("1");
                struct direc* Dir=(struct direc*)malloc(sizeof(struct direc));
                strcpy(Dir->present,".");
                strcpy(Dir->homed,".");
               seek_call(Dir,command[lk]);
            }
            
             else if (strncmp(command[lk], "iMan", 4) == 0) {
            // Parse the arguments for the peek command[lk]
                
            // Parse the arguments for the peek command[lk]

            char *token = strtok(command[lk] + 4, " \t");
            
            char arg[1024];
            strcpy(arg,token);
            flag5=1;               
                   
    print_man_page(arg);

}           
                                           
            else if (strncmp(command[lk], "peek", 4) == 0) {
            //char *ol=strdup(command[lk]);
            // Parse the arguments for the peek command[lk]
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command[lk] + 4, " \t");
    
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
        else if (strncmp(command[lk], "ping", 4) == 0) {
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command[lk] + 4, " \t");
    
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
        else if (strncmp(command[lk], "pastevents", 10) == 0) {
            char *args[MAX_TOKENS];
            int arg_count = 0;
            char *token = strtok(command[lk] + 10, " \t");
            //printf("%s",token);
            if(token!=NULL && !strcmp(token,"purge")){
                purge(cwd);
            }
            else if (token != NULL && strcmp(token, "execute") == 0) {
                // Extract the command[lk] index
                token = strtok(NULL, " \t");
                if (token != NULL) {
                   int hg=atoi(token);

                   hg=hg-1;
                   if(hg<20){

                   char* jkl=strdup(ex(cwd,hg));
                   //printf("%s",jkl);
                        execute(jkl);}
                    else{
                        printf("Error: command not found in history\n");
                    }

                        } else {
                            printf("Error: command not found in history\n");
                        }
                    }
                    else if(token==NULL){
            if(getHistory2(k,args)<0){
               printf("error");
            }}
            
            
            }
               //printf("%s",command[lk]);
          
         else if (strlen(command[lk]) > 0 && flag5 ==0) {
                 //printf("1");
                char* p=strdup(command[lk]);
                 e= strtok(p, " \t");
                 //printf("%d",is_background);
                o=runCommand(is_background,command[lk]);

                if(o>2&&!is_background){
                    flag1=4;
                    
                }
                
                //continue;
            } 
           
          lk++;
           //printf("%s",command[lk]);
           //count1=0;

        }}}
// Keep accepting command[lk]s
    int main() {
    
    
   
    getlogin_r(username, LOGIN_NAME_MAX);
    gethostname(hostname, HOST_NAME_MAX);
    getcwd(cwd,PATH_MAX);
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, ctrlCZhandler);
    signal(SIGTSTP, ctrlCZhandler);
    start();
    return 0;
}

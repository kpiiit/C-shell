#include "history.h"

#include "headers.h"

char* getHistory(char* root,char** commands,int k) {
  long unsigned size = 1024;
  char path[1024];
  int noOfCommands = 0;

  commands[0] = NULL;
  strcpy(path, root);
  strcat(path, "/.history");
   //printf("%d",k);
  FILE* file = fopen(path, "r");
  char* argv=NULL;
  if (file) {
    for (int i = 0; i < 20; i++) {
      commands[i + 1] = NULL;
      if (getline(&commands[i], &size, file) > 0&&(i)!=k) {
        //printf("%s",commands[i]);
        noOfCommands++;
      } 
      else if(getline(&commands[i], &size, file) > 0&&(i)==k){
        argv=strdup(commands[i]);
        //printf("%s",argv);
        break;
      }
      else {
        break;
      }
    }
    fclose(file);
  }
  
    return argv;
  
}
int getHistory1(char* root, char** commands) {
  long unsigned size = 1024;
  char path[1024];
  int noOfCommands = 0;

  commands[0] = NULL;
  strcpy(path, root);
  strcat(path, "/.history");

  FILE* file = fopen(path, "r");

  if (file) {
    for (int i = 0; i < 20; i++) {
      commands[i + 1] = NULL;
      if (getline(&commands[i], &size, file) > 0) {
        noOfCommands++;
      } else {
        break;
      }
    }
    fclose(file);
  }

  return noOfCommands;
}
void purge(char* root){
     char path[1024];
     strcpy(path, root);
     strcat(path, "/.history");
    // Open the file in write mode, which truncates its content
    FILE *file = fopen(path, "w");
    
    // Check if the file was successfully opened
    if (file == NULL) {
        perror("Error opening the file");
        return ;
    }

    // Close the file to delete its contents
    fclose(file);}
int getHistory2(char* root, char** commands) {
  long unsigned size = 1024;
  char path[1024];
  int noOfCommands = 0;
  //printf("1");
  commands[0] = NULL;
  strcpy(path, root);
  strcat(path, "/.history");

  FILE* file = fopen(path, "r");

  if (file) {
    for (int i = 0; i < 20; i++) {
      commands[i + 1] = NULL;
      if (getline(&commands[i], &size, file) > 0) {
        noOfCommands++;
        printf("%s",commands[i]);
      } else {
        break;
      }
    }
    fclose(file);
  }

  return noOfCommands;
}
char* ex(char* root,int index){
  char* commands[21];
  long unsigned size = 1024;
  char path[1024];
  
  int noOfCommands = getHistory1(root, commands);
  
  strcpy(path, root);
  strcat(path, "/.history");

  FILE* file = fopen(path, "r");

  // Check if the command is already in history
  for (int i = 0; i < noOfCommands; i++) {
    
    if (index==i) {
      char* s=strdup(commands[i]);
      fclose(file);
       // Close the file and return if it's already in history
        size_t len = strlen(s);

  while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')) {
    s[len - 1] = '\0';
    len--;
  }   
  
      return s;
    }
  }

}
void addHistory(char* root, char* str) {
  int valid = 0;

  for (int i = 0; str[i] != '\0' && !valid; i++) {
    if (str[i] != ' ' && str[i] != '\t') valid = 1;
  }
  
  if (!valid) return;

  while (str[0] == ' ' || str[0] == '\t') {
    str++;
  }

  size_t len = strlen(str);

  while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n')) {
    str[len - 1] = '\0';
    len--;
  }   
  
  char* commands[21];
  long unsigned size = 1024;
  char path[1024];
  
  int noOfCommands = getHistory1(root, commands);
  
  strcpy(path, root);
  strcat(path, "/.history");

  FILE* file = fopen(path, "a");
  strcat(str,"\n");
  // Check if the command is already in history
  for (int i = 0; i < noOfCommands; i++) {
    //printf("q");
   // printf("%s",commands[i]);
   // printf("%",str);
    if (strcmp(commands[i],str) == 0) {
      fclose(file); // Close the file and return if it's already in history
      return;
    }
  }

  if (file) {
   

    fprintf(file, "%s", str);
    
    fclose(file);
  }
}

void removePastEvents(char *root) {
    char path[1024];
    strcpy(path, root);
    strcat(path, "/.history");

    // Read the contents of the history file
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening history file");
        return;
    }

    char *lines[1024];
    size_t line_count = 0;
    size_t max_lines = sizeof(lines) / sizeof(lines[0]);
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';
        
        // Check if the line contains "pastevents"
        if (strstr(line, "pastevents") == NULL) {
            lines[line_count] = strdup(line);
            line_count++;
        }
    }
    
    fclose(file);

    // Rewrite the history file without the removed lines
    file = fopen(path, "w");
    if (!file) {
        perror("Error opening history file for writing");
        return;
    }
    
    for (size_t i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    
    fclose(file);
}


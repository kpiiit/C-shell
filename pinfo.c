#include "pinfo.h"

#include "headers.h"

int tichnas_pinfo(char* root, char* pidStr) {
  char dataFolder[1024] = "/proc/";
  char fileName[1024];
  int pid = -1;
  char status = '-';
  int memory = -1;
  char* path = malloc(1024);
  int pgrp = -1;
  int tpgid = -1;

  if (pidStr) {
    strcat(dataFolder, pidStr);
  } else {
    strcat(dataFolder, "self");
  }

  strcpy(fileName, dataFolder);
  strcat(fileName, "/stat");

  FILE* file = fopen(fileName, "r");

  if (file) {
    fscanf(file,
           "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
           "%*s %*s %*s %*s %*s %d",
           &pid, &status, &pgrp, &tpgid, &memory);

    printf("pid : %d\nprocess Status : %c%c\nProcess Group : %d\nVirtual memory : %d\n", pid, status,
           pgrp == tpgid ? '+' : ' ',pgrp,memory);
  } else {
    perror("Error");
    return -1;
  }

  fclose(file);

  strcpy(fileName, dataFolder);
  strcat(fileName, "/exe");

  int pathLen = readlink(fileName, path, 1023);

  if (pathLen >= 0) {
    int isRelative = 0;
    path[pathLen] = '\0';

    for (int i = 0;; i++) {
      if (root[i] == '\0') {
        isRelative = 1;
        break;
      }
      if (i == pathLen || path[i] != root[i]) break;
    }

    if (isRelative) {
      path += strlen(root) - 1;
      path[0] = '~';
    }

    printf("executable path : %s\n", path);
  } else {
    perror("Error");
    return -1;
  }

  return 0;
}
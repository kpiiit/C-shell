#include "headers.h"
#include "peek.h"
char *getModificationTime(time_t mtime) {
    static char buffer[20];
    strftime(buffer, sizeof(buffer), "%b %d %H:%M", localtime(&mtime));
    return buffer;
}
long long int number[] = {0,      9,       99,       999,       9999,       99999,
               999999, 9999999, 99999999, 999999999, 9999999999, -1};

void printDetails(struct stat* itemStatus, int sizeWidth, int linkWidth) {
  int permissionBit = (1 << 8);
  char permissionSymbols[] = "rwx";
  char months[][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  struct tm* time;
  struct passwd* owner;
  struct group* grp;
 
    if (S_ISDIR(itemStatus->st_mode)) {
        printf("\033[34m"); // Blue for directories
    } else if (itemStatus->st_mode & S_IXUSR || itemStatus->st_mode & S_IXGRP || itemStatus->st_mode & S_IXOTH) {
        printf("\033[32m"); // Green for executables
    }
 printf("%c", S_ISDIR(itemStatus->st_mode) ? 'd' : '-');

  for (int i = 0; permissionBit; i++) {
    printf("%c", (permissionBit & itemStatus->st_mode)
                     ? permissionSymbols[i % 3]
                     : '-');

    permissionBit >>= 1;
  }

  printf(" %*ld ", linkWidth, itemStatus->st_nlink);

  owner = getpwuid(itemStatus->st_uid);
  grp = getgrgid(itemStatus->st_gid);
  printf("%s\t%s\t", owner->pw_name, grp->gr_name);

  printf(" %*ld ", sizeWidth, itemStatus->st_size);

  time = localtime(&(itemStatus->st_mtime));

  printf("%s %02d %02d:%02d ", months[time->tm_mon], time->tm_mday,
         time->tm_hour, time->tm_min);
  printf("\033[0m");
}


int printLs(char* root, char* rawLocation, int showAll, int showDetails) {
  char location[1024] = "";
  char fullPath[1024];

  if (rawLocation[0] == '~') {
    strcat(location, root);
    rawLocation++;
  }

  strcat(location, rawLocation);

  struct stat locationStatus;

  if (stat(location, &locationStatus) < 0) {
    perror("Error");
    return -1;
  }

  if (S_ISDIR(locationStatus.st_mode)) {
    struct dirent** namelist;
    int n;
    int total = 0;

    if ((n = scandir(location, &namelist, NULL, alphasort)) < 0) {
      perror("Error");
      return -1;
    }

    struct stat statusArr[n];

    int sizeWidth = 0;
    int linkWidth = 0;

    for (int i = 0; i < n; i++) {
      if (showDetails && ((namelist[i]->d_name)[0] != '.' || showAll)) {
        strcpy(fullPath, location);
        strcat(fullPath, "/");
        strcat(fullPath, namelist[i]->d_name);

        if (stat(fullPath, &statusArr[i]) < 0) {
          perror("Error");
          return -1;
        }

        total += statusArr[i].st_blocks;

        for (int j = 0; number[j] != -1; j++) {
          if ((statusArr[i].st_nlink) > number[j] && j + 1 > linkWidth)
            linkWidth = j + 1;
          if ((statusArr[i].st_size) > number[j] && j + 1 > sizeWidth)
            sizeWidth = j + 1;
        }
      }
    }

    if (showDetails) printf("total %d\n", total / 2);

    for (int i = 0; i < n; i++) {
      if (!((namelist[i]->d_name)[0] != '.' || showAll)) continue;

      if (showDetails) printDetails(&statusArr[i], sizeWidth, linkWidth);

      printf("%s\n", namelist[i]->d_name);

      free(namelist[i]);
    }
  } else {
    struct stat status;

    if (showDetails && stat(location, &status) < 0) {
      perror("Error");
      return -1;
    }

    int sizeWidth = 0;
    int linkWidth = 0;

    for (int i = 0; number[i] != -1; i++) {
      if ((status.st_nlink) > number[i] && i + 1 > linkWidth) linkWidth = i + 1;
      if ((status.st_size) > number[i] && i + 1 > sizeWidth) sizeWidth = i + 1;
    }

    if (showDetails) printDetails(&status, sizeWidth, linkWidth);

    printf("%s\n", location);
  }

  return 0;
}

int tichnas_ls(char* root, char** args) {
    int showAll = 0;
    int showDetails = 0;
    int noOfArguments = 0;
    int firstArg;
    int retValue = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] == '-') {
            if (args[i][1] == 'a' || args[i][2] == 'a') showAll = 1;
            if (args[i][1] == 'l' || args[i][2] == 'l') showDetails = 1;
        }//else if(args[i]=='..'||args[i]='-'||args[i][0]=='~'&&args[i][1]=='/'||) 
        else {
            firstArg = i;
            noOfArguments++;
        }
    }

    if (noOfArguments <= 1) {
        if (printLs(root, noOfArguments ? args[firstArg] : ".", showAll,
                    showDetails) < 0)
            retValue = -1;
    } else {
        firstArg = 0;

        for (int i = 0; args[i] != NULL; i++) {
            if (args[i][0] == '-') continue;

            if (firstArg) printf("\n");
            firstArg = 1;

            printf("%s:\n", args[i]);

            // Get the number of entries and store their names
            int n;
            struct dirent** namelist;
            n = scandir(args[i], &namelist, NULL, alphasort);
            if (n < 0) {
                perror("Error scanning directory");
                return -1;
            }

            // Get the status for each entry and display details
            struct stat statusArr[n];
            int sizeWidth = 0;
            int linkWidth = 0;

            for (int j = 0; j < n; j++) {
                char fullPath[1024];
                strcpy(fullPath, args[i]);
                strcat(fullPath, "/");
                strcat(fullPath, namelist[j]->d_name);

                if (stat(fullPath, &statusArr[j]) < 0) {
                    perror("Error");
                    return -1;
                }

                for (int k = 0; number[k] != -1; k++) {
                    if ((statusArr[j].st_nlink) > number[k] && k + 1 > linkWidth)
                        linkWidth = k + 1;
                    if ((statusArr[j].st_size) > number[k] && k + 1 > sizeWidth)
                        sizeWidth = k + 1;
                }
            }

            if (showDetails) printf("total %d\n", n); // Print total number of entries

            for (int j = 0; j < n; j++) {
                if (!showAll && namelist[j]->d_name[0] == '.') continue;

                if (showDetails) printDetails(&statusArr[j], sizeWidth, linkWidth);

                // Apply color based on file type
                if (S_ISDIR(statusArr[j].st_mode)) {
                    printf("\033[34m%s\033[0m\n", namelist[j]->d_name); // Blue for directories
                } else if (statusArr[j].st_mode & S_IXUSR || statusArr[j].st_mode & S_IXGRP || statusArr[j].st_mode & S_IXOTH) {
                    printf("\033[32m%s\033[0m\n", namelist[j]->d_name); // Green for executables
                } else {
                    printf("%s\n", namelist[j]->d_name); // White for regular files
                }

                free(namelist[j]);
            }

            free(namelist);
        }
    }

    return retValue;
}


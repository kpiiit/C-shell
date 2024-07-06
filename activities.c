#include "headers.h"
#include "activities.h"
//struct ProcessInfo processArray[];
//int numProcesses;
// Function to print the values of struct ProcessInfo
void printProcessInfo() {
    for (int i = 0; i < numProcesses; i++) {
        printf("PID: %d, Name: %s\n", processArray[i].pid, processArray[i].name);
    }
}

// Function to check if a process is still running
int isProcessRunning(pid_t pid) {
    int status;
    return waitpid(pid, &status, WNOHANG) == 0;
}

// ... (rest of your code)
char* getStatusByPID(int pid) {
    char filename[50];
    sprintf(filename, "/proc/%d/status", pid);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        //printf("1");
        return "Not Found"; // Process not found
    }

    char line[100];
    char* status = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "State:", 6) == 0) {
            // Extract the status from the "State" line
            status = strdup(line + 7); // Skip "State: "
            break;
        }
    }

    fclose(file);
    //printf("1");
    return status != NULL ? status : "Unknown";
}

void main1() {
    // ... (previous code)

    // Iterate through the processArray
    for (int i = 0; i < numProcesses; i++) {
        printf("%d : %s ", processArray[i].pid, processArray[i].kl);

        // Get the status of the process
        char* status = getStatusByPID(processArray[i].pid);
        
        if (strcmp(status, "Not Found") == 0) {
            printf("- Completed\n");
        } else if (strcmp(status, "Unknown") == 0) {
            printf("- Status unknown\n");
        } else if(strcmp(status,"S (sleeping)")==0){
            printf("- Running\n");
        }
        else if(strcmp(status,"T (stopped)")==0){
            printf("- Stopped\n");
        }
        else{
            printf("- %s\n",status);
        }

        //free(status); // Free the memory allocated by getStatusByPID
    }

    // ... (rest of your code)
}
int deleteProcessByPID(int pidToDelete) {
    int found = 0;
    for (int i = 0; i < numProcesses; i++) {
        if (processArray[i].pid == pidToDelete) {
            found = 1;

            // Shift elements to remove the process
            for (int j = i; j < (numProcesses - 1); j++) {
                processArray[j] = processArray[j + 1];
            }

            // Decrease the count of processes
            (numProcesses)--;
            break;
        }
    }
    return found;
}
int findProcessByPID(int pidToDelete) {
    int found = 0;
    for (int i = 0; i < numProcesses; i++) {
        if (processArray[i].pid == pidToDelete) {
            found = 1;

            // Decrease the count of processes
            //(numProcesses)--;
            break;
        }
    }
    return found;
}
char* getProcessByPID(int pidToDelete) {
    int found = 0;
    char* y;
    for (int i = 0; i < numProcesses; i++) {
        if (processArray[i].pid == pidToDelete) {
            found = 1;
            y=strdup(processArray[i].kl);
            // Shift elements to remove the process
            for (int j = i; j < (numProcesses - 1); j++) {
                processArray[j] = processArray[j + 1];
            }

            // Decrease the count of processes
            (numProcesses)--;
            break;
        }
    }
    return y;
}
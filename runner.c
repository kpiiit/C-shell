#include "runner.h"
#include "headers.h"
#define MAX_PROCESSES 256

int k = -1; // Initialize k to an invalid PID
char* o;

// Number of processes currently tracked
struct ProcessInfo processArray[256];
int numProcesses =0;
void sigchld_handler(int signo) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("%s exited normally (%d).\n", o, pid);
            if (pid == k) {
                k = -1; // Reset the stored PID
            }
        } else if (WIFSIGNALED(status)) {
            printf("%s exited abnormally  (%d).\n", o, pid);
            if (pid == k) {
                k = -1; // Reset the stored PID
            }
        }
    }
}

int runCommand(int background, char* command) {
    int pid = fork();
    char *args[MAX_TOKENS];
    int arg_count = 0;
    char* hj=strdup(command);
    // Tokenize the command
    char *token = strtok(command, " \t");
    while (token != NULL) {
        args[arg_count] = token;

        arg_count++;
        token = strtok(NULL, " \t");
    }
    args[arg_count] = NULL;
    o = args[0];

    if (pid < 0) {
        perror("Error");
        return -1;
    } else if (pid) {
        // Parent process
        if (background) {
            fprintf(stderr, " %d\n", pid);
            k = pid;

            // Store PID and process name in the struct
            if (numProcesses < MAX_PROCESSES) {
                processArray[numProcesses].pid = pid;
                strncpy(processArray[numProcesses].name, args[0], sizeof(processArray[numProcesses].name));
                processArray[numProcesses].kl=strdup(hj);
                processArray[numProcesses].q = 1;
                numProcesses++;
            } else {
                fprintf(stderr, "Maximum number of processes reached. Cannot track more processes.\n");
            }
        } else {
            int status;
            if (numProcesses < MAX_PROCESSES) {
                processArray[numProcesses].pid = pid;
                strncpy(processArray[numProcesses].name, args[0], sizeof(processArray[numProcesses].name));
                processArray[numProcesses].q = 0;
                processArray[numProcesses].kl=strdup(hj);
                numProcesses++;
            } else {
                fprintf(stderr, "Maximum number of processes reached. Cannot track more processes.\n");
            }
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(0, pid);
            time_t start_time = time(NULL);
            waitpid(pid, &status, WUNTRACED);

            tcsetpgrp(0, getpgid(0));

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if (WIFSTOPPED(status)) return pid;

            if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) return -1;
            time_t end_time = time(NULL);
            int time_taken = (int)(end_time - start_time);
            if (time_taken > 2) {
                return time_taken;
            }
        }
    } else {
        // Child process
        setpgid(0, 0);

        if (execvp(args[0], args) < 0) {
            perror("Error");
            exit(1);
        }
    }

    return 0;
}



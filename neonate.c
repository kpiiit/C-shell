#include "headers.h"
//volatile sig_atomic_t stop;
int parse_pid_from_line(const char *line)
{
    char *token = strtok((char *)line, " \t\n"); // Split the line using spaces and tabs as delimiters

    // Loop through tokens until we find a non-empty one
    while (token != NULL)
    {
        // Attempt to convert the token to an integer (PID)
        int pid = atoi(token);

        // Check if the conversion was successful and the PID is non-negative
        if (pid > 0)
        {
            return pid;
        }

        // Get the next token
        token = strtok(NULL, " \t\n");
    }

    // If no valid PID was found, return -1
    return -1;
}

volatile sig_atomic_t stop = 0;

void sigint_handler(int signum)
{
    stop = 1;
}

char read_key()
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1)
    {
        perror("read");
        exit(1);
    }
    return c;
}

int get_most_recent_pid()
{
    pid_t child_pid;
    int pipe_fd[2];
    int most_recent_pid = -1;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if ((child_pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0)
    {
        // Child process: Redirect stdout to the write end of the pipe
        close(pipe_fd[0]); // Close the read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); // Close the original write end of the pipe

        // Execute the 'ps' command to list all processes sorted by start time
        execlp("ps", "ps", "axo", "pid", "--sort=start_time", (char *)NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        // Parent process: Close the write end of the pipe
        close(pipe_fd[1]);

        FILE *pipe_fp = fdopen(pipe_fd[0], "r");
        if (pipe_fp == NULL)
        {
            perror("fdopen");
            exit(1);
        }

        char line[256];
        while (!stop && fgets(line, sizeof(line), pipe_fp) != NULL)
        {
            // Parse the line to extract the PID (you'll need to implement this)
            int pid = parse_pid_from_line(line);
            if (pid > most_recent_pid)
            {
                most_recent_pid = pid;
            }
        }

        fclose(pipe_fp);
        wait(NULL); // Wait for the child process to exit
    }

    return most_recent_pid;
}
int rip(char* command)
{
    stop=0;
    char *flags[MAX_TOKENS];
            int n = 0;
            char *token = strtok(command, " \t");
            while (token != NULL) {
                flags[n] = token;
                n++;
                token = strtok(NULL, " \t");
            }
    if (n != 3)
    {
        fprintf(stderr, "Usage: %s -n [time_arg]\n", flags[0]);
        return 1;
    }

    int time_arg = atoi(flags[2]);
    if (time_arg <= 0)
    {
        fprintf(stderr, "Invalid time argument: %s\n", flags[2]);
        return 1;
    }

    signal(SIGINT, sigint_handler);

    // Enable raw mode to read characters without buffering
    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    while (!stop)
    {
        int most_recent_pid = get_most_recent_pid();
        if (most_recent_pid != -1)
        {
            printf("%d\n", most_recent_pid);
        }
        sleep(time_arg);

        // Check for 'x' keypress to exit
        if (read_key() == 'x')
        {
            stop = 1;
        }
    }

    // Restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    //free(flags);
    return 0;
}
#include <stdio.h>
#include "main.h"

void execute(char *command)
{
    setenv("PATH", "/usr/local/bin:/usr/bin:/bin", 1);

    pid_t pid;
    char *args[1024];
    int i = 0;

    // Parse the command line and separate the command and its arguments
    char *token = strtok(command, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Mark the end of the argument list with NULL

    // Check if the command exists and is executable
    if (access(args[0], X_OK) != 0) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return;
    }

    // Fork and execute the command
    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error
        perror("fork");
    } else {
        // Parent process
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

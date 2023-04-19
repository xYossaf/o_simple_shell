#include "main.h"

/**
 * execute - executes the given command with its arguments
 * @args: array of strings containing the command and its arguments
 * Return: void
 */
void execute(char **args)
{
    pid_t pid;
    int status;
    char *path, *p, *path_copy;
    int command_exists = 0;

    /* Check if the command exists in one of the directories in PATH */
    path = getenv("PATH");
    path_copy = strdup(path); /* make a copy of path */
    p = strtok(path_copy, ":"); /* use path_copy instead of path */

    while (p != NULL) /* check if p is not NULL */
    {
        char *cmd = malloc(strlen(p) + strlen(args[0]) + 2);
        sprintf(cmd, "%s/%s", p, args[0]);
        if (access(cmd, X_OK) == 0)
        {
            /* Command exists, set command_exists flag to 1 */
            command_exists = 1;
            break;
        }
        free(cmd);
        p = strtok(NULL, ":"); /* use NULL instead of path_copy */
    }

    free(path_copy); /* free the memory allocated by strdup */

    if (command_exists)
    {
        /* Command exists, fork and execute */
        pid = fork();

        if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror("simple_shell");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("simple_shell");
        }
        else
        {
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    else
    {
        /* Command not found */
        fprintf(stderr, "%s: command not found\n", args[0]);
    }
}

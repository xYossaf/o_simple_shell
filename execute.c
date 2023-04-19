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

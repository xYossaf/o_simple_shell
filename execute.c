#include "main.h"
/**
 * execute - executes the given command
 * @command: the command to execute
 * Retrun: Void
 */
void execute(char *command)
{
pid_t pid;
int status;

pid = fork();

if (pid == 0)
{
if (execlp(command, command, (char *)0) == -1)
{
perror("./shell");
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

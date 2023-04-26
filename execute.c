#include "main.h"

/**
 * execute - executes the given command with its arguments
 * @args: array of strings containing the command and its arguments
 * Return: void
 */

void execute(char **args)
{
	char *path;
	char **paths;
	char *cmd;
/* Check if the command is "exit" */
if (strcmp(args[0], "exit") == 0)
{
exit(0);
}

/* Check if the command is "env" */
if (strcmp(args[0], "env") == 0)
{
print_env();
return;
}

/* Check if the command exists in one of the directories in PATH */
path = getenv("PATH");
paths = split_path(path);
cmd = find_command(args[0], paths);
free_split(paths);

if (cmd != NULL)
{
/* Command exists, fork and execute */
fork_and_execute(args, cmd);
free(cmd);
}
else
{
/* Command not found */
fprintf(stderr, "%s: command not found\n", args[0]);
}
}

/**
 * print_env - prints env
 *
 * Return: void
 */

void print_env(void)
{
char **env = __environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
}
/**
 * split_path - splits path
 * @path: path given
 * Return: char - path spilt
 */
char **split_path(char *path)
{
char **paths = malloc(sizeof(char *));
char *p = strtok(path, ":");

int i = 0;
while (p != NULL)
{
paths[i] = p;
i++;

paths = realloc(paths, (i + 1) * sizeof(char *));
p = strtok(NULL, ":");
}

paths[i] = NULL;
return (paths);
}
/**
 * find_command - splits path
 * @cmd: cmd given
 * @paths: paths given
 * Return: char -  full path
 */
char *find_command(char *cmd, char **paths)
{
char *path = NULL;
int i;

for (i = 0; paths[i] != NULL; i++)
{
char *full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
sprintf(full_path, "%s/%s", paths[i], cmd);

if (access(full_path, X_OK) == 0)
{
/* Command exists */
path = full_path;
break;
}

free(full_path);
}

return (path);
}

/**
 * fork_and_execute - splits path
 * @args: args given
 * @cmd: cmd given
 * Return: void
 */
void fork_and_execute(char **args, char *cmd)
{
pid_t pid = fork();
int status;

if (pid == 0)
{
/* Child process */
if (execvp(cmd, args) == -1)
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
/* Parent process */
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

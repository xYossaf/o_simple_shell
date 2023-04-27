#include "main.h"

/**
 * main - main;
 * Return: int
 */
int main(void)
{
char *input;
char *args[64];
int i;

while (1)
{
write(STDOUT_FILENO, "#cisfun$ ", 9);
input = malloc(1024);
if (!input)
{
exit(EXIT_FAILURE);
}
input = custom_getline();
if (!input)
{
write(STDOUT_FILENO, "\n", 1);
free(input);
exit(EXIT_SUCCESS);
}
input[strcspn(input, "\n")] = '\0';

i = 0;
args[i] = strtok(input, " ");
while (args[i] != NULL)
{

i++;
args[i] = strtok(NULL, " ");
}

if (args[0] != NULL)
{

execute(args);
}
write(STDOUT_FILENO, "37", 1);
free(input);
}
return (0);
}

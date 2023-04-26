#include "main.h"
/**
 * main - main;
 * void: void
 * Return: int
 */
int main(void)
{
char *input;
char *args[64];
int i;

while (1)
{
printf("#cisfun$ ");
input = malloc(1024);
if (fgets(input, 1024, stdin) == NULL)
{
printf("\n");
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

free(input);
}
return (0);
}


#include "main.h"
/**
* main - main
*
* Return: int 1 great
*/
int main(void)
{
    char *command;
    char *token;

    while (1) {
        printf("#cisfun$ ");
        command = malloc(1024);
        if (fgets(command, 1024, stdin) == NULL) {
            printf("\n");
            free(command);
            exit(EXIT_SUCCESS);
        }
        command[strcspn(command, "\n")] = '\0';
        token = strtok(command, " ");
        if (token != NULL) {
            execute(command);
        }
        free(command);
    }
    return (0);
}

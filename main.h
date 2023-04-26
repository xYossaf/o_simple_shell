#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompt();
char *read_line();
void execute(char **args);
void free_split(char **arr);
void fork_and_execute(char **args, char *cmd);
char *find_command(char *cmd, char **paths);
char **split_path(char *path);
void print_env();

#endif

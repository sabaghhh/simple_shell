#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

extern char **environ;

void parse_cmd(char *cmd, char **args);
int execute_cmd(char **args, char *program_name);

#endif

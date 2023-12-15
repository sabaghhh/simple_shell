#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;
char display_prompt(void);
void free_argv(char **argv);
int custom_atoi(char *str);
int _str_len(const char *str);
int _str_cmp(char *str1, char *str2);
char *_str_conc(char *dest, char *source);
char *_str_cpy(char *dest, const char *source);
void _Buff(char **buffPtr, char *s_assign, size_t *buffSize, size_t strSize);
void *allocateM(void *existing, unsigned int prevSize, unsigned int newSize);
ssize_t _get_line(char **outputString, size_t *outputSize, FILE *inputFile);
char *_read_line(void);
char **_split_line(char *line);
void _get_path(char *s1, char *s2, char *cmd);
char *_find_path(char *cmd);
int _my_exit(char **argv);
int _my_env(char **argv);
int _my_cd(char **argv);
int _execute_line(char **argv);
int _builtin(void);
int _is_builtin(char **argv);
char *_read(void);
void _non_interactive(void);
void runCommandsFromFile(char *filePath);
int main(int argc, char **argv);

#endif

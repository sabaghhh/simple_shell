#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my_strcpy.h"
#include "my_strcat.h"
#include "my_strchr.h"
#include "my_strcmp.h"
#include "my_strlen.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}
/**
 * _puts - prints a string, followed by a new line, to stdout
 * @str: string to print
 * Return: nothing
 * On error, -1 is returned, and errno is set appropriately.
 */
void _puts(char *str)
{
int i = 0;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
_putchar('\n');

}
/**
 * builtin_env - print the environment
 * @args: arguments passed to the function
 *
 * Return: 1 to continue execution.
 */
int builtin_env(char **args);
/**
 * builtin_exit - exit the shell
 * @args: arguments passed to the function
 *
 * Return: 0 to terminate execution.
 */
int builtin_exit(char **args);

/**
 * builtin_cd - change directory
 * @args: arguments passed to the function
 *
 * Return: 1 to continue execution.
 */
int builtin_cd(char **args);

char **built_in_setenv(char **args, char **env);

char *builtin_str[] = {"env", "cd", "exit"};
int (*builtin_func[]) (char **) = {&builtin_env, &builtin_cd, &builtin_exit};


/**
 * builtin_env - print the environment
 * @args: arguments passed to the function
 *
 * Return:  to continue execution.
 */

int builtin_env(char **args)
{
if (args[1] == NULL)
{
char **env = __environ;
while (*env)
{
_puts(*env++);
}
return (1);
}
else
{
return (-1);
}
}

/**
 * mygetenv - get the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: the value of the environment variable or NULL.
 */
char *mygetenv(const char *name)
{
int i = 0;
char *token;
char *env = __environ[i];
while (env != NULL)
{
token = strtok(env, "=");
if (strcmp(token, name) == 0)
{
token = strtok(NULL, "=");
return (token);
}
i++;
env = __environ[i];
}
return (NULL);
}
/**
* **built_in_setenv - get the value of an environment variable
* @args: the name of the environment variable
* @env: the name of the environment variable
* Return: the value of the environment variable or NULL.
*/
char **built_in_setenv(char **args, char **env)
{
char *name;
char *value;
char *new_env_var;
char **new_env;
int i = 0;
if (args[1] == NULL || args[2] == NULL)
{
return (env);
}
name = args[1];
value = args[2];
while (env[i] != NULL)
{
if (mystrcmp(env[i], name) == 0)
{
new_env_var = malloc(mystrlen(name) + mystrlen(value) + 2);
mystrcpy(new_env_var, name);
mystrcat(new_env_var, "=");
mystrcat(new_env_var, value);
env[i] = new_env_var;
return (env);
}
i++;
}
new_env = malloc(sizeof(char *) * (i + 2));
i = 0;
while (env[i] != NULL)
{
new_env[i] = env[i];
i++;
}
new_env[i] = malloc(mystrlen(name) + mystrlen(value) + 2);
mystrcpy(new_env[i], name);
mystrcat(new_env[i], "=");
mystrcat(new_env[i], value);
new_env[i + 1] = NULL;
return (new_env);
}

/**
 * builtin_exit - exit the shell
 * @args: arguments passed to the function
 *
 * Return: 0 to terminate execution.
 */
int builtin_exit(char **args)
{
if (args[1] == NULL)
{
exit(EXIT_SUCCESS);
}
else
{
exit(atoi(args[1]));
}
}
/**
* builtin_cd - exit the shell
* @args: arguments passed to the function
*
* Return: 0 to terminate execution.
*/
int builtin_cd(char **args)
{
if (args[1] == NULL)
{
return (-1);
}
else
{
if (chdir(args[1]) != 0)
{
perror("cd");
return (-1);
}
}
return (1);
}

/**
 * builtin_num - return the number of builtin commands
 *
 * Return: the number of builtin commands.
 */
int builtin_num(void)
{
return (sizeof(builtin_str) / sizeof(char *));
}


/**
 * prompt - display prompt
 *
 * Return:nothing
 */
void prompt(void)
{
char the_prompt[] = "$ ";
write(STDOUT_FILENO, the_prompt, sizeof(the_prompt) - 1);
fflush(stdout);
}
/**
 * read_line - Read line of input
 *
 * Return: Pointer to the user's input.
 *
* @brief Read a line of input from stdin.
* @return The line from stdin.
 */
#define BUFSIZE 1024
char *read_line(void)
{
int bufsize = BUFSIZE;
int position = 0;
char *buffer = malloc(sizeof(char) * bufsize);
int c;
if (!buffer)
{
exit(EXIT_FAILURE);
}
while (!NULL)
{
c = getchar();
if (c == EOF || c == '\n')
{
buffer[position] = '\0';
return (buffer);
}
else
{
buffer[position] = c;
}
position++;
if (position >= bufsize)
{
bufsize += BUFSIZE;
buffer = malloc(sizeof(char) * bufsize);
if (!buffer)
{
exit(EXIT_FAILURE);
}
}
}
}

/**
 * parse_line - parse user input into tokens
 * @line: the line to be parsed.
 * Return: an array of pointers to tokens or NULL.
 */
char **parse_line(char *line)
{
char *token;
char **tokens;
int i = 0, buffer_size = 64;
tokens = malloc(buffer_size * sizeof(char *));
if (!tokens)
return (NULL);
token = strtok(line, " ");
while (token)
{
tokens[i] = token;
i++;
if (i >= buffer_size)
{
buffer_size += buffer_size;
tokens = malloc(buffer_size *sizeof(char *));
if (!tokens)
{
perror("$: ");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, " ");
}
tokens[i] = NULL;
return (tokens);
}


/**
 * execute - Execute the line.
 * @args: An array of strings of the tokens.
 *
 * Return: The exit status.
 */
int execute(char **args)
{
pid_t pid;
int status;
pid = fork();
if (pid == 0)
{
if (mystrchr(args[0], '/') == NULL)
{
char *path = mygetenv("PATH");
char *dirs = strtok(path, ":");
while (dirs != NULL)
{
char *command_path = malloc(mystrlen(dirs) + strlen(args[0]) + 2);
mystrcpy(command_path, dirs);
mystrcat(command_path, "/");
mystrcat(command_path, args[0]);
execve(command_path, args, __environ);
free(command_path);
dirs = strtok(NULL, ":");
}
}
else
{
execve(args[0], args, __environ);
}
perror(args[0]);
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("./shell");
}
else
{
do { waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}

/**
 * execute_builtin - Execute the builtin command.
 * @args: An array of strings of the tokens.
 *
 * Return: The exit status.
 */
int execute_builtin(char **args)
{
int counter;
if (args[0] == NULL)
{
return (1);
}
for (counter = 0; counter < builtin_num(); counter++)
{
if (mystrcmp(args[0], builtin_str[counter]) == 0)
{
return ((*builtin_func[counter])(args));
}
}
return (execute(args));
}

/**
 * loop - loop to get input and execute it.
 *
 * Return: nothing
 */
void loop(void)
{
char *line;
char **args;
int status;
do {
prompt();
line = read_line();
args = parse_line(line);
status = execute_builtin(args);
free(line);
free(args);
} while (status);
}
/**
 * main - works as a simple shell
 * @argc: An array of strings of the tokens.
 * @argv: An array of strings of the tokens.
 * Return: 0
 */

int main(void)
{
loop();
return (EXIT_SUCCESS);
}


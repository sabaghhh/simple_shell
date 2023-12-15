#include "shell.h"
/**
 * parse_cmd - parse a command line into arguments
 * @cmd: command line
 * @args: array of arguments
*/
void parse_cmd(char *cmd, char **args)
{
	int i = 0;

	args[i] = strtok(cmd, " \n");
	while (args[i] != NULL)
	{
		args[++i] = strtok(NULL, " \n");
	}
}
/**
 * execute_cmd - execute a command
 * @args: array of arguments
 * @program_name: name of the program
 * Return: 0 if the command is exit, 1 otherwise
*/
int execute_cmd(char **args, char *program_name)
{
	char **env;

	if (strcmp(args[0], "exit") == 0)
	{
		return (0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (env = environ; *env != 0; env++)
		{
			char *thisEnv = *env;

			printf("%s\n", thisEnv);
		}
		return (1);
	}
	else
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Error");
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
			return (1);
		}
	}
	return (1);
}

/**
 * main - simple shell main function
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int main(int argc, char **argv)
{
	char cmd[MAX_CMD_LEN];
	char *args[MAX_ARGS];
	int status = 1;

	argc = argc;
	while (status)
	{
		printf("$ ");
		if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		parse_cmd(cmd, args);
		if (args[0] != NULL)
		{
			status = execute_cmd(args, argv[0]);
		}
	}

	return (EXIT_SUCCESS);
}

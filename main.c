#include "shell.h"
/**
 * runCommandsFromFile - executes commands from a file.
 * @filePath: path to the file containing commands.
 * Return: Nothing.
 */
void runCommandsFromFile(char *filePath)
{
	FILE *file;
	char **arguments, *commandLine = NULL;
	size_t bytesRead, bufferSize = 0;

	file = fopen(filePath, "r");
	if (!file)
	{
		perror("Error: Unable to open the specified file");
		exit(EXIT_FAILURE);
	}

	while ((bytesRead = getline(&commandLine, &bufferSize, file)) != -1)
	{
		commandLine[strcspn(commandLine, "\n")] = '\0';
		arguments = _split_line(commandLine);
		_execute_line(arguments);
		free(arguments);
	}
free(commandLine);
fclose(file);
}

/**
 * main - simple shell.
 * @argc: number of arguments passed.
 * @argv: arguments passed.
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	char *line;
	int value = -1;

	if (argc > 1)
	{
		runCommandsFromFile(argv[1]);
		return (0);
	}

	if (isatty(STDIN_FILENO) == 1)
	{
		while (value == -1)
		{
			display_prompt();
			line = _read_line();
			argv = _split_line(line);
			value = _is_builtin(argv);
			free(line);
			free(argv);
			if (value >= 0)
				exit(value);
		}
	}
	else
		_non_interactive();
	return (0);
}

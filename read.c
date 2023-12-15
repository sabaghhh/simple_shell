#include "shell.h"
/**
 * _read - reads line from a stream.
 *
 * Return: the line read.
 */
char *_read(void)
{
char *line;
int chars, i = 0, buff = 1024;

line = malloc(sizeof(char) * buff);
if (!line)
{
perror("Error: Memory allocation failed");
exit(EXIT_FAILURE);
}

while (1)
{
chars = getchar();
if (chars == EOF)
{
free(line);
exit(EXIT_SUCCESS);
}

else if (chars == '\n')
{
*(line + i) = '\0';
return (line);
}

else
*(line + i) = chars;

i++;
if (i >= buff)
{
buff *= 2;
line = realloc(line, buff);
if (!line)
{
perror("Error: Memory reallocation failed");
exit(EXIT_FAILURE);
}
}
}
}

/**
 * _non_interactive - runs the non-interactive mode.
 *
 * Return: Nothing.
 */
void _non_interactive(void)
{
	char **tokens, *line;
	int value = -1;

	while (value == -1)
	{
		line = _read();
		tokens = _split_line(line);
		value = _is_builtin(tokens);
		free(line);
		free(tokens);
		if (value >= 0)
			exit(value);
	}
}


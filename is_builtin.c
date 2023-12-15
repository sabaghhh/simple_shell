#include "shell.h"
/**
 * _is_builtin - checks if the command is bulitin.
 * @argv: array of commands.
 * Return: 1 on success.
 */

int _is_builtin(char **argv)
{
	int i;

	char *builtin[] = {
		"exit",
		"env",
		"cd"
	};

	int (*builtin_functions[])(char **) = {
		&_my_exit,
		&_my_env,
		&_my_cd
	};

	if (!argv[0])
	{
		perror("Error");
		return (-1);
	}
	for (i = 0; i < _builtin(); i++)
	{
		if (_str_cmp(argv[0], builtin[i]) == 0)
			return ((*builtin_functions[i])(argv));
	}
	return (_execute_line(argv));
}

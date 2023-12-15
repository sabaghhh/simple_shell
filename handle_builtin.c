/**
 * _my_exit - exits the shell.
 * @argv: array of arguments.
 * Return: 0 on success.
 */
int _my_exit(char **argv)
{
	int i = 0, value = 0;

	if (argv[1])
	{
		value = _atoi(argv[1]);
		if (value == -1)
		{
			perror("Error: Incorrect exit status\n");
			return (-1);
		}
	}
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	exit(value);
}


/**
 * _my_env - print enviroment variables.
 * @argv: array of arguments.
 * Return: 1 on success or 0 otherwise
 */
int _my_env(char **argv)
{
	int i = 0, var = 0;

	(void)argv;

	while (environ[i])
	{
		var = write(STDOUT_FILENO, environ[i], _str_len(environ[i]));
		if (var == -1)
			return (-1);
		var = write(STDOUT_FILENO, "\n", 1);
		if (var == -1)
			return (-1);
		i++;
	}
	return (-1);
}

/**
 * _my_cd - changes the directory.
 * @argv: array arguments.
 * Return: 1 ion success or 0 otherwise.
 */
int _my_cd(char **argv)
{
	int dir;

	if (argv[1] == NULL)
	{
		perror("Error: Expected argument to \"cd\"\n");
	}

	else
	{
		dir = chdir(argv[1]);
		if (dir != 0)
		{
			perror("Error: changing dir\n");
		}
	}
	return (-1);
}

/**
 ** _execute_line - executes command.
 ** @argv: array of commands.
 ** Return: Nothing.
 **/
int _execute_line(char **argv)
{
	pid_t pid;
	int value;
	char *path;

	pid = fork();
	if (pid < 0)
		perror("Error: Fork failed");
	else if (pid ==  0)
	{
		path = _find_path(argv[0]);

		if (execve(path, argv, NULL) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		while (1)
		{
			waitpid(pid, &value, WUNTRACED);
			if (WIFEXITED(value) || WIFSIGNALED(value))
				break;
		}
	}
	return (-1);
}

/**
 * _builtin - calculate the no of builtins.
 *
 * Return: no of builtin functions.
 */
int _builtin(void)
{
	int n;
	char *builtins[] = {
		"exit",
		"env",
		"cd"
	};

	n = (sizeof(builtins) / (sizeof(char *)));

	return (n);
}


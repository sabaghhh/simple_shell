#include "shell.h"
/**
 * _get_path - gets the path.
 * @s1: dest.
 * @s2: source.
 * @cmd: command
 * Return: Nothing.
 */
void _get_path(char *s1, char *s2, char *cmd)
{
	_str_cpy(s1, s2);
	_str_conc(s1, "/");
	_str_conc(s1, cmd);
}

/**
 ** _find_path - finds the path of the command.
 ** @cmd: the command.
 ** Return: the path.
 **/
char *_find_path(char *cmd)
{
	char *path, *cmdpath, *copy, *dir, *line, *bin = "/bin/";

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	path = getenv("PATH");
	if (!path)
		perror("ERROR: ");
	copy = strdup(path);
	dir = strtok(copy, ":");
	cmdpath = NULL;
	while (dir && !cmdpath)
	{
		line = malloc(_str_len(dir) + _str_len(cmd) + 2);
		if (line == NULL)
			exit(-1);
		_get_path(line, dir, cmd);
		if (access(line, X_OK) == 0)
			cmdpath = strdup(line);
		free(line);
		dir = strtok(NULL, ":");
	}
	if (!cmdpath)
	{
		line = malloc(_str_len("/bin") + _str_len(cmd) + 2);
		if (!line)
		{
			perror("Error: failed to allocate memory.\n");
			exit(-1);
		}
		_str_cpy(line, bin);
		_str_conc(line, cmd);
		if (access(line, X_OK) == 0)
			cmdpath = strdup(line);
		free(line);
	}
	free(copy);
	return (cmdpath);
}


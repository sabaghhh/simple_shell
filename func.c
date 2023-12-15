#include "shell.h"
/**
 * display_prompt - display the shell prompt.
 *
 * Return: the prompt
 */
char display_prompt(void)
{
	char the_p;

	the_p = write(STDOUT_FILENO, "$ ", 2);
	return (the_p);
}

/**
 * free_argv - frees an array of arguments.
 * @argv: the passed array of arguments.
 * Return: Nothing.
 */
void free_argv(char **argv)
{
	int i;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
}



/**
 * custom_atoi - converts the string to int.
 * @str: the string.
 * Return: integer.
 */
int custom_atoi(char *str)
{
	unsigned int result = 0;
	char is_negative = 0;
	int sign = 1;

	if (!str)
		return (0);

	while (*str)
	{
		if (*str == '-')
			sign *= -1;
		if (*str >= '0' && *str <= '9')
		{
			is_negative = 1;
			result = result * 10 + (*str - '0');
		}
		else if (*str < '0' || *str > '9')
		{
			if (is_negative == 1)
				break;
		}

		str++;
	}

	if (sign < 0)
		result = -1 * result;

	return (result);
}

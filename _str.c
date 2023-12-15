/**
 * _str_len - finds the length of string.
 * @str: the string.
 * Return: the lenght.
 */
int _str_len(const char *str)
{
	int i;

	for (i = 0; *str != '\0'; i++)
		str++;

	return (i);
}


/**
 * _str_cpy - copies strings.
 * @dest: pointer to the destination string.
 * @source: pointer to the source string.
 * Return: copied string.
 */
char *_str_cpy(char *dest, const char *source)
{
	char *str = dest;

	while (*source != '\0')
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
	return (str);
}

/**
 * _str_cmp - compares strings.
 * @str1: first string.
 * @str2: second string.
 * Return: 0 on success.
 */
int _str_cmp(char *str1, char *str2)
{
	if (!str1 || !str2)
	{
		if (str1 == str2)
			return (0);
		return ((str1 == NULL) ? -1 : 1);
	}
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return ((*str1 < *str2) ? -1 : 1);
}

/**
 * _str_conc - conctenates strings.
 * @dest: destination string.
 * @source: source string.
 * Return: pointer to dest.
 */
char *_str_conc(char *dest, char *source)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
	return (str);
}

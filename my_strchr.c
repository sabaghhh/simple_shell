#include <stdio.h>
#include "my_strchr.h"

/**
 * mystrchr - locate character in string
 * @s: string to search
 * @c: character to search for
 *
 * Return: pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found
 */
char *mystrchr(char *s, char c)
{
int i = 0;
while (s[i] != '\0')
{
if (s[i] == c)
{
return (&s[i]);
}
i++;
}
return (NULL);
}

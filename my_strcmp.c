#include "my_strcmp.h"

/**
 * mystrcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if the strings match, otherwise the difference between the first
 * unmatched characters
 */

int mystrcmp(char *s1, char *s2)
{
int i = 0;
while (s1[i] != '\0' && s2[i] != '\0')
{
if (s1[i] != s2[i])
{
return (s1[i] - s2[i]);
}
i++;
}
return (s1[i] - s2[i]);
}

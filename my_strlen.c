#include "my_strlen.h"

/**
 * mystrlen - find the length of a string
 * @s: string to find the length of
 *
 * Return: length of the string
 */

int mystrlen(char *s)
{
int i = 0;
while (s[i] != '\0')
{
i++;
}
return (i);
}

#include "my_strcat.h"

/**
 * mystrcat - concatenate two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */
char *mystrcat(char *dest, char *src)
{
int i = 0;
int j = 0;
while (dest[i] != '\0')
{
i++;
}
while (src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}
dest[i] = '\0';
return (dest);
}

#include "my_strcpy.h"

/**
 * mystrcpy - copy a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */
char *mystrcpy(char *dest, char *src)
{
int i = 0;
while (src[i] != '\0')
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

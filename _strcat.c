#include "shell.h"
/**
 * _strcat - function that concatena two strings
 * @dest: leeter
 * @src: letter
 * Return: dest of string
 */
char *_strcat(char *dest, char *src)
{
int words = 0, b;
while (dest[words] != 0)
words++;
for (b = 0; src[b] != 0; b++, words++)
dest[words] = src[b];
dest[words] = 0;
return (dest);
}
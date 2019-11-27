#include "shell.h"
/**
 * _strcpy - copy of string
 * @dest: string
 * @src: string
 * Return: dest a copy
 */
char *_strcpy(char *dest, char *src)
{
int cont_words;
for (cont_words = 0; src[cont_words] != 0; cont_words++)
dest[cont_words] = src[cont_words];
dest[cont_words] = 0;
return (dest);
}
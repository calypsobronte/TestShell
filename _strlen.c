#include "shell.h"
/**
 * _strlen - counts length of a string
 * @str: - letter string
 * Return: number of string
 */
int _strlen(char *str)
{
int _string;
while (str[_string] != 0)
_string++;
return (_string);
}
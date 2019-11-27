#include "shell.h"
/**
  * _strtok - tokenizes a string
  * @str: string to tokenize
  * @delimitador: string that contains the delimitadoriters
  * Return: pointer to position in string of a null terminated word.
  */
char *_strtok(char *str, const char *delimitador)
{
	static char *run_string, *end_string, *end;
	unsigned int i, j;
	int words = 0;

	if (str == NULL)
	{
		if (run_string == NULL || end == NULL)
			return (NULL);
		str = end + 1;
	}
	else
		end_string = str + _strlen(str);
	for (i = 0; str + i < end_string; i++)
	{
		for (j = 0; delimitador != NULL && delimitador[j] != '\0'; j++)
		{
			if (str[i] == delimitador[j])
			{
				if (words == 1)
				{
					str[i] = '\0';
					end = str + i;
					return (run_string);
				}
				break;
			}
		}
		if (delimitador[j] == '\0' && words == 0)
		{
			words = 1;
			run_string = str + i;
		}
	}
	end = NULL;
	if (words == 1)
		return (run_string);
	return (NULL);
}

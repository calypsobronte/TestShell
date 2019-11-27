#include "shell.h"
/**
 * main - funcion de la shell
 * @ac: int
 * @av: point of point
 * Return: 1
 */
int main(int ac, char **av)
{
	// Lina
	char *buffer = NULL, *TokenTemporal = NULL;
	char **TokenMain = NULL;
	size_t BUFFSIZE = 32, characters = 0;
	int i = 0, j = 0;

	while (1)
	{
		buffer = malloc(BUFFSIZE * sizeof(char));
		if (buffer == NULL)
		{
			perror("Unable to allocate buffer");
			exit(1);
		}
		printf("HolbiPro"); // cambiar despues
		printf("$ ");
		characters = getline(&buffer, &BUFFSIZE, stdin);
		TokenMain = malloc(sizeof(char *) * BUFFSIZE);
		if (TokenMain == NULL)
		{
			return (0);
		}
		if (characters == (size_t)-1)
		{
			free(TokenMain);
			free(buffer);
			printf("\n");
			break;
		}
		TokenTemporal = _strtok(buffer, " ");
		i = 0;
		while (TokenTemporal != NULL)
		{
			TokenMain[i] = malloc((sizeof(char) * _strlen(TokenTemporal)) + 1);
			_strcpy(TokenMain[i], TokenTemporal);
			TokenTemporal = _strtok(NULL, " ");
			i++;
		}
		get_func(TokenMain[0], TokenMain);
		j = 0;
		while (TokenMain[j] != NULL)
			j++;
		free_shell(TokenMain, j);
		free(buffer);
		}
		return (0);
}

// Chris
/**
 * free_shell - funcion de para liberar en el main
 * @TokenMain: char
 * @size: size del argumento
 */
void free_shell(char **TokenMain, int size)
{
int i;
for (i = 0; i < size; i++)
{
if (TokenMain[i] != NULL)
	free(TokenMain[i]);
}
free(TokenMain);
}

/**
 * get_func - funcion con sus principales funcionamientos con los diferentes comando y tags
 * @TokenMain: char
 * @Token: token
 * Return: 1
 */
// Chris y Lina
int get_func(char *TokenMain, char **Token)
{
	// Chris
	char *search = NULL;
	pid_t child_pid = 0;
	int status = 0;
	int i = 0;

	while (Token[i] != NULL)
		i++;
	Token[i] = NULL;
	if (i == 1)
	{
		TokenMain[_strlen(TokenMain) - 1] = '\0';
	}
	else if (i > 1)
	{
		Token[i - 1][_strlen(Token[i - 1]) - 1] = '\0';
	}
	// cambio 27 nov
	if (TokenMain[0] == '/' || TokenMain[0] == '.')
	{
		search = malloc(sizeof(char) * _strlen(TokenMain) + 1);
		_strcpy(search, TokenMain);

	}
	else
	{
		search = malloc(sizeof(char) * _strlen(TokenMain) + 6);
		_strcpy(search, "/bin/");
		_strcat(search, TokenMain);
	}
	// Lina
	free(Token[0]);
	Token[0] = malloc(sizeof(char) * _strlen(search) + 1);
	_strcat(Token[0], search);


	if (access(search, X_OK | F_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(search, Token, NULL);
			return (0);
		}
		else
			//waitpid(child_pid, &status, 0);
			waitpid(child_pid, NULL, 0);

	}
	else
		perror("./shell");
	free(search);
	return (1);
}

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

/* cambiar por los que tenemos OJO*/

// strlen https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x05-pointers_arrays_strings/2-strlen.c
// strcpy https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x05-pointers_arrays_strings/9-strcpy.c
// strcat https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x06-pointers_arrays_strings/0-strcat.c

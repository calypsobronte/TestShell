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
		TokenTemporal = strtok(buffer, " ");
		i = 0;
		while (TokenTemporal != NULL)
		{
			TokenMain[i] = malloc((sizeof(char) * strlen(TokenTemporal)) + 1);
			strcpy(TokenMain[i], TokenTemporal);
			TokenTemporal = strtok(NULL, " ");
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
		TokenMain[strlen(TokenMain) - 1] = '\0';
	}
	else if (i > 1)
	{
		Token[i - 1][strlen(Token[i - 1]) - 1] = '\0';
	}
	if (TokenMain[0] == '/')
	{
		search = malloc(sizeof(char) * strlen(TokenMain) + 1);
		strcpy(search, TokenMain);

	}
	else
	{
		search = malloc(sizeof(char) * strlen(TokenMain) + 6);
		strcpy(search, "/bin/");
		strcat(search, TokenMain);
	}
	// Lina
	free(Token[0]);
	Token[0] = malloc(sizeof(char) * strlen(search) + 1);
	strcat(Token[0], search);


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

/* cambiar por los que tenemos OJO*/

// strlen https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x05-pointers_arrays_strings/2-strlen.c
// strcpy https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x05-pointers_arrays_strings/9-strcpy.c
// strcat https://github.com/calypsobronte/holbertonschool-low_level_programming/blob/master/0x06-pointers_arrays_strings/0-strcat.c

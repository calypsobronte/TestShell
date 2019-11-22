#include "shell.h"

int main(int ac, char **av)
{
    char *buffer = NULL, *TokenTemporal = NULL, *copy = NULL;
    char **TokenMain = NULL;
    size_t BUFFSIZE = 32;
    size_t characters;
    int i = 0;
    buffer = malloc(BUFFSIZE * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
	copy = malloc(sizeof(char) * BUFFSIZE);
	if (copy == NULL)
	{
	perror("Unable to allocate buffer");
	exit(1);
	}
    while (1)
    {
        printf("HolbiPro");
        printf("$ ");
        characters = getline(&buffer, &BUFFSIZE, stdin);
		strcpy(copy, buffer);
        TokenMain = malloc(sizeof(char *) * BUFFSIZE);
        if (characters == (size_t)-1)
        {
            free(TokenMain);
            free(buffer);
			free(copy);
            printf("\n");
            break;
        }
        TokenTemporal = strtok(copy, " ");
		i = 0;
        while (TokenTemporal != NULL)
        {
			TokenMain[i] = malloc((sizeof(char) * strlen(TokenTemporal)) + 1);
            strcpy(TokenMain[i], TokenTemporal);
            TokenTemporal = strtok(NULL, " ");
			i++;
        }
		get_func(TokenMain[0], TokenMain);
        free_shell(TokenMain, i);
    }
    return (0);
}

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

int get_func(char * TokenMain, char **Token)
{
	char search[1024];
	pid_t child_pid;
	int status;
	int i = 0;
	strcpy(search, "/bin/");
	TokenMain[strlen(TokenMain)-1] = '\0';
	while(Token[i] != NULL)
	{
		i++;
	}
	Token[i] = NULL;
	if(access(TokenMain, X_OK | F_OK) == 0)
	{
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return (1);
    }
    if (child_pid == 0)
    {
		execve(TokenMain, Token, NULL);
        fflush(0);
		return(0);
	}
	else
        wait(&status);
	}
	else
	{
	strcat(search, TokenMain);
	if(access(search, X_OK | F_OK) == 0)
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
        fflush(0);
		return(0);
	}
	else
        wait(&status);
	}
	}
	return(1);
}

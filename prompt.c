#include "shell.h"
/* int main(int argc, char const *argv[])
{
        printf("\e[1;1H\e[2J");
        char *buffer;
        size_t BUFFSIZE = 32;
        size_t characters;
        char **s =  malloc(BUFFSIZE * sizeof(char));
        buffer = (char *)malloc(BUFFSIZE * sizeof(char));
        if(buffer == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }
        while (1)
        {
            //Start color
            printf("\e[36mHolbisPro\e[0m");
            printf("$ >");
            //End color
            printf("\e[92m \e[0m");
            characters = getline(&buffer,&BUFFSIZE,stdin);
            if (characters == -1)
            {
                printf("\n");
                break;
            }
            //Call Tokens
            TokensGenator(buffer);
        }
        free(s);
        free(buffer);
    return 0;
}
 */

int main(int ac, char **av)
{
    char *buffer, *TokenTemporal, *copy;
    char **TokenMain;
    size_t BUFFSIZE = 32;
    size_t characters;
    int i = 0, pid, size = 0;
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
			printf("Command Requested is %s\n", TokenMain[i]);
            TokenTemporal = strtok(NULL, " ");
			i++;
        }
		get_func(TokenMain[0]);
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

int get_func(char * TokenMain)
{
	char *search;
	search = malloc(sizeof(char) * (strlen(TokenMain) + 6));
	strcpy(search, "/bin/");
	TokenMain[strlen(TokenMain)-1] = '\0';
	strcat(search, TokenMain);
	if(access(search, X_OK | F_OK) == 0)
	{
		printf("%s is executable\n", search);
		free(search);
		return(1);
	}
	printf("%s is not executable\n", search);
	free(search);
	return(0);
}

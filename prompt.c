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

int main(void)
{
    char *buffer, *TokenTemporal;
    char **TokenMain;
    size_t BUFFSIZE = 32;
    size_t characters;
    int i = 0;
    buffer = malloc(BUFFSIZE * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    while (1)
    {
        TokenMain = malloc(sizeof(char *) * BUFFSIZE);
        printf("\e[36mHolbisPro\e[0m");
        printf(" $ >");
        //End color
        printf("\e[92m \e[0m");
        characters = getline(&buffer, &BUFFSIZE, stdin);
        if (characters == (size_t)-1)
        {
            free(TokenMain);
            free(buffer);
            printf("\n");
            break;
        }
        TokenTemporal = strtok(buffer, " ");
        while    (TokenTemporal != NULL)
        {
            TokenMain[i] = TokenTemporal;
            TokenTemporal = strtok(NULL, " ");
            i++;
        }
        free(TokenMain);
    }
    return (0);
}

//char envp[] = {(char *) "PATH=/bin/$x", 0};
// exit
// cd
// ls
// pwd
// env
// clear

#include "shell.h"
int main(int argc, char const *argv[])
{
        printf("\e[1;1H\e[2J");
        char *buffer;
        size_t bufsize = 32;
        size_t characters;
        char **s =  malloc(bufsize * sizeof(char));
        buffer = (char *)malloc(bufsize * sizeof(char));
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
            characters = getline(&buffer,&bufsize,stdin);
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

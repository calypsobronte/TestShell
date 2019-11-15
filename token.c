#include "shell.h"
char **TokensGenator(char *dates)
{
    char *TokenT;
    char **TokenP;
    int i = 0, len = 0;
    TokenT = strtok(dates, " ");
    while (TokenT != NULL)
    {
        printf("%s\n", TokenT);
        TokenT = strtok(NULL, " ");
    }
    return(0);
}

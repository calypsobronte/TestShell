#ifndef bit
#define bit
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
void free_shell(char **TokenMain, int size);
int get_func(char * TokenMain, char **Token);

#endif /* libraries example of shell Holberton  gcc -g -Wall -Werror -Wextra -pedantic prompt.c -o hsh && valgrind --leak-check=full --show-leak-kinds=all ./hsh*/

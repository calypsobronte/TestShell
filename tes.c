#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */

void handle_SIGINT()
{
  printf("Found your CTRL-C\n");
}

void setup(char inputBuffer[], char *args[],int *background)
{
    int length, /* # of characters in the command line */
         i,      /* loop index for accessing inputBuffer array */
         start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */

     ct = 0;

     /* read what the user enters on the command line */
     length = read(STDIN_FILENO, inputBuffer, MAX_LINE);  

     start = -1;
     if (length == 0)
        exit(0);            /* ^d was entered, end of user command stream */
     if (length < 0){
        perror("error reading the command");
    exit(-1);           /* terminate with error code of -1 */
    }

     /* examine every character in the inputBuffer */
     for (i = 0; i < length; i++) { 
        switch (inputBuffer[i]){
        case ' ':
        case '\t' :               /* argument separators */
            if(start != -1){
                args[ct] = &inputBuffer[start];    /* set up pointer */
                ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;

        case '\n':                 /* should be the final char examined */
            if (start != -1){
                args[ct] = &inputBuffer[start];     
                ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;

        case '&':
            *background = 1;
            inputBuffer[i] = '\0';
            break;

        default :             /* some other character */
            if (start == -1)
                start = i;
    } 
    }    
    args[ct] = NULL; /* just in case the input line was > 80 */
} 

int main(void)
{
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    int background;             /* equals 1 if a command is followed by '&' */
    char *args[MAX_LINE/2+1];/* command line (of 80) has max of 40 arguments */

    struct sigaction handler;
    handler.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);

    while (1){            /* Program terminates normally inside setup */
        background = 0;
    printf("COMMAND->");
        fflush(0);
        setup(inputBuffer, args, &background);       /* get next command */

        int pid;

    pid = fork(); /* for a child process */

    if (pid < 0) { /* check if error occurred with child process */
      fprintf(stderr, "Fork Failed");
      return 1;
    } else if (pid == 0) { /* child process */
      execvp(args[0], args);
    } else {
      if (background == 0){ /* check if the parent should wait */
        //wait(args);
        waitpid(pid, NULL, 0);
      }
    }

    /* the steps are:
      (1) fork a child process using fork()
      (2) the child process will invoke execvp()
      (3) if background == 0, the parent will wait, 
        otherwise returns to the setup() function. */
    }
}
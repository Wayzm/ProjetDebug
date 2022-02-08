#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

#include "tools.h"

int* vector;

char key;

void choice (int nbr, char **argc)
{
    key = 0;

    switch(key){
      case 's':
        // Segfaul
        break;
      case 'c':
        // catch SIGINT
        break;
      case 'q':
        break;
      default:
        printf("How to use : \n \n Press s to find the segfault. \n Press c to catch SIGINT. \n Press q to exit.");
      break;
    }
}


int main (int argv, char ** argc)
{
  char key;
  printf("LOL\n");
  return 0;
}

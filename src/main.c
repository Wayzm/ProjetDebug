#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

#include "tools.h"
#include "sfm.h"

int* vector;

char key;

void choice (int nbr)
{
    key = 0;

    switch(key){
      case 's':
        // Segfault
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
  return 0;
}

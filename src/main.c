#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "tools.h"


int main ()
{
  char cwd[257];
  char* name;
  name = (char*)malloc((128)*sizeof(char));
  prog_name(name,cwd);

  //Change how the tty works 
  struct termios old_term, new_term;
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK | O_NOCTTY );
  tcgetattr(STDIN_FILENO, &old_term);
  new_term = old_term;
  new_term.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

  choice();
  printf("LOL! \n");

  //Everything back to starting point
  tcflush(STDIN_FILENO, TCIFLUSH); 
  tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
  fcntl(STDIN_FILENO, F_SETFL, flags);

  free(name);
  return 0;

}

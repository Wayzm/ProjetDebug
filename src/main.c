#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "tools.h"


int main (int argc, char **argv)
{
  int h = 0;
  prog_name(argv);

  choice(argv);

  return 0;

}

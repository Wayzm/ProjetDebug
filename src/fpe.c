#include <stdlib.h>
#include <stdio.h>

#include "Errors.h"


void fpe ()
{
  int n = 1;
  int d = 0;
  double ans = n/d;
}

int main (int argc, char **argv)
{
  printf(" Argument : %s", argv[1]);
  fpe();
  return 2;
}

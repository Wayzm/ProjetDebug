#include <stdlib.h>
#include <stdio.h>

#include "Errors.h"


void fpe ()
{
  int n = 1;
  int d = 0;
  double ans = n/d;
}

int main (int argv, char **argc)
{
  fpe();
  return 2;
}

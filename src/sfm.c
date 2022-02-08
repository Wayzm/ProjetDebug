#include <stdio.h>
#include <stdlib.h>

#include "Errors.h"

int *axis;

void segfault(int* vector)
{
  // We dont malloc in order to induce a segfault

  for (int i=0; i<25;i++)
  {
    vector[i]=rand();
    printf("%d \n",vector[i]);
  }

}

int main (int arg, char **argc)
{
  segfault(axis);
  return 1;
}

#include <stdio.h>
#include <stdlib.h>

int *Segfaultmachine;

int main (int argv, char **argc)
{
  // We dont malloc in order to induce a segfault 

  for (int i=0; i<25;i++)
  {
    Segfaultmachine[i]=rand();
    printf("%d \n",Segfaultmachine[i]);
  }

  return 0;
  free(Segfaultmachine);
}

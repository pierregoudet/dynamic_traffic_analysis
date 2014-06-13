#include "distrib.h"

#include <stdio.h>
#include <stdlib.h>


void enter_distrib(int mes, char * distrib)
{
  distrib[mes] ++; 
}

void calc_distrib(char *distrib)
{
  FILE * f;
  if((f = fopen(argv[1], "w+")) == NULL)
    {
      perror("fopen");
    }

  float prob[OMEGA];
  int i;
  char tmp[SIZE];

  for(i = 0; i <= OMEGA; i++)
    {
      prob[i] = distrib[i] / OMEGA;
      sprintf(tmp, "%d %g\n", i, prob[i]);
      fprintf(f, tmp);
    }
}

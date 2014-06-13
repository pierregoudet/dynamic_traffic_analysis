#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "const.h"

int main (int argc, char **argv)
{
  if(argc != 2)
    {
      fprintf(stderr,"Please enter two data file as argument\n");
      return EXIT_SUCCESS;
    }
  time_t t;
  srand((unsigned) time(&t));
  
  FILE* f;
  int sum = 0;
  int flow; 
  int i = 0;
  int j = 0;
  char tmp[SIZE];
  char mes[OMEGA];

  if((f = fopen(argv[1], "w+")) == NULL)
    {
      perror("fopen");
    }
  
  for(i = 0; i <= TIME; i++)
    {
      sprintf(tmp, "%d ", i);
      for(j = 0; j <= NB_VN; j++)
      	{
      	  flow = rand() % FLOW_SLICE;
      	  sprintf(tmp, "%s %d", tmp, flow);
      	  sum = sum + flow;
	  enter_distrib(sum, mes);
      	}
      sprintf(tmp,"%s %d\n", tmp, sum);
      fprintf(f, tmp);
      sum = 0;
    }
  
  fclose(f);
  return EXIT_SUCCESS;
}

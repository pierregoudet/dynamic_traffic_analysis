#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "allocation.h"
#include "tad.h"
#include "const.h"



int allocation(struct link* link, float rate, int* res)
{
  int i;
  int req = 0;

  time_t t;
  srand ((unsigned) time(&t));
  
  for(i = 0; i < NB_VN; i++)
    {
      req = rand() % (link->r_capacity/2) + 1;
      init_link_eco(link, rate, req);
      res[0] += req;
      res[1] += rate*req;
    }
  return EXIT_SUCCESS;
}



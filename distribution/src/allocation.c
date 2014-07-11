#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "allocation.h"
#include "tad.h"
#include "const.h"

int allocation(struct link* link, float rate, int* res, int nb_vn, int capacity)
{
  int i;
  int req = 0;

  time_t t;
  srand ((unsigned) time(&t));
  do
    {
      res[0] = 0;
      res[1] = 0;
      init_link_blank(link, nb_vn);

      for(i = 0; i < nb_vn; i++)
	{
	  req = rand() % (link->r_capacity/2) + 1;
	  init_link_eco(link, rate, req, nb_vn);
	  res[0] += req;
	  res[1] += rate*req;
	}
    }
  while(res[0] >= capacity);
      
  return EXIT_SUCCESS;
}


